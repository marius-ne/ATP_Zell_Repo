// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wzlscheduler_interfaces:srv/SceneObjectAdd.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ADD__STRUCT_H_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ADD__STRUCT_H_

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

/// Struct defined in srv/SceneObjectAdd in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__SceneObjectAdd_Request
{
  rosidl_runtime_c__String name;
  rosidl_runtime_c__String collisionobjectkey;
  geometry_msgs__msg__Pose coordinates;
} wzlscheduler_interfaces__srv__SceneObjectAdd_Request;

// Struct for a sequence of wzlscheduler_interfaces__srv__SceneObjectAdd_Request.
typedef struct wzlscheduler_interfaces__srv__SceneObjectAdd_Request__Sequence
{
  wzlscheduler_interfaces__srv__SceneObjectAdd_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__SceneObjectAdd_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/SceneObjectAdd in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__SceneObjectAdd_Response
{
  int32_t result;
} wzlscheduler_interfaces__srv__SceneObjectAdd_Response;

// Struct for a sequence of wzlscheduler_interfaces__srv__SceneObjectAdd_Response.
typedef struct wzlscheduler_interfaces__srv__SceneObjectAdd_Response__Sequence
{
  wzlscheduler_interfaces__srv__SceneObjectAdd_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__SceneObjectAdd_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ADD__STRUCT_H_
