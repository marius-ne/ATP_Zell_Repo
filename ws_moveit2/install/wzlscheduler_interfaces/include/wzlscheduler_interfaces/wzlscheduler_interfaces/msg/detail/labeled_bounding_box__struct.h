// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wzlscheduler_interfaces:msg/LabeledBoundingBox.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOX__STRUCT_H_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOX__STRUCT_H_

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

/// Struct defined in msg/LabeledBoundingBox in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__msg__LabeledBoundingBox
{
  rosidl_runtime_c__String label;
  int32_t x;
  int32_t y;
  int32_t width;
  int32_t height;
} wzlscheduler_interfaces__msg__LabeledBoundingBox;

// Struct for a sequence of wzlscheduler_interfaces__msg__LabeledBoundingBox.
typedef struct wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence
{
  wzlscheduler_interfaces__msg__LabeledBoundingBox * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOX__STRUCT_H_
