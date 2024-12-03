// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wzlscheduler_interfaces:srv/SceneObjectDetach.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_DETACH__STRUCT_H_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_DETACH__STRUCT_H_

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

/// Struct defined in srv/SceneObjectDetach in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__SceneObjectDetach_Request
{
  rosidl_runtime_c__String name;
} wzlscheduler_interfaces__srv__SceneObjectDetach_Request;

// Struct for a sequence of wzlscheduler_interfaces__srv__SceneObjectDetach_Request.
typedef struct wzlscheduler_interfaces__srv__SceneObjectDetach_Request__Sequence
{
  wzlscheduler_interfaces__srv__SceneObjectDetach_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__SceneObjectDetach_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'name'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'coordinates'
#include "geometry_msgs/msg/detail/pose__struct.h"

/// Struct defined in srv/SceneObjectDetach in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__SceneObjectDetach_Response
{
  int32_t result;
  rosidl_runtime_c__String name;
  geometry_msgs__msg__Pose coordinates;
} wzlscheduler_interfaces__srv__SceneObjectDetach_Response;

// Struct for a sequence of wzlscheduler_interfaces__srv__SceneObjectDetach_Response.
typedef struct wzlscheduler_interfaces__srv__SceneObjectDetach_Response__Sequence
{
  wzlscheduler_interfaces__srv__SceneObjectDetach_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__SceneObjectDetach_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_DETACH__STRUCT_H_
