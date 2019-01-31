// Generated by gencpp from file aiguillages/Capteurs.msg
// DO NOT EDIT!


#ifndef AIGUILLAGES_MESSAGE_CAPTEURS_H
#define AIGUILLAGES_MESSAGE_CAPTEURS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace aiguillages
{
template <class ContainerAllocator>
struct Capteurs_
{
  typedef Capteurs_<ContainerAllocator> Type;

  Capteurs_()
    : capteurs(0)  {
    }
  Capteurs_(const ContainerAllocator& _alloc)
    : capteurs(0)  {
  (void)_alloc;
    }



   typedef int64_t _capteurs_type;
  _capteurs_type capteurs;




  typedef boost::shared_ptr< ::aiguillages::Capteurs_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::aiguillages::Capteurs_<ContainerAllocator> const> ConstPtr;

}; // struct Capteurs_

typedef ::aiguillages::Capteurs_<std::allocator<void> > Capteurs;

typedef boost::shared_ptr< ::aiguillages::Capteurs > CapteursPtr;
typedef boost::shared_ptr< ::aiguillages::Capteurs const> CapteursConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::aiguillages::Capteurs_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::aiguillages::Capteurs_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace aiguillages

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'aiguillages': ['/home/projn7cellule/PL_2018/ros_ws/src/aiguillages/msg'], 'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::aiguillages::Capteurs_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::aiguillages::Capteurs_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::aiguillages::Capteurs_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::aiguillages::Capteurs_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::aiguillages::Capteurs_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::aiguillages::Capteurs_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::aiguillages::Capteurs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bf794154bbba9db270fca7e0cc669d41";
  }

  static const char* value(const ::aiguillages::Capteurs_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xbf794154bbba9db2ULL;
  static const uint64_t static_value2 = 0x70fca7e0cc669d41ULL;
};

template<class ContainerAllocator>
struct DataType< ::aiguillages::Capteurs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "aiguillages/Capteurs";
  }

  static const char* value(const ::aiguillages::Capteurs_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::aiguillages::Capteurs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64 capteurs\n\
\n\
";
  }

  static const char* value(const ::aiguillages::Capteurs_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::aiguillages::Capteurs_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.capteurs);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Capteurs_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::aiguillages::Capteurs_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::aiguillages::Capteurs_<ContainerAllocator>& v)
  {
    s << indent << "capteurs: ";
    Printer<int64_t>::stream(s, indent + "  ", v.capteurs);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AIGUILLAGES_MESSAGE_CAPTEURS_H
