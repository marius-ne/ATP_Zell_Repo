// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from robo_planner_msgs:msg/SceneObjectSetPose.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_SET_POSE__FUNCTIONS_H_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_SET_POSE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "robo_planner_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "robo_planner_msgs/msg/detail/scene_object_set_pose__struct.h"

/// Initialize msg/SceneObjectSetPose message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * robo_planner_msgs__msg__SceneObjectSetPose
 * )) before or use
 * robo_planner_msgs__msg__SceneObjectSetPose__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
bool
robo_planner_msgs__msg__SceneObjectSetPose__init(robo_planner_msgs__msg__SceneObjectSetPose * msg);

/// Finalize msg/SceneObjectSetPose message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
void
robo_planner_msgs__msg__SceneObjectSetPose__fini(robo_planner_msgs__msg__SceneObjectSetPose * msg);

/// Create msg/SceneObjectSetPose message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * robo_planner_msgs__msg__SceneObjectSetPose__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
robo_planner_msgs__msg__SceneObjectSetPose *
robo_planner_msgs__msg__SceneObjectSetPose__create();

/// Destroy msg/SceneObjectSetPose message.
/**
 * It calls
 * robo_planner_msgs__msg__SceneObjectSetPose__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
void
robo_planner_msgs__msg__SceneObjectSetPose__destroy(robo_planner_msgs__msg__SceneObjectSetPose * msg);

/// Check for msg/SceneObjectSetPose message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
bool
robo_planner_msgs__msg__SceneObjectSetPose__are_equal(const robo_planner_msgs__msg__SceneObjectSetPose * lhs, const robo_planner_msgs__msg__SceneObjectSetPose * rhs);

/// Copy a msg/SceneObjectSetPose message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
bool
robo_planner_msgs__msg__SceneObjectSetPose__copy(
  const robo_planner_msgs__msg__SceneObjectSetPose * input,
  robo_planner_msgs__msg__SceneObjectSetPose * output);

/// Initialize array of msg/SceneObjectSetPose messages.
/**
 * It allocates the memory for the number of elements and calls
 * robo_planner_msgs__msg__SceneObjectSetPose__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
bool
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__init(robo_planner_msgs__msg__SceneObjectSetPose__Sequence * array, size_t size);

/// Finalize array of msg/SceneObjectSetPose messages.
/**
 * It calls
 * robo_planner_msgs__msg__SceneObjectSetPose__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
void
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__fini(robo_planner_msgs__msg__SceneObjectSetPose__Sequence * array);

/// Create array of msg/SceneObjectSetPose messages.
/**
 * It allocates the memory for the array and calls
 * robo_planner_msgs__msg__SceneObjectSetPose__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
robo_planner_msgs__msg__SceneObjectSetPose__Sequence *
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__create(size_t size);

/// Destroy array of msg/SceneObjectSetPose messages.
/**
 * It calls
 * robo_planner_msgs__msg__SceneObjectSetPose__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
void
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__destroy(robo_planner_msgs__msg__SceneObjectSetPose__Sequence * array);

/// Check for msg/SceneObjectSetPose message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
bool
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__are_equal(const robo_planner_msgs__msg__SceneObjectSetPose__Sequence * lhs, const robo_planner_msgs__msg__SceneObjectSetPose__Sequence * rhs);

/// Copy an array of msg/SceneObjectSetPose messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_robo_planner_msgs
bool
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__copy(
  const robo_planner_msgs__msg__SceneObjectSetPose__Sequence * input,
  robo_planner_msgs__msg__SceneObjectSetPose__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_SET_POSE__FUNCTIONS_H_
