// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from opcua_interfaces:msg/ActuatorWrite.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "opcua_interfaces/msg/detail/actuator_write__rosidl_typesupport_introspection_c.h"
#include "opcua_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "opcua_interfaces/msg/detail/actuator_write__functions.h"
#include "opcua_interfaces/msg/detail/actuator_write__struct.h"


// Include directives for member types
// Member `actuator_id`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  opcua_interfaces__msg__ActuatorWrite__init(message_memory);
}

void opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_fini_function(void * message_memory)
{
  opcua_interfaces__msg__ActuatorWrite__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_message_member_array[4] = {
  {
    "actuator_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(opcua_interfaces__msg__ActuatorWrite, actuator_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "actuator_write_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(opcua_interfaces__msg__ActuatorWrite, actuator_write_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "actuator_command_bool1",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(opcua_interfaces__msg__ActuatorWrite, actuator_command_bool1),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "actuator_command_bool2",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(opcua_interfaces__msg__ActuatorWrite, actuator_command_bool2),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_message_members = {
  "opcua_interfaces__msg",  // message namespace
  "ActuatorWrite",  // message name
  4,  // number of fields
  sizeof(opcua_interfaces__msg__ActuatorWrite),
  opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_message_member_array,  // message members
  opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_init_function,  // function to initialize message memory (memory has to be allocated)
  opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_message_type_support_handle = {
  0,
  &opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_opcua_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, opcua_interfaces, msg, ActuatorWrite)() {
  if (!opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_message_type_support_handle.typesupport_identifier) {
    opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &opcua_interfaces__msg__ActuatorWrite__rosidl_typesupport_introspection_c__ActuatorWrite_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
