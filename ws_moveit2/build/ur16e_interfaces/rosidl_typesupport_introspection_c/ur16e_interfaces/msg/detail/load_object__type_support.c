// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ur16e_interfaces:msg/LoadObject.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ur16e_interfaces/msg/detail/load_object__rosidl_typesupport_introspection_c.h"
#include "ur16e_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ur16e_interfaces/msg/detail/load_object__functions.h"
#include "ur16e_interfaces/msg/detail/load_object__struct.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"
// Member `coordinates`
#include "geometry_msgs/msg/pose.h"
// Member `coordinates`
#include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ur16e_interfaces__msg__LoadObject__init(message_memory);
}

void ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_fini_function(void * message_memory)
{
  ur16e_interfaces__msg__LoadObject__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_message_member_array[3] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ur16e_interfaces__msg__LoadObject, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "coordinates",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ur16e_interfaces__msg__LoadObject, coordinates),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "scale",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ur16e_interfaces__msg__LoadObject, scale),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_message_members = {
  "ur16e_interfaces__msg",  // message namespace
  "LoadObject",  // message name
  3,  // number of fields
  sizeof(ur16e_interfaces__msg__LoadObject),
  ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_message_member_array,  // message members
  ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_init_function,  // function to initialize message memory (memory has to be allocated)
  ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_message_type_support_handle = {
  0,
  &ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ur16e_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ur16e_interfaces, msg, LoadObject)() {
  ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  if (!ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_message_type_support_handle.typesupport_identifier) {
    ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ur16e_interfaces__msg__LoadObject__rosidl_typesupport_introspection_c__LoadObject_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
