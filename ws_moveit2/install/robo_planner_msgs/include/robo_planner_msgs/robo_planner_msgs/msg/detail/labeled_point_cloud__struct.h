// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robo_planner_msgs:msg/LabeledPointCloud.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUD__STRUCT_H_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'label'
#include "rosidl_runtime_c/string.h"
// Member 'poseorigin'
// Member 'posecad'
#include "geometry_msgs/msg/detail/pose__struct.h"
// Member 'pointcloud'
#include "sensor_msgs/msg/detail/point_cloud2__struct.h"

/// Struct defined in msg/LabeledPointCloud in the package robo_planner_msgs.
typedef struct robo_planner_msgs__msg__LabeledPointCloud
{
  rosidl_runtime_c__String label;
  geometry_msgs__msg__Pose poseorigin;
  geometry_msgs__msg__Pose posecad;
  sensor_msgs__msg__PointCloud2 pointcloud;
} robo_planner_msgs__msg__LabeledPointCloud;

// Struct for a sequence of robo_planner_msgs__msg__LabeledPointCloud.
typedef struct robo_planner_msgs__msg__LabeledPointCloud__Sequence
{
  robo_planner_msgs__msg__LabeledPointCloud * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robo_planner_msgs__msg__LabeledPointCloud__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUD__STRUCT_H_
