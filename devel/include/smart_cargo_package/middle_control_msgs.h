// Generated by gencpp from file smart_cargo_package/middle_control_msgs.msg
// DO NOT EDIT!


#ifndef SMART_CARGO_PACKAGE_MESSAGE_MIDDLE_CONTROL_MSGS_H
#define SMART_CARGO_PACKAGE_MESSAGE_MIDDLE_CONTROL_MSGS_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace smart_cargo_package
{
template <class ContainerAllocator>
struct middle_control_msgs_
{
  typedef middle_control_msgs_<ContainerAllocator> Type;

  middle_control_msgs_()
    : time_stamp()
    , target_object(0)
    , action(0)  {
    }
  middle_control_msgs_(const ContainerAllocator& _alloc)
    : time_stamp()
    , target_object(0)
    , action(0)  {
  (void)_alloc;
    }



   typedef ros::Time _time_stamp_type;
  _time_stamp_type time_stamp;

   typedef int32_t _target_object_type;
  _target_object_type target_object;

   typedef int32_t _action_type;
  _action_type action;





  typedef boost::shared_ptr< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> const> ConstPtr;

}; // struct middle_control_msgs_

typedef ::smart_cargo_package::middle_control_msgs_<std::allocator<void> > middle_control_msgs;

typedef boost::shared_ptr< ::smart_cargo_package::middle_control_msgs > middle_control_msgsPtr;
typedef boost::shared_ptr< ::smart_cargo_package::middle_control_msgs const> middle_control_msgsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::smart_cargo_package::middle_control_msgs_<ContainerAllocator1> & lhs, const ::smart_cargo_package::middle_control_msgs_<ContainerAllocator2> & rhs)
{
  return lhs.time_stamp == rhs.time_stamp &&
    lhs.target_object == rhs.target_object &&
    lhs.action == rhs.action;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::smart_cargo_package::middle_control_msgs_<ContainerAllocator1> & lhs, const ::smart_cargo_package::middle_control_msgs_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace smart_cargo_package

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8d58a37429769e2a5c482d5c6ba001eb";
  }

  static const char* value(const ::smart_cargo_package::middle_control_msgs_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8d58a37429769e2aULL;
  static const uint64_t static_value2 = 0x5c482d5c6ba001ebULL;
};

template<class ContainerAllocator>
struct DataType< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "smart_cargo_package/middle_control_msgs";
  }

  static const char* value(const ::smart_cargo_package::middle_control_msgs_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "time time_stamp      # Message 발행 시간 (ros::Time)\n"
"int32 target_object  # 대상 객체 H/W Index Enum\n"
"int32 action         # 명령 동작 Action Index Enum (홀수만 와야 한다)\n"
;
  }

  static const char* value(const ::smart_cargo_package::middle_control_msgs_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.time_stamp);
      stream.next(m.target_object);
      stream.next(m.action);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct middle_control_msgs_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::smart_cargo_package::middle_control_msgs_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::smart_cargo_package::middle_control_msgs_<ContainerAllocator>& v)
  {
    s << indent << "time_stamp: ";
    Printer<ros::Time>::stream(s, indent + "  ", v.time_stamp);
    s << indent << "target_object: ";
    Printer<int32_t>::stream(s, indent + "  ", v.target_object);
    s << indent << "action: ";
    Printer<int32_t>::stream(s, indent + "  ", v.action);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SMART_CARGO_PACKAGE_MESSAGE_MIDDLE_CONTROL_MSGS_H
