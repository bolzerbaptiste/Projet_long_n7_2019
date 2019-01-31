// Generated by gencpp from file vrep_common/VisionSensorDepthBuff.msg
// DO NOT EDIT!


#ifndef VREP_COMMON_MESSAGE_VISIONSENSORDEPTHBUFF_H
#define VREP_COMMON_MESSAGE_VISIONSENSORDEPTHBUFF_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Int32.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32MultiArray.h>

namespace vrep_common
{
template <class ContainerAllocator>
struct VisionSensorDepthBuff_
{
  typedef VisionSensorDepthBuff_<ContainerAllocator> Type;

  VisionSensorDepthBuff_()
    : x()
    , y()
    , data()  {
    }
  VisionSensorDepthBuff_(const ContainerAllocator& _alloc)
    : x(_alloc)
    , y(_alloc)
    , data(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Int32_<ContainerAllocator>  _x_type;
  _x_type x;

   typedef  ::std_msgs::Int32_<ContainerAllocator>  _y_type;
  _y_type y;

   typedef  ::std_msgs::Float32MultiArray_<ContainerAllocator>  _data_type;
  _data_type data;




  typedef boost::shared_ptr< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> const> ConstPtr;

}; // struct VisionSensorDepthBuff_

typedef ::vrep_common::VisionSensorDepthBuff_<std::allocator<void> > VisionSensorDepthBuff;

typedef boost::shared_ptr< ::vrep_common::VisionSensorDepthBuff > VisionSensorDepthBuffPtr;
typedef boost::shared_ptr< ::vrep_common::VisionSensorDepthBuff const> VisionSensorDepthBuffConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace vrep_common

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'sensor_msgs': ['/opt/ros/indigo/share/sensor_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/indigo/share/geometry_msgs/cmake/../msg'], 'vrep_common': ['/home/projn7cellule/PL_2018/ros_ws/src/vrep_common/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> >
{
  static const char* value()
  {
    return "fe6c62e891cf9e2aef9b4742b6ae660f";
  }

  static const char* value(const ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xfe6c62e891cf9e2aULL;
  static const uint64_t static_value2 = 0xef9b4742b6ae660fULL;
};

template<class ContainerAllocator>
struct DataType< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> >
{
  static const char* value()
  {
    return "vrep_common/VisionSensorDepthBuff";
  }

  static const char* value(const ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Int32 x\n\
std_msgs/Int32 y\n\
std_msgs/Float32MultiArray data\n\
================================================================================\n\
MSG: std_msgs/Int32\n\
int32 data\n\
================================================================================\n\
MSG: std_msgs/Float32MultiArray\n\
# Please look at the MultiArrayLayout message definition for\n\
# documentation on all multiarrays.\n\
\n\
MultiArrayLayout  layout        # specification of data layout\n\
float32[]         data          # array of data\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/MultiArrayLayout\n\
# The multiarray declares a generic multi-dimensional array of a\n\
# particular data type.  Dimensions are ordered from outer most\n\
# to inner most.\n\
\n\
MultiArrayDimension[] dim # Array of dimension properties\n\
uint32 data_offset        # padding elements at front of data\n\
\n\
# Accessors should ALWAYS be written in terms of dimension stride\n\
# and specified outer-most dimension first.\n\
# \n\
# multiarray(i,j,k) = data[data_offset + dim_stride[1]*i + dim_stride[2]*j + k]\n\
#\n\
# A standard, 3-channel 640x480 image with interleaved color channels\n\
# would be specified as:\n\
#\n\
# dim[0].label  = \"height\"\n\
# dim[0].size   = 480\n\
# dim[0].stride = 3*640*480 = 921600  (note dim[0] stride is just size of image)\n\
# dim[1].label  = \"width\"\n\
# dim[1].size   = 640\n\
# dim[1].stride = 3*640 = 1920\n\
# dim[2].label  = \"channel\"\n\
# dim[2].size   = 3\n\
# dim[2].stride = 3\n\
#\n\
# multiarray(i,j,k) refers to the ith row, jth column, and kth channel.\n\
\n\
================================================================================\n\
MSG: std_msgs/MultiArrayDimension\n\
string label   # label of given dimension\n\
uint32 size    # size of given dimension (in type units)\n\
uint32 stride  # stride of given dimension\n\
";
  }

  static const char* value(const ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VisionSensorDepthBuff_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::vrep_common::VisionSensorDepthBuff_<ContainerAllocator>& v)
  {
    s << indent << "x: ";
    s << std::endl;
    Printer< ::std_msgs::Int32_<ContainerAllocator> >::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    s << std::endl;
    Printer< ::std_msgs::Int32_<ContainerAllocator> >::stream(s, indent + "  ", v.y);
    s << indent << "data: ";
    s << std::endl;
    Printer< ::std_msgs::Float32MultiArray_<ContainerAllocator> >::stream(s, indent + "  ", v.data);
  }
};

} // namespace message_operations
} // namespace ros

#endif // VREP_COMMON_MESSAGE_VISIONSENSORDEPTHBUFF_H
