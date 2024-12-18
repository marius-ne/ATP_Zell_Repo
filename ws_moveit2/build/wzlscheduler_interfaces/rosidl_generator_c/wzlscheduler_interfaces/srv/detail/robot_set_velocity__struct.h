// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wzlscheduler_interfaces:srv/RobotSetVelocity.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_SET_VELOCITY__STRUCT_H_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_SET_VELOCITY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/RobotSetVelocity in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__RobotSetVelocity_Request
{
  double velocityscalingfactor;
  double accelerationscalingfactor;
  int32_t type;
} wzlscheduler_interfaces__srv__RobotSetVelocity_Request;

// Struct for a sequence of wzlscheduler_interfaces__srv__RobotSetVelocity_Request.
typedef struct wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence
{
  wzlscheduler_interfaces__srv__RobotSetVelocity_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/RobotSetVelocity in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__RobotSetVelocity_Response
{
  int32_t result;
} wzlscheduler_interfaces__srv__RobotSetVelocity_Response;

// Struct for a sequence of wzlscheduler_interfaces__srv__RobotSetVelocity_Response.
typedef struct wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence
{
  wzlscheduler_interfaces__srv__RobotSetVelocity_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_SET_VELOCITY__STRUCT_H_
