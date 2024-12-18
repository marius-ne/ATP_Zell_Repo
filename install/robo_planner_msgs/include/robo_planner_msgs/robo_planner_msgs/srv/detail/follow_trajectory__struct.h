// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robo_planner_msgs:srv/FollowTrajectory.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__SRV__DETAIL__FOLLOW_TRAJECTORY__STRUCT_H_
#define ROBO_PLANNER_MSGS__SRV__DETAIL__FOLLOW_TRAJECTORY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'supportpoints'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in srv/FollowTrajectory in the package robo_planner_msgs.
typedef struct robo_planner_msgs__srv__FollowTrajectory_Request
{
  geometry_msgs__msg__Pose__Sequence supportpoints;
  double value;
} robo_planner_msgs__srv__FollowTrajectory_Request;

// Struct for a sequence of robo_planner_msgs__srv__FollowTrajectory_Request.
typedef struct robo_planner_msgs__srv__FollowTrajectory_Request__Sequence
{
  robo_planner_msgs__srv__FollowTrajectory_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robo_planner_msgs__srv__FollowTrajectory_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/FollowTrajectory in the package robo_planner_msgs.
typedef struct robo_planner_msgs__srv__FollowTrajectory_Response
{
  int32_t result;
} robo_planner_msgs__srv__FollowTrajectory_Response;

// Struct for a sequence of robo_planner_msgs__srv__FollowTrajectory_Response.
typedef struct robo_planner_msgs__srv__FollowTrajectory_Response__Sequence
{
  robo_planner_msgs__srv__FollowTrajectory_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robo_planner_msgs__srv__FollowTrajectory_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBO_PLANNER_MSGS__SRV__DETAIL__FOLLOW_TRAJECTORY__STRUCT_H_
