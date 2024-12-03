// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robo_planner_msgs:msg/SceneObjectAdd.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_ADD__STRUCT_H_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_ADD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
// Member 'collisionobjectkey'
#include "rosidl_runtime_c/string.h"
// Member 'coordinates'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in msg/SceneObjectAdd in the package robo_planner_msgs.
typedef struct robo_planner_msgs__msg__SceneObjectAdd
{
  rosidl_runtime_c__String name;
  rosidl_runtime_c__String collisionobjectkey;
  geometry_msgs__msg__Pose coordinates;
} robo_planner_msgs__msg__SceneObjectAdd;

// Struct for a sequence of robo_planner_msgs__msg__SceneObjectAdd.
typedef struct robo_planner_msgs__msg__SceneObjectAdd__Sequence
{
  robo_planner_msgs__msg__SceneObjectAdd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robo_planner_msgs__msg__SceneObjectAdd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_ADD__STRUCT_H_
