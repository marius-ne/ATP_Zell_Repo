// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robo_planner_msgs:srv/GripperChangePick.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE_PICK__STRUCT_H_
#define ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE_PICK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GripperChangePick in the package robo_planner_msgs.
typedef struct robo_planner_msgs__srv__GripperChangePick_Request
{
  uint8_t structure_needs_at_least_one_member;
} robo_planner_msgs__srv__GripperChangePick_Request;

// Struct for a sequence of robo_planner_msgs__srv__GripperChangePick_Request.
typedef struct robo_planner_msgs__srv__GripperChangePick_Request__Sequence
{
  robo_planner_msgs__srv__GripperChangePick_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robo_planner_msgs__srv__GripperChangePick_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/GripperChangePick in the package robo_planner_msgs.
typedef struct robo_planner_msgs__srv__GripperChangePick_Response
{
  int32_t result;
} robo_planner_msgs__srv__GripperChangePick_Response;

// Struct for a sequence of robo_planner_msgs__srv__GripperChangePick_Response.
typedef struct robo_planner_msgs__srv__GripperChangePick_Response__Sequence
{
  robo_planner_msgs__srv__GripperChangePick_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robo_planner_msgs__srv__GripperChangePick_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE_PICK__STRUCT_H_
