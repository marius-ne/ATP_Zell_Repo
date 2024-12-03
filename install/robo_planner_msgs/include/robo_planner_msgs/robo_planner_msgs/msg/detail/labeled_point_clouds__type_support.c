// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from robo_planner_msgs:msg/LabeledPointClouds.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "robo_planner_msgs/msg/detail/labeled_point_clouds__rosidl_typesupport_introspection_c.h"
#include "robo_planner_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "robo_planner_msgs/msg/detail/labeled_point_clouds__functions.h"
#include "robo_planner_msgs/msg/detail/labeled_point_clouds__struct.h"


// Include directives for member types
// Member `elements`
#include "robo_planner_msgs/msg/labeled_point_cloud.h"
// Member `elements`
#include "robo_planner_msgs/msg/detail/labeled_point_cloud__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  robo_planner_msgs__msg__LabeledPointClouds__init(message_memory);
}

void robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_fini_function(void * message_memory)
{
  robo_planner_msgs__msg__LabeledPointClouds__fini(message_memory);
}

size_t robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__size_function__LabeledPointClouds__elements(
  const void * untyped_member)
{
  const robo_planner_msgs__msg__LabeledPointCloud__Sequence * member =
    (const robo_planner_msgs__msg__LabeledPointCloud__Sequence *)(untyped_member);
  return member->size;
}

const void * robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_const_function__LabeledPointClouds__elements(
  const void * untyped_member, size_t index)
{
  const robo_planner_msgs__msg__LabeledPointCloud__Sequence * member =
    (const robo_planner_msgs__msg__LabeledPointCloud__Sequence *)(untyped_member);
  return &member->data[index];
}

void * robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_function__LabeledPointClouds__elements(
  void * untyped_member, size_t index)
{
  robo_planner_msgs__msg__LabeledPointCloud__Sequence * member =
    (robo_planner_msgs__msg__LabeledPointCloud__Sequence *)(untyped_member);
  return &member->data[index];
}

void robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__fetch_function__LabeledPointClouds__elements(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const robo_planner_msgs__msg__LabeledPointCloud * item =
    ((const robo_planner_msgs__msg__LabeledPointCloud *)
    robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_const_function__LabeledPointClouds__elements(untyped_member, index));
  robo_planner_msgs__msg__LabeledPointCloud * value =
    (robo_planner_msgs__msg__LabeledPointCloud *)(untyped_value);
  *value = *item;
}

void robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__assign_function__LabeledPointClouds__elements(
  void * untyped_member, size_t index, const void * untyped_value)
{
  robo_planner_msgs__msg__LabeledPointCloud * item =
    ((robo_planner_msgs__msg__LabeledPointCloud *)
    robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_function__LabeledPointClouds__elements(untyped_member, index));
  const robo_planner_msgs__msg__LabeledPointCloud * value =
    (const robo_planner_msgs__msg__LabeledPointCloud *)(untyped_value);
  *item = *value;
}

bool robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__resize_function__LabeledPointClouds__elements(
  void * untyped_member, size_t size)
{
  robo_planner_msgs__msg__LabeledPointCloud__Sequence * member =
    (robo_planner_msgs__msg__LabeledPointCloud__Sequence *)(untyped_member);
  robo_planner_msgs__msg__LabeledPointCloud__Sequence__fini(member);
  return robo_planner_msgs__msg__LabeledPointCloud__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_member_array[1] = {
  {
    "elements",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robo_planner_msgs__msg__LabeledPointClouds, elements),  // bytes offset in struct
    NULL,  // default value
    robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__size_function__LabeledPointClouds__elements,  // size() function pointer
    robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_const_function__LabeledPointClouds__elements,  // get_const(index) function pointer
    robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__get_function__LabeledPointClouds__elements,  // get(index) function pointer
    robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__fetch_function__LabeledPointClouds__elements,  // fetch(index, &value) function pointer
    robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__assign_function__LabeledPointClouds__elements,  // assign(index, value) function pointer
    robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__resize_function__LabeledPointClouds__elements  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_members = {
  "robo_planner_msgs__msg",  // message namespace
  "LabeledPointClouds",  // message name
  1,  // number of fields
  sizeof(robo_planner_msgs__msg__LabeledPointClouds),
  robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_member_array,  // message members
  robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_init_function,  // function to initialize message memory (memory has to be allocated)
  robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_type_support_handle = {
  0,
  &robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robo_planner_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robo_planner_msgs, msg, LabeledPointClouds)() {
  robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robo_planner_msgs, msg, LabeledPointCloud)();
  if (!robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_type_support_handle.typesupport_identifier) {
    robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &robo_planner_msgs__msg__LabeledPointClouds__rosidl_typesupport_introspection_c__LabeledPointClouds_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
