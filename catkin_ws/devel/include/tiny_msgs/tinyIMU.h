// Generated by gencpp from file tiny_msgs/tinyIMU.msg
// DO NOT EDIT!


#ifndef TINY_MSGS_MESSAGE_TINYIMU_H
#define TINY_MSGS_MESSAGE_TINYIMU_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <tiny_msgs/tinyVector.h>
#include <tiny_msgs/tinyVector.h>

namespace tiny_msgs
{
template <class ContainerAllocator>
struct tinyIMU_
{
  typedef tinyIMU_<ContainerAllocator> Type;

  tinyIMU_()
    : header()
    , accel()
    , gyro()  {
    }
  tinyIMU_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , accel(_alloc)
    , gyro(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::tiny_msgs::tinyVector_<ContainerAllocator>  _accel_type;
  _accel_type accel;

   typedef  ::tiny_msgs::tinyVector_<ContainerAllocator>  _gyro_type;
  _gyro_type gyro;




  typedef boost::shared_ptr< ::tiny_msgs::tinyIMU_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::tiny_msgs::tinyIMU_<ContainerAllocator> const> ConstPtr;

}; // struct tinyIMU_

typedef ::tiny_msgs::tinyIMU_<std::allocator<void> > tinyIMU;

typedef boost::shared_ptr< ::tiny_msgs::tinyIMU > tinyIMUPtr;
typedef boost::shared_ptr< ::tiny_msgs::tinyIMU const> tinyIMUConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::tiny_msgs::tinyIMU_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::tiny_msgs::tinyIMU_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace tiny_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'tiny_msgs': ['/home/ubuntu/catkin_ws/src/tiny_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::tiny_msgs::tinyIMU_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::tiny_msgs::tinyIMU_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tiny_msgs::tinyIMU_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::tiny_msgs::tinyIMU_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tiny_msgs::tinyIMU_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::tiny_msgs::tinyIMU_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::tiny_msgs::tinyIMU_<ContainerAllocator> >
{
  static const char* value()
  {
    return "53582bc8b7315f3bc7728d82df98bb24";
  }

  static const char* value(const ::tiny_msgs::tinyIMU_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x53582bc8b7315f3bULL;
  static const uint64_t static_value2 = 0xc7728d82df98bb24ULL;
};

template<class ContainerAllocator>
struct DataType< ::tiny_msgs::tinyIMU_<ContainerAllocator> >
{
  static const char* value()
  {
    return "tiny_msgs/tinyIMU";
  }

  static const char* value(const ::tiny_msgs::tinyIMU_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::tiny_msgs::tinyIMU_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# a Tiny IMU message\n\
\n\
Header header\n\
tinyVector accel\n\
tinyVector gyro\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: tiny_msgs/tinyVector\n\
# A Tiny Vector\n\
\n\
int16 x\n\
int16 y\n\
int16 z\n\
";
  }

  static const char* value(const ::tiny_msgs::tinyIMU_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::tiny_msgs::tinyIMU_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.accel);
      stream.next(m.gyro);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct tinyIMU_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::tiny_msgs::tinyIMU_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::tiny_msgs::tinyIMU_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "accel: ";
    s << std::endl;
    Printer< ::tiny_msgs::tinyVector_<ContainerAllocator> >::stream(s, indent + "  ", v.accel);
    s << indent << "gyro: ";
    s << std::endl;
    Printer< ::tiny_msgs::tinyVector_<ContainerAllocator> >::stream(s, indent + "  ", v.gyro);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TINY_MSGS_MESSAGE_TINYIMU_H
