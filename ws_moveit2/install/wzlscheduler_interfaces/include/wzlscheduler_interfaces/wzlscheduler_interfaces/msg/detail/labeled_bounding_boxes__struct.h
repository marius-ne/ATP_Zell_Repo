// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wzlscheduler_interfaces:msg/LabeledBoundingBoxes.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOXES__STRUCT_H_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOXES__STRUCT_H_

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
#include "wzlscheduler_interfaces/msg/detail/labeled_bounding_box__struct.h"

/// Struct defined in msg/LabeledBoundingBoxes in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__msg__LabeledBoundingBoxes
{
  wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence elements;
} wzlscheduler_interfaces__msg__LabeledBoundingBoxes;

// Struct for a sequence of wzlscheduler_interfaces__msg__LabeledBoundingBoxes.
typedef struct wzlscheduler_interfaces__msg__LabeledBoundingBoxes__Sequence
{
  wzlscheduler_interfaces__msg__LabeledBoundingBoxes * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__msg__LabeledBoundingBoxes__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOXES__STRUCT_H_
