// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wzlscheduler_interfaces:srv/RobotMoveToPosition.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__STRUCT_H_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in srv/RobotMoveToPosition in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__RobotMoveToPosition_Request
{
  int32_t movetype;
  geometry_msgs__msg__Pose pose;
} wzlscheduler_interfaces__srv__RobotMoveToPosition_Request;

// Struct for a sequence of wzlscheduler_interfaces__srv__RobotMoveToPosition_Request.
typedef struct wzlscheduler_interfaces__srv__RobotMoveToPosition_Request__Sequence
{
  wzlscheduler_interfaces__srv__RobotMoveToPosition_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__RobotMoveToPosition_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/RobotMoveToPosition in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__RobotMoveToPosition_Response
{
  int32_t result;
} wzlscheduler_interfaces__srv__RobotMoveToPosition_Response;

// Struct for a sequence of wzlscheduler_interfaces__srv__RobotMoveToPosition_Response.
typedef struct wzlscheduler_interfaces__srv__RobotMoveToPosition_Response__Sequence
{
  wzlscheduler_interfaces__srv__RobotMoveToPosition_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__RobotMoveToPosition_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__STRUCT_H_
