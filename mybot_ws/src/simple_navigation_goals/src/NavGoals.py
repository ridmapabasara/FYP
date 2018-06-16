#!/usr/bin/env python
# license removed for brevity

import rospy

# Brings in the SimpleActionClient
import actionlib
# Brings in the .action file and messages used by the move base action
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal

def movebase_client(Name):

   # Create an action client called "move_base" with action definition file "MoveBaseAction"
    client = actionlib.SimpleActionClient('move_base',MoveBaseAction)
 
   # Waits until the action server has started up and started listening for goals.
    client.wait_for_server()

   # Creates a new goal with the MoveBaseGoal constructor
    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.header.stamp = rospy.Time.now()
   # Move 0.5 meters forward along the x axis of the "map" coordinate frame 

	#creating the cordinate list
    Kamal=['Kamal',54.9,48];
    Amal=['Amal',51.1,46.2];
    Nimal=['Nimal',49.1,46.1];
    

    if(Name=='Kamal'):
    	goal.target_pose.pose.position.x = Kamal[1]
    	goal.target_pose.pose.position.y = Kamal[2]
   # No rotation of the mobile base frame w.r.t. map frame
    	goal.target_pose.pose.orientation.w = 1.0
    if(Name=='Amal'):
    	goal.target_pose.pose.position.x = Amal[1]
    	goal.target_pose.pose.position.y = Amal[2]
   # No rotation of the mobile base frame w.r.t. map frame
    	goal.target_pose.pose.orientation.w = 1.0
    if(Name=='Nimal'):
    	goal.target_pose.pose.position.x = Nimal[1]
    	goal.target_pose.pose.position.y = Nimal[2]
   # No rotation of the mobile base frame w.r.t. map frame
    	goal.target_pose.pose.orientation.w = 1
    else:
	print 'invalid location given'

   # Sends the goal to the action server.
    client.send_goal(goal)
   # Waits for the server to finish performing the action.
    wait = client.wait_for_result()
   # If the result doesn't arrive, assume the Server is not available
    if not wait:
        rospy.logerr("Action server not available!")
        rospy.signal_shutdown("Action server not available!")
    else:
    # Result of executing the action
        return client.get_result()   

# If the python node is executed as main process (sourced directly)
if __name__ == '__main__':
    try:
       # Initializes a rospy node to let the SimpleActionClient publish and subscribe
        rospy.init_node('GiveGoal')
	while(1):
		print 'Enter a name'
		Name=raw_input()
        	result = movebase_client(Name)
        	if result:
            		rospy.loginfo("Goal execution done!")

    except rospy.ROSInterruptException:
        rospy.loginfo("Navigation test finished.")

