// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from wzlscheduler_interfaces:msg/SceneObjectRemove.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "wzlscheduler_interfaces/msg/detail/scene_object_remove__rosidl_typesupport_introspection_c.h"
#include "wzlscheduler_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "wzlscheduler_interfaces/msg/detail/scene_object_remove__functions.h"
#include "wzlscheduler_interfaces/msg/detail/scene_object_remove__struct.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  wzlscheduler_interfaces__msg__SceneObjectRemove__init(message_memory);
}

void wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_fini_function(void * message_memory)
{
  wzlscheduler_interfaces__msg__SceneObjectRemove__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_message_member_array[1] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces__msg__SceneObjectRemove, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_message_members = {
  "wzlscheduler_interfaces__msg",  // message namespace
  "SceneObjectRemove",  // message name
  1,  // number of fields
  sizeof(wzlscheduler_interfaces__msg__SceneObjectRemove),
  wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_message_member_array,  // message members
  wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_init_function,  // function to initialize message memory (memory has to be allocated)
  wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_message_type_support_handle = {
  0,
  &wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_wzlscheduler_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, msg, SceneObjectRemove)() {
  if (!wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_message_type_support_handle.typesupport_identifier) {
    wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &wzlscheduler_interfaces__msg__SceneObjectRemove__rosidl_typesupport_introspection_c__SceneObjectRemove_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
