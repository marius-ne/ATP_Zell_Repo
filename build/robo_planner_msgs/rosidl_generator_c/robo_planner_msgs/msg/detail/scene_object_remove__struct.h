// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robo_planner_msgs:msg/SceneObjectRemove.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_REMOVE__STRUCT_H_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_REMOVE__STRUCT_H_

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
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/SceneObjectRemove in the package robo_planner_msgs.
typedef struct robo_planner_msgs__msg__SceneObjectRemove
{
  rosidl_runtime_c__String name;
} robo_planner_msgs__msg__SceneObjectRemove;

// Struct for a sequence of robo_planner_msgs__msg__SceneObjectRemove.
typedef struct robo_planner_msgs__msg__SceneObjectRemove__Sequence
{
  robo_planner_msgs__msg__SceneObjectRemove * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robo_planner_msgs__msg__SceneObjectRemove__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_REMOVE__STRUCT_H_
