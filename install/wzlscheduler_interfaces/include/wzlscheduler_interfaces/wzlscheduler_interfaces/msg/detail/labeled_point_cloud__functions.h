// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from wzlscheduler_interfaces:msg/LabeledPointCloud.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__FUNCTIONS_H_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "wzlscheduler_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "wzlscheduler_interfaces/msg/detail/labeled_point_cloud__struct.h"

/// Initialize msg/LabeledPointCloud message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * wzlscheduler_interfaces__msg__LabeledPointCloud
 * )) before or use
 * wzlscheduler_interfaces__msg__LabeledPointCloud__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
bool
wzlscheduler_interfaces__msg__LabeledPointCloud__init(wzlscheduler_interfaces__msg__LabeledPointCloud * msg);

/// Finalize msg/LabeledPointCloud message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
void
wzlscheduler_interfaces__msg__LabeledPointCloud__fini(wzlscheduler_interfaces__msg__LabeledPointCloud * msg);

/// Create msg/LabeledPointCloud message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * wzlscheduler_interfaces__msg__LabeledPointCloud__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
wzlscheduler_interfaces__msg__LabeledPointCloud *
wzlscheduler_interfaces__msg__LabeledPointCloud__create();

/// Destroy msg/LabeledPointCloud message.
/**
 * It calls
 * wzlscheduler_interfaces__msg__LabeledPointCloud__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
void
wzlscheduler_interfaces__msg__LabeledPointCloud__destroy(wzlscheduler_interfaces__msg__LabeledPointCloud * msg);

/// Check for msg/LabeledPointCloud message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
bool
wzlscheduler_interfaces__msg__LabeledPointCloud__are_equal(const wzlscheduler_interfaces__msg__LabeledPointCloud * lhs, const wzlscheduler_interfaces__msg__LabeledPointCloud * rhs);

/// Copy a msg/LabeledPointCloud message.
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
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
bool
wzlscheduler_interfaces__msg__LabeledPointCloud__copy(
  const wzlscheduler_interfaces__msg__LabeledPointCloud * input,
  wzlscheduler_interfaces__msg__LabeledPointCloud * output);

/// Initialize array of msg/LabeledPointCloud messages.
/**
 * It allocates the memory for the number of elements and calls
 * wzlscheduler_interfaces__msg__LabeledPointCloud__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
bool
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__init(wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * array, size_t size);

/// Finalize array of msg/LabeledPointCloud messages.
/**
 * It calls
 * wzlscheduler_interfaces__msg__LabeledPointCloud__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
void
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__fini(wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * array);

/// Create array of msg/LabeledPointCloud messages.
/**
 * It allocates the memory for the array and calls
 * wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence *
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__create(size_t size);

/// Destroy array of msg/LabeledPointCloud messages.
/**
 * It calls
 * wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
void
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__destroy(wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * array);

/// Check for msg/LabeledPointCloud message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
bool
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__are_equal(const wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * lhs, const wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * rhs);

/// Copy an array of msg/LabeledPointCloud messages.
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
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
bool
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__copy(
  const wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * input,
  wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__FUNCTIONS_H_
