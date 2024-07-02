// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robo_planner_msgs:msg/LabeledPointClouds.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__STRUCT_H_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'elements'
#include "robo_planner_msgs/msg/detail/labeled_point_cloud__struct.h"

/// Struct defined in msg/LabeledPointClouds in the package robo_planner_msgs.
typedef struct robo_planner_msgs__msg__LabeledPointClouds
{
  robo_planner_msgs__msg__LabeledPointCloud__Sequence elements;
} robo_planner_msgs__msg__LabeledPointClouds;

// Struct for a sequence of robo_planner_msgs__msg__LabeledPointClouds.
typedef struct robo_planner_msgs__msg__LabeledPointClouds__Sequence
{
  robo_planner_msgs__msg__LabeledPointClouds * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robo_planner_msgs__msg__LabeledPointClouds__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__STRUCT_H_
