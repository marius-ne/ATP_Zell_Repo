// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from robo_planner_msgs:msg/SceneObjectSetPose.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "robo_planner_msgs/msg/detail/scene_object_set_pose__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace robo_planner_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void SceneObjectSetPose_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) robo_planner_msgs::msg::SceneObjectSetPose(_init);
}

void SceneObjectSetPose_fini_function(void * message_memory)
{
  auto typed_message = static_cast<robo_planner_msgs::msg::SceneObjectSetPose *>(message_memory);
  typed_message->~SceneObjectSetPose();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SceneObjectSetPose_message_member_array[2] = {
  {
    "name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robo_planner_msgs::msg::SceneObjectSetPose, name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "coordinates",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<geometry_msgs::msg::Pose>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robo_planner_msgs::msg::SceneObjectSetPose, coordinates),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SceneObjectSetPose_message_members = {
  "robo_planner_msgs::msg",  // message namespace
  "SceneObjectSetPose",  // message name
  2,  // number of fields
  sizeof(robo_planner_msgs::msg::SceneObjectSetPose),
  SceneObjectSetPose_message_member_array,  // message members
  SceneObjectSetPose_init_function,  // function to initialize message memory (memory has to be allocated)
  SceneObjectSetPose_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SceneObjectSetPose_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SceneObjectSetPose_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace robo_planner_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robo_planner_msgs::msg::SceneObjectSetPose>()
{
  return &::robo_planner_msgs::msg::rosidl_typesupport_introspection_cpp::SceneObjectSetPose_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robo_planner_msgs, msg, SceneObjectSetPose)() {
  return &::robo_planner_msgs::msg::rosidl_typesupport_introspection_cpp::SceneObjectSetPose_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
