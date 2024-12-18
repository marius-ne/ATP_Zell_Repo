// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from opcua_interfaces:msg/ActuatorRead.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "opcua_interfaces/msg/detail/actuator_read__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace opcua_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ActuatorRead_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) opcua_interfaces::msg::ActuatorRead(_init);
}

void ActuatorRead_fini_function(void * message_memory)
{
  auto typed_message = static_cast<opcua_interfaces::msg::ActuatorRead *>(message_memory);
  typed_message->~ActuatorRead();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ActuatorRead_message_member_array[4] = {
  {
    "actuator_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(opcua_interfaces::msg::ActuatorRead, actuator_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "actuator_read_type",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(opcua_interfaces::msg::ActuatorRead, actuator_read_type),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "actuator_value_bool",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(opcua_interfaces::msg::ActuatorRead, actuator_value_bool),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "actuator_value_int",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(opcua_interfaces::msg::ActuatorRead, actuator_value_int),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ActuatorRead_message_members = {
  "opcua_interfaces::msg",  // message namespace
  "ActuatorRead",  // message name
  4,  // number of fields
  sizeof(opcua_interfaces::msg::ActuatorRead),
  ActuatorRead_message_member_array,  // message members
  ActuatorRead_init_function,  // function to initialize message memory (memory has to be allocated)
  ActuatorRead_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ActuatorRead_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ActuatorRead_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace opcua_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<opcua_interfaces::msg::ActuatorRead>()
{
  return &::opcua_interfaces::msg::rosidl_typesupport_introspection_cpp::ActuatorRead_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, opcua_interfaces, msg, ActuatorRead)() {
  return &::opcua_interfaces::msg::rosidl_typesupport_introspection_cpp::ActuatorRead_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
