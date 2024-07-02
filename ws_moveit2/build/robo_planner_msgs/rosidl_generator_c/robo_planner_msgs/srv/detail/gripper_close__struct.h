// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robo_planner_msgs:srv/GripperClose.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CLOSE__STRUCT_H_
#define ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CLOSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GripperClose in the package robo_planner_msgs.
typedef struct robo_planner_msgs__srv__GripperClose_Request
{
  int32_t dummyinput;
} robo_planner_msgs__srv__GripperClose_Request;

// Struct for a sequence of robo_planner_msgs__srv__GripperClose_Request.
typedef struct robo_planner_msgs__srv__GripperClose_Request__Sequence
{
  robo_planner_msgs__srv__GripperClose_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robo_planner_msgs__srv__GripperClose_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/GripperClose in the package robo_planner_msgs.
typedef struct robo_planner_msgs__srv__GripperClose_Response
{
  int32_t result;
} robo_planner_msgs__srv__GripperClose_Response;

// Struct for a sequence of robo_planner_msgs__srv__GripperClose_Response.
typedef struct robo_planner_msgs__srv__GripperClose_Response__Sequence
{
  robo_planner_msgs__srv__GripperClose_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robo_planner_msgs__srv__GripperClose_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CLOSE__STRUCT_H_
