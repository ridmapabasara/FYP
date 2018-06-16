//
//ROS headers
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <ros.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>
#include <ros/time.h>
#include "robot_specs.h"
#include <Encoder.h>
//#include <tiny_msgs/tinyVector.h>
//#include <tiny_msgs/tinyIMU.h>


//Library to communicate with I2C devices
#include "Wire.h"
//I2C communication library for MPU6050
//#include "I2Cdev.h"
//MPU6050 interfacing library
//#include "MPU6050_6Axis_MotionApps20.h"
#include "DualVNH5019MotorShieldMod3.h"
#include <limits.h>
//MPU6050 accelgyro(0x68);
//set up the class dot names for the libraries and


#define encodPinA1      3     // encoder A pin
#define encodPinB1      4     // encoder B pin
#define encodPinA2      18
#define encodPinB2      17
#define LOOPTIME        100   // PID loop time(ms)
#define SMOOTH      10
#define FORWARD 1
#define RELEASE 0
#define BACKWARD -1
#define sign(x) (x > 0) - (x < 0)

// configure library pins
DualVNH5019MotorShieldMod3 md;//Use default pins
//Motor Shield headers

Encoder knobLeft(3, 4);//Encoders////////////////////////////////ENCODERS////////////////////////////////////
Encoder knobRight(18, 17);
long positionLeft  = -999;
long positionRight = -999;



////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////


unsigned long lastMilli = 0;       // loop timing
unsigned long lastMilliPub = 0;
double rpm_req1 = 0;
double rpm_req2 = 0;
double rpm_act1 = 0;
double rpm_act2 = 0;
double rpm_req1_smoothed = 0;
double rpm_req2_smoothed = 0;

int direction1 = FORWARD;
int direction2 = FORWARD;
int prev_direction1 = RELEASE;
int prev_direction2 = RELEASE;
int PWM_val1 = 0;
int PWM_val2 = 0;
volatile long count1 = 0;          // rev counter
volatile long count2 = 0;
long countAnt1 = 0;
long countAnt2 = 0;
float Kp =   0.5;
float Kd =   0;
float Ki =   0;

ros::NodeHandle nh;

void handle_cmd( const geometry_msgs::Twist& cmd_msg) {
  double x = cmd_msg.linear.x;
  double z = cmd_msg.angular.z;
  if (z == 0) {     // go straight
    // convert m/s to rpm
    rpm_req1 = x * 60 / (pi * wheel_diameter);
    rpm_req2 = rpm_req1;
  }
  else if (x == 0) {
    // convert rad/s to rpm
    rpm_req2 = z * track_width * 60 / (wheel_diameter * pi * 2);
    rpm_req1 = -rpm_req2;
  }
  else {
    rpm_req1 = x * 60 / (pi * wheel_diameter) - z * track_width * 60 / (wheel_diameter * pi * 2);
    rpm_req2 = x * 60 / (pi * wheel_diameter) + z * track_width * 60 / (wheel_diameter * pi * 2);
  }
   
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", handle_cmd);



geometry_msgs::Vector3Stamped rpm_msg;
ros::Publisher rpm_pub("rpm", &rpm_msg);
ros::Time current_time;
ros::Time last_time;

void setup() {
  md.init();
  //AFMS.begin();  // create with the default frequency 1.6KHz
  count1 = 0;
  count2 = 0;
  countAnt1 = 0;
  countAnt2 = 0;
  rpm_req1 = 0;
  rpm_req2 = 0;
  rpm_act1 = 0;
  rpm_act2 = 0;
  PWM_val1 = 0;
  PWM_val2 = 0;
 // Setup_MPU6050();
  //Setup Reset pins
  nh.initNode();
  nh.getHardware()->setBaud(57600);
  //Setup MPU 6050


  nh.subscribe(sub);
  nh.advertise(rpm_pub);
  //nh.advertise(imu_pub);


  //pinMode(encodPinA1, INPUT);
  // pinMode(encodPinB1, INPUT);
  //digitalWrite(encodPinA1, HIGH);                // turn on pullup resistor
  // digitalWrite(encodPinB1, HIGH);
  // attachInterrupt(1, encoder1, RISING);

  //pinMode(encodPinA2, INPUT);
  //pinMode(encodPinB2, INPUT);
  //digitalWrite(encodPinA2, HIGH);                // turn on pullup resistor
  //digitalWrite(encodPinB2, HIGH);
  //attachInterrupt(0, encoder2, RISING);
  //motor1->setSpeed(0);
  //motor2->setSpeed(0);
  md.setM1Speed(0);
  md.setM2Speed(0);

}

void loop() {
  nh.spinOnce();
  unsigned long time = millis();
  if (time - lastMilli >= LOOPTIME)   {  // enter tmed loop
    getMotorData(time - lastMilli);
    PWM_val1 = updatePid(1, PWM_val1, rpm_req1, rpm_act1);
    PWM_val2 = updatePid(2, PWM_val2, rpm_req2, rpm_act2);
  
    if (PWM_val1 > 0) direction1 = FORWARD;
    else if (PWM_val1 < 0) direction1 = BACKWARD;
    if (rpm_req1 == 0) direction1 = RELEASE;
    if (PWM_val2 > 0) direction2 = FORWARD;
    else if (PWM_val2 < 0) direction2 = BACKWARD;
    if (rpm_req2 == 0) direction2 = RELEASE;
    //motor1->run(direction1);
    //motor2->run(direction2);

    md.setM1Speed(abs(PWM_val1)*direction1);
    md.setM2Speed(abs(PWM_val2)*direction2);
 

    publishRPM(time - lastMilli);//Added IMU as well as a seperate publisher called tinyIMU
    lastMilli = time;
   
  }
  if (time - lastMilliPub >= LOOPTIME) {
    //  publishRPM(time-lastMilliPub);
    lastMilliPub = time;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void getMotorData(unsigned long time)  {
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {

    count1 = newLeft;
    count2 = newRight;

    positionLeft = newLeft;
    positionRight = newRight;
  }


  rpm_act1 = double((count1 - countAnt1) * 60 * 1000) / double(time * encoder_pulse * gear_ratio);
  rpm_act2 = double((count2 - countAnt2) * 60 * 1000) / double(time * encoder_pulse * gear_ratio);
  countAnt1 = count1;
  countAnt2 = count2;
}

int updatePid(int id, int command, double targetValue, double currentValue) {
  double pidTerm = 0;                            // PID correction
  double error = 0;
  double new_pwm = 0;
  double new_cmd = 0;
  static double last_error1 = 0;
  static double last_error2 = 0;
  static double int_error1 = 0;
  static double int_error2 = 0;

  error = targetValue - currentValue;
  if (id == 1) {
    int_error1 += error;
    pidTerm = Kp * error + Kd * (error - last_error1) + Ki * int_error1;
    last_error1 = error;
  }
  else {
    int_error2 += error;
    pidTerm = Kp * error + Kd * (error - last_error2) + Ki * int_error2;
    last_error2 = error;
  }
  new_pwm = constrain(double(command) * MAX_RPM / 4095.0 + pidTerm, -MAX_RPM, MAX_RPM);
  new_cmd = 4095.0 * new_pwm / MAX_RPM;
  return int(new_cmd);
}




void publishRPM(unsigned long time) {

  rpm_msg.header.stamp = nh.now();
  rpm_msg.vector.x = rpm_act1;
  rpm_msg.vector.y = rpm_act2;
  rpm_msg.vector.z = double(time) / 1000;
  rpm_pub.publish(&rpm_msg);
  nh.spinOnce();
  //////////////////////IMU////////

  //imu_msg.header.stamp = nh.now();
  //imu_msg.header.frame_id = 0;
 // imu_msg.header.seq = seq;




}

//void encoder1() {
//  if (digitalRead(encodPinA1) == digitalRead(encodPinB1)) count1++;
//  else count1--;
//}
//void encoder2() {
//  if (digitalRead(encodPinA2) == digitalRead(encodPinB2)) count2++;
//  else count2--;
//}
