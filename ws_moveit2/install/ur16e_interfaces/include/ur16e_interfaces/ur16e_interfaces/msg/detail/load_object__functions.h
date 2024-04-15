// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from ur16e_interfaces:msg/LoadObject.idl
// generated code does not contain a copyright notice

#ifndef UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__FUNCTIONS_H_
#define UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "ur16e_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "ur16e_interfaces/msg/detail/load_object__struct.h"

/// Initialize msg/LoadObject message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur16e_interfaces__msg__LoadObject
 * )) before or use
 * ur16e_interfaces__msg__LoadObject__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
bool
ur16e_interfaces__msg__LoadObject__init(ur16e_interfaces__msg__LoadObject * msg);

/// Finalize msg/LoadObject message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
void
ur16e_interfaces__msg__LoadObject__fini(ur16e_interfaces__msg__LoadObject * msg);

/// Create msg/LoadObject message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur16e_interfaces__msg__LoadObject__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
ur16e_interfaces__msg__LoadObject *
ur16e_interfaces__msg__LoadObject__create();

/// Destroy msg/LoadObject message.
/**
 * It calls
 * ur16e_interfaces__msg__LoadObject__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
void
ur16e_interfaces__msg__LoadObject__destroy(ur16e_interfaces__msg__LoadObject * msg);

/// Check for msg/LoadObject message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
bool
ur16e_interfaces__msg__LoadObject__are_equal(const ur16e_interfaces__msg__LoadObject * lhs, const ur16e_interfaces__msg__LoadObject * rhs);

/// Copy a msg/LoadObject message.
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
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
bool
ur16e_interfaces__msg__LoadObject__copy(
  const ur16e_interfaces__msg__LoadObject * input,
  ur16e_interfaces__msg__LoadObject * output);

/// Initialize array of msg/LoadObject messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur16e_interfaces__msg__LoadObject__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
bool
ur16e_interfaces__msg__LoadObject__Sequence__init(ur16e_interfaces__msg__LoadObject__Sequence * array, size_t size);

/// Finalize array of msg/LoadObject messages.
/**
 * It calls
 * ur16e_interfaces__msg__LoadObject__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
void
ur16e_interfaces__msg__LoadObject__Sequence__fini(ur16e_interfaces__msg__LoadObject__Sequence * array);

/// Create array of msg/LoadObject messages.
/**
 * It allocates the memory for the array and calls
 * ur16e_interfaces__msg__LoadObject__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
ur16e_interfaces__msg__LoadObject__Sequence *
ur16e_interfaces__msg__LoadObject__Sequence__create(size_t size);

/// Destroy array of msg/LoadObject messages.
/**
 * It calls
 * ur16e_interfaces__msg__LoadObject__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
void
ur16e_interfaces__msg__LoadObject__Sequence__destroy(ur16e_interfaces__msg__LoadObject__Sequence * array);

/// Check for msg/LoadObject message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
bool
ur16e_interfaces__msg__LoadObject__Sequence__are_equal(const ur16e_interfaces__msg__LoadObject__Sequence * lhs, const ur16e_interfaces__msg__LoadObject__Sequence * rhs);

/// Copy an array of msg/LoadObject messages.
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
ROSIDL_GENERATOR_C_PUBLIC_ur16e_interfaces
bool
ur16e_interfaces__msg__LoadObject__Sequence__copy(
  const ur16e_interfaces__msg__LoadObject__Sequence * input,
  ur16e_interfaces__msg__LoadObject__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__FUNCTIONS_H_
