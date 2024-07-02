// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wzlscheduler_interfaces:msg/LabeledPointClouds.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUDS__STRUCT_H_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUDS__STRUCT_H_

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
#include "wzlscheduler_interfaces/msg/detail/labeled_point_cloud__struct.h"

/// Struct defined in msg/LabeledPointClouds in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__msg__LabeledPointClouds
{
  wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence elements;
} wzlscheduler_interfaces__msg__LabeledPointClouds;

// Struct for a sequence of wzlscheduler_interfaces__msg__LabeledPointClouds.
typedef struct wzlscheduler_interfaces__msg__LabeledPointClouds__Sequence
{
  wzlscheduler_interfaces__msg__LabeledPointClouds * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__msg__LabeledPointClouds__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUDS__STRUCT_H_
