// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from opcua_interfaces:msg/ActuatorWrite.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__FUNCTIONS_H_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "opcua_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "opcua_interfaces/msg/detail/actuator_write__struct.h"

/// Initialize msg/ActuatorWrite message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * opcua_interfaces__msg__ActuatorWrite
 * )) before or use
 * opcua_interfaces__msg__ActuatorWrite__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorWrite__init(opcua_interfaces__msg__ActuatorWrite * msg);

/// Finalize msg/ActuatorWrite message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorWrite__fini(opcua_interfaces__msg__ActuatorWrite * msg);

/// Create msg/ActuatorWrite message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * opcua_interfaces__msg__ActuatorWrite__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
opcua_interfaces__msg__ActuatorWrite *
opcua_interfaces__msg__ActuatorWrite__create();

/// Destroy msg/ActuatorWrite message.
/**
 * It calls
 * opcua_interfaces__msg__ActuatorWrite__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorWrite__destroy(opcua_interfaces__msg__ActuatorWrite * msg);

/// Check for msg/ActuatorWrite message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorWrite__are_equal(const opcua_interfaces__msg__ActuatorWrite * lhs, const opcua_interfaces__msg__ActuatorWrite * rhs);

/// Copy a msg/ActuatorWrite message.
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
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorWrite__copy(
  const opcua_interfaces__msg__ActuatorWrite * input,
  opcua_interfaces__msg__ActuatorWrite * output);

/// Initialize array of msg/ActuatorWrite messages.
/**
 * It allocates the memory for the number of elements and calls
 * opcua_interfaces__msg__ActuatorWrite__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorWrite__Sequence__init(opcua_interfaces__msg__ActuatorWrite__Sequence * array, size_t size);

/// Finalize array of msg/ActuatorWrite messages.
/**
 * It calls
 * opcua_interfaces__msg__ActuatorWrite__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorWrite__Sequence__fini(opcua_interfaces__msg__ActuatorWrite__Sequence * array);

/// Create array of msg/ActuatorWrite messages.
/**
 * It allocates the memory for the array and calls
 * opcua_interfaces__msg__ActuatorWrite__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
opcua_interfaces__msg__ActuatorWrite__Sequence *
opcua_interfaces__msg__ActuatorWrite__Sequence__create(size_t size);

/// Destroy array of msg/ActuatorWrite messages.
/**
 * It calls
 * opcua_interfaces__msg__ActuatorWrite__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorWrite__Sequence__destroy(opcua_interfaces__msg__ActuatorWrite__Sequence * array);

/// Check for msg/ActuatorWrite message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorWrite__Sequence__are_equal(const opcua_interfaces__msg__ActuatorWrite__Sequence * lhs, const opcua_interfaces__msg__ActuatorWrite__Sequence * rhs);

/// Copy an array of msg/ActuatorWrite messages.
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
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorWrite__Sequence__copy(
  const opcua_interfaces__msg__ActuatorWrite__Sequence * input,
  opcua_interfaces__msg__ActuatorWrite__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__FUNCTIONS_H_
