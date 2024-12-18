// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wzlscheduler_interfaces:msg/SceneObjectRemove.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_REMOVE__STRUCT_H_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_REMOVE__STRUCT_H_

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

/// Struct defined in msg/SceneObjectRemove in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__msg__SceneObjectRemove
{
  rosidl_runtime_c__String name;
} wzlscheduler_interfaces__msg__SceneObjectRemove;

// Struct for a sequence of wzlscheduler_interfaces__msg__SceneObjectRemove.
typedef struct wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence
{
  wzlscheduler_interfaces__msg__SceneObjectRemove * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__SCENE_OBJECT_REMOVE__STRUCT_H_
