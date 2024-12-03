// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from wzlscheduler_interfaces:msg/LabeledPoses.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__FUNCTIONS_H_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "wzlscheduler_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "wzlscheduler_interfaces/msg/detail/labeled_poses__struct.h"

/// Initialize msg/LabeledPoses message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * wzlscheduler_interfaces__msg__LabeledPoses
 * )) before or use
 * wzlscheduler_interfaces__msg__LabeledPoses__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
bool
wzlscheduler_interfaces__msg__LabeledPoses__init(wzlscheduler_interfaces__msg__LabeledPoses * msg);

/// Finalize msg/LabeledPoses message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
void
wzlscheduler_interfaces__msg__LabeledPoses__fini(wzlscheduler_interfaces__msg__LabeledPoses * msg);

/// Create msg/LabeledPoses message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * wzlscheduler_interfaces__msg__LabeledPoses__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
wzlscheduler_interfaces__msg__LabeledPoses *
wzlscheduler_interfaces__msg__LabeledPoses__create();

/// Destroy msg/LabeledPoses message.
/**
 * It calls
 * wzlscheduler_interfaces__msg__LabeledPoses__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
void
wzlscheduler_interfaces__msg__LabeledPoses__destroy(wzlscheduler_interfaces__msg__LabeledPoses * msg);

/// Check for msg/LabeledPoses message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
bool
wzlscheduler_interfaces__msg__LabeledPoses__are_equal(const wzlscheduler_interfaces__msg__LabeledPoses * lhs, const wzlscheduler_interfaces__msg__LabeledPoses * rhs);

/// Copy a msg/LabeledPoses message.
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
wzlscheduler_interfaces__msg__LabeledPoses__copy(
  const wzlscheduler_interfaces__msg__LabeledPoses * input,
  wzlscheduler_interfaces__msg__LabeledPoses * output);

/// Initialize array of msg/LabeledPoses messages.
/**
 * It allocates the memory for the number of elements and calls
 * wzlscheduler_interfaces__msg__LabeledPoses__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
bool
wzlscheduler_interfaces__msg__LabeledPoses__Sequence__init(wzlscheduler_interfaces__msg__LabeledPoses__Sequence * array, size_t size);

/// Finalize array of msg/LabeledPoses messages.
/**
 * It calls
 * wzlscheduler_interfaces__msg__LabeledPoses__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
void
wzlscheduler_interfaces__msg__LabeledPoses__Sequence__fini(wzlscheduler_interfaces__msg__LabeledPoses__Sequence * array);

/// Create array of msg/LabeledPoses messages.
/**
 * It allocates the memory for the array and calls
 * wzlscheduler_interfaces__msg__LabeledPoses__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
wzlscheduler_interfaces__msg__LabeledPoses__Sequence *
wzlscheduler_interfaces__msg__LabeledPoses__Sequence__create(size_t size);

/// Destroy array of msg/LabeledPoses messages.
/**
 * It calls
 * wzlscheduler_interfaces__msg__LabeledPoses__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
void
wzlscheduler_interfaces__msg__LabeledPoses__Sequence__destroy(wzlscheduler_interfaces__msg__LabeledPoses__Sequence * array);

/// Check for msg/LabeledPoses message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_wzlscheduler_interfaces
bool
wzlscheduler_interfaces__msg__LabeledPoses__Sequence__are_equal(const wzlscheduler_interfaces__msg__LabeledPoses__Sequence * lhs, const wzlscheduler_interfaces__msg__LabeledPoses__Sequence * rhs);

/// Copy an array of msg/LabeledPoses messages.
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
wzlscheduler_interfaces__msg__LabeledPoses__Sequence__copy(
  const wzlscheduler_interfaces__msg__LabeledPoses__Sequence * input,
  wzlscheduler_interfaces__msg__LabeledPoses__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__FUNCTIONS_H_
