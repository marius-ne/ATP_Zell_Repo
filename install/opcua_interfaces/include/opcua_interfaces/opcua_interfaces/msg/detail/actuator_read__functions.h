// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from opcua_interfaces:msg/ActuatorRead.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ__FUNCTIONS_H_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "opcua_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "opcua_interfaces/msg/detail/actuator_read__struct.h"

/// Initialize msg/ActuatorRead message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * opcua_interfaces__msg__ActuatorRead
 * )) before or use
 * opcua_interfaces__msg__ActuatorRead__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorRead__init(opcua_interfaces__msg__ActuatorRead * msg);

/// Finalize msg/ActuatorRead message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorRead__fini(opcua_interfaces__msg__ActuatorRead * msg);

/// Create msg/ActuatorRead message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * opcua_interfaces__msg__ActuatorRead__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
opcua_interfaces__msg__ActuatorRead *
opcua_interfaces__msg__ActuatorRead__create();

/// Destroy msg/ActuatorRead message.
/**
 * It calls
 * opcua_interfaces__msg__ActuatorRead__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorRead__destroy(opcua_interfaces__msg__ActuatorRead * msg);

/// Check for msg/ActuatorRead message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorRead__are_equal(const opcua_interfaces__msg__ActuatorRead * lhs, const opcua_interfaces__msg__ActuatorRead * rhs);

/// Copy a msg/ActuatorRead message.
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
opcua_interfaces__msg__ActuatorRead__copy(
  const opcua_interfaces__msg__ActuatorRead * input,
  opcua_interfaces__msg__ActuatorRead * output);

/// Initialize array of msg/ActuatorRead messages.
/**
 * It allocates the memory for the number of elements and calls
 * opcua_interfaces__msg__ActuatorRead__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorRead__Sequence__init(opcua_interfaces__msg__ActuatorRead__Sequence * array, size_t size);

/// Finalize array of msg/ActuatorRead messages.
/**
 * It calls
 * opcua_interfaces__msg__ActuatorRead__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorRead__Sequence__fini(opcua_interfaces__msg__ActuatorRead__Sequence * array);

/// Create array of msg/ActuatorRead messages.
/**
 * It allocates the memory for the array and calls
 * opcua_interfaces__msg__ActuatorRead__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
opcua_interfaces__msg__ActuatorRead__Sequence *
opcua_interfaces__msg__ActuatorRead__Sequence__create(size_t size);

/// Destroy array of msg/ActuatorRead messages.
/**
 * It calls
 * opcua_interfaces__msg__ActuatorRead__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorRead__Sequence__destroy(opcua_interfaces__msg__ActuatorRead__Sequence * array);

/// Check for msg/ActuatorRead message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorRead__Sequence__are_equal(const opcua_interfaces__msg__ActuatorRead__Sequence * lhs, const opcua_interfaces__msg__ActuatorRead__Sequence * rhs);

/// Copy an array of msg/ActuatorRead messages.
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
opcua_interfaces__msg__ActuatorRead__Sequence__copy(
  const opcua_interfaces__msg__ActuatorRead__Sequence * input,
  opcua_interfaces__msg__ActuatorRead__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ__FUNCTIONS_H_
