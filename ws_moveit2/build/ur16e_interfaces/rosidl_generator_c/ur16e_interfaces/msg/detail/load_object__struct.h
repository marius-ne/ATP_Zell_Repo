// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ur16e_interfaces:msg/LoadObject.idl
// generated code does not contain a copyright notice

#ifndef UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__STRUCT_H_
#define UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__STRUCT_H_

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
// Member 'coordinates'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in msg/LoadObject in the package ur16e_interfaces.
typedef struct ur16e_interfaces__msg__LoadObject
{
  rosidl_runtime_c__String name;
  geometry_msgs__msg__Pose coordinates;
  double scale;
} ur16e_interfaces__msg__LoadObject;

// Struct for a sequence of ur16e_interfaces__msg__LoadObject.
typedef struct ur16e_interfaces__msg__LoadObject__Sequence
{
  ur16e_interfaces__msg__LoadObject * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur16e_interfaces__msg__LoadObject__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__STRUCT_H_
