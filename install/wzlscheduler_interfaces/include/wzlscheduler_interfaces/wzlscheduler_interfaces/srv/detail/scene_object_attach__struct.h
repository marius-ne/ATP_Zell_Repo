// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from wzlscheduler_interfaces:srv/SceneObjectAttach.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ATTACH__STRUCT_H_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ATTACH__STRUCT_H_

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
// Member 'parentkey'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SceneObjectAttach in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__SceneObjectAttach_Request
{
  rosidl_runtime_c__String name;
  rosidl_runtime_c__String parentkey;
} wzlscheduler_interfaces__srv__SceneObjectAttach_Request;

// Struct for a sequence of wzlscheduler_interfaces__srv__SceneObjectAttach_Request.
typedef struct wzlscheduler_interfaces__srv__SceneObjectAttach_Request__Sequence
{
  wzlscheduler_interfaces__srv__SceneObjectAttach_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__SceneObjectAttach_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/SceneObjectAttach in the package wzlscheduler_interfaces.
typedef struct wzlscheduler_interfaces__srv__SceneObjectAttach_Response
{
  int32_t result;
} wzlscheduler_interfaces__srv__SceneObjectAttach_Response;

// Struct for a sequence of wzlscheduler_interfaces__srv__SceneObjectAttach_Response.
typedef struct wzlscheduler_interfaces__srv__SceneObjectAttach_Response__Sequence
{
  wzlscheduler_interfaces__srv__SceneObjectAttach_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} wzlscheduler_interfaces__srv__SceneObjectAttach_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ATTACH__STRUCT_H_
