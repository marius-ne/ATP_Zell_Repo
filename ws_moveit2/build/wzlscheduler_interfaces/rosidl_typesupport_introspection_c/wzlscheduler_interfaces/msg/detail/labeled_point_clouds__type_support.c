// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from wzlscheduler_interfaces:msg/LabeledPointClouds.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "wzlscheduler_interfaces/msg/detail/labeled_point_clouds__rosidl_typesupport_introspection_c.h"
#include "wzlscheduler_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "wzlscheduler_interfaces/msg/detail/labeled_point_clouds__functions.h"
#include "wzlscheduler_interfaces/msg/detail/labeled_point_clouds__struct.h"


// Include directives for member types
// Member `elements`
#include "wzlscheduler_interfaces/msg/labeled_point_cloud.h"
// Member `elements`
#include "wzlscheduler_interfaces/msg/detail/labeled_point_cloud__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  wzlscheduler_interfaces__msg__LabeledPointClouds__init(message_memory);
}

void wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_fini_function(void * message_memory)
{
  wzlscheduler_interfaces__msg__LabeledPointClouds__fini(message_memory);
}

size_t wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__size_function__LabeledPointClouds__elements(
  const void * untyped_member)
{
  const wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * member =
    (const wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence *)(untyped_member);
  return member->size;
}

const void * wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_const_function__LabeledPointClouds__elements(
  const void * untyped_member, size_t index)
{
  const wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * member =
    (const wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence *)(untyped_member);
  return &member->data[index];
}

void * wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_function__LabeledPointClouds__elements(
  void * untyped_member, size_t index)
{
  wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * member =
    (wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence *)(untyped_member);
  return &member->data[index];
}

void wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__fetch_function__LabeledPointClouds__elements(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const wzlscheduler_interfaces__msg__LabeledPointCloud * item =
    ((const wzlscheduler_interfaces__msg__LabeledPointCloud *)
    wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_const_function__LabeledPointClouds__elements(untyped_member, index));
  wzlscheduler_interfaces__msg__LabeledPointCloud * value =
    (wzlscheduler_interfaces__msg__LabeledPointCloud *)(untyped_value);
  *value = *item;
}

void wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__assign_function__LabeledPointClouds__elements(
  void * untyped_member, size_t index, const void * untyped_value)
{
  wzlscheduler_interfaces__msg__LabeledPointCloud * item =
    ((wzlscheduler_interfaces__msg__LabeledPointCloud *)
    wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_function__LabeledPointClouds__elements(untyped_member, index));
  const wzlscheduler_interfaces__msg__LabeledPointCloud * value =
    (const wzlscheduler_interfaces__msg__LabeledPointCloud *)(untyped_value);
  *item = *value;
}

bool wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__resize_function__LabeledPointClouds__elements(
  void * untyped_member, size_t size)
{
  wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * member =
    (wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence *)(untyped_member);
  wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__fini(member);
  return wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_member_array[1] = {
  {
    "elements",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces__msg__LabeledPointClouds, elements),  // bytes offset in struct
    NULL,  // default value
    wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__size_function__LabeledPointClouds__elements,  // size() function pointer
    wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_const_function__LabeledPointClouds__elements,  // get_const(index) function pointer
    wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_function__LabeledPointClouds__elements,  // get(index) function pointer
    wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__fetch_function__LabeledPointClouds__elements,  // fetch(index, &value) function pointer
    wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__assign_function__LabeledPointClouds__elements,  // assign(index, value) function pointer
    wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__resize_function__LabeledPointClouds__elements  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_members = {
  "wzlscheduler_interfaces__msg",  // message namespace
  "LabeledPointClouds",  // message name
  1,  // number of fields
  sizeof(wzlscheduler_interfaces__msg__LabeledPointClouds),
  wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_member_array,  // message members
  wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_init_function,  // function to initialize message memory (memory has to be allocated)
  wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_type_support_handle = {
  0,
  &wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_wzlscheduler_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, msg, LabeledPointClouds)() {
  wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, msg, LabeledPointCloud)();
  if (!wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_type_support_handle.typesupport_identifier) {
    wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &wzlscheduler_interfaces__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
