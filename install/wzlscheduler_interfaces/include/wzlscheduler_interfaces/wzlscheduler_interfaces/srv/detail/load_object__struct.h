// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wzlscheduler_interfaces:srv/LoadObject.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__LOAD_OBJECT__STRUCT_H_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__LOAD_OBJECT__STRUCT_H_

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

/// Struct defined in srv/LoadObject in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__LoadObject_Request
{
  rosidl_runtime_c__String name;
  geometry_msgs__msg__Pose coordinates;
  double scale;
} wzlscheduler_interfaces__srv__LoadObject_Request;

// Struct for a sequence of wzlscheduler_interfaces__srv__LoadObject_Request.
typedef struct wzlscheduler_interfaces__srv__LoadObject_Request__Sequence
{
  wzlscheduler_interfaces__srv__LoadObject_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__LoadObject_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/LoadObject in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__LoadObject_Response
{
  int32_t result;
} wzlscheduler_interfaces__srv__LoadObject_Response;

// Struct for a sequence of wzlscheduler_interfaces__srv__LoadObject_Response.
typedef struct wzlscheduler_interfaces__srv__LoadObject_Response__Sequence
{
  wzlscheduler_interfaces__srv__LoadObject_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__LoadObject_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__LOAD_OBJECT__STRUCT_H_
