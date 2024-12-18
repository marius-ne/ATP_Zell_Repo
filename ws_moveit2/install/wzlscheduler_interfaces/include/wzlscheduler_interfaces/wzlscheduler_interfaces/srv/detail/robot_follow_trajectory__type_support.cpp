// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from wzlscheduler_interfaces:srv/RobotFollowTrajectory.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace wzlscheduler_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void RobotFollowTrajectory_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request(_init);
}

void RobotFollowTrajectory_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request *>(message_memory);
  typed_message->~RobotFollowTrajectory_Request();
}

size_t size_function__RobotFollowTrajectory_Request__supportpoints(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<geometry_msgs::msg::Pose> *>(untyped_member);
  return member->size();
}

const void * get_const_function__RobotFollowTrajectory_Request__supportpoints(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<geometry_msgs::msg::Pose> *>(untyped_member);
  return &member[index];
}

void * get_function__RobotFollowTrajectory_Request__supportpoints(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<geometry_msgs::msg::Pose> *>(untyped_member);
  return &member[index];
}

void fetch_function__RobotFollowTrajectory_Request__supportpoints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const geometry_msgs::msg::Pose *>(
    get_const_function__RobotFollowTrajectory_Request__supportpoints(untyped_member, index));
  auto & value = *reinterpret_cast<geometry_msgs::msg::Pose *>(untyped_value);
  value = item;
}

void assign_function__RobotFollowTrajectory_Request__supportpoints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<geometry_msgs::msg::Pose *>(
    get_function__RobotFollowTrajectory_Request__supportpoints(untyped_member, index));
  const auto & value = *reinterpret_cast<const geometry_msgs::msg::Pose *>(untyped_value);
  item = value;
}

void resize_function__RobotFollowTrajectory_Request__supportpoints(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<geometry_msgs::msg::Pose> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember RobotFollowTrajectory_Request_message_member_array[1] = {
  {
    "supportpoints",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Pose>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request, supportpoints),  // bytes offset in struct
    nullptr,  // default value
    size_function__RobotFollowTrajectory_Request__supportpoints,  // size() function pointer
    get_const_function__RobotFollowTrajectory_Request__supportpoints,  // get_const(index) function pointer
    get_function__RobotFollowTrajectory_Request__supportpoints,  // get(index) function pointer
    fetch_function__RobotFollowTrajectory_Request__supportpoints,  // fetch(index, &value) function pointer
    assign_function__RobotFollowTrajectory_Request__supportpoints,  // assign(index, value) function pointer
    resize_function__RobotFollowTrajectory_Request__supportpoints  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers RobotFollowTrajectory_Request_message_members = {
  "wzlscheduler_interfaces::srv",  // message namespace
  "RobotFollowTrajectory_Request",  // message name
  1,  // number of fields
  sizeof(wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request),
  RobotFollowTrajectory_Request_message_member_array,  // message members
  RobotFollowTrajectory_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  RobotFollowTrajectory_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t RobotFollowTrajectory_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &RobotFollowTrajectory_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace wzlscheduler_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request>()
{
  return &::wzlscheduler_interfaces::srv::rosidl_typesupport_introspection_cpp::RobotFollowTrajectory_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, wzlscheduler_interfaces, srv, RobotFollowTrajectory_Request)() {
  return &::wzlscheduler_interfaces::srv::rosidl_typesupport_introspection_cpp::RobotFollowTrajectory_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace wzlscheduler_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void RobotFollowTrajectory_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response(_init);
}

void RobotFollowTrajectory_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response *>(message_memory);
  typed_message->~RobotFollowTrajectory_Response();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember RobotFollowTrajectory_Response_message_member_array[1] = {
  {
    "result",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response, result),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers RobotFollowTrajectory_Response_message_members = {
  "wzlscheduler_interfaces::srv",  // message namespace
  "RobotFollowTrajectory_Response",  // message name
  1,  // number of fields
  sizeof(wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response),
  RobotFollowTrajectory_Response_message_member_array,  // message members
  RobotFollowTrajectory_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  RobotFollowTrajectory_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t RobotFollowTrajectory_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &RobotFollowTrajectory_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace wzlscheduler_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response>()
{
  return &::wzlscheduler_interfaces::srv::rosidl_typesupport_introspection_cpp::RobotFollowTrajectory_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, wzlscheduler_interfaces, srv, RobotFollowTrajectory_Response)() {
  return &::wzlscheduler_interfaces::srv::rosidl_typesupport_introspection_cpp::RobotFollowTrajectory_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace wzlscheduler_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers RobotFollowTrajectory_service_members = {
  "wzlscheduler_interfaces::srv",  // service namespace
  "RobotFollowTrajectory",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<wzlscheduler_interfaces::srv::RobotFollowTrajectory>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t RobotFollowTrajectory_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &RobotFollowTrajectory_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace wzlscheduler_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<wzlscheduler_interfaces::srv::RobotFollowTrajectory>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::wzlscheduler_interfaces::srv::rosidl_typesupport_introspection_cpp::RobotFollowTrajectory_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, wzlscheduler_interfaces, srv, RobotFollowTrajectory)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<wzlscheduler_interfaces::srv::RobotFollowTrajectory>();
}

#ifdef __cplusplus
}
#endif
