// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from opcua_interfaces:msg/ActuatorReadRequest.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__FUNCTIONS_H_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "opcua_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "opcua_interfaces/msg/detail/actuator_read_request__struct.h"

/// Initialize msg/ActuatorReadRequest message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * opcua_interfaces__msg__ActuatorReadRequest
 * )) before or use
 * opcua_interfaces__msg__ActuatorReadRequest__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorReadRequest__init(opcua_interfaces__msg__ActuatorReadRequest * msg);

/// Finalize msg/ActuatorReadRequest message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorReadRequest__fini(opcua_interfaces__msg__ActuatorReadRequest * msg);

/// Create msg/ActuatorReadRequest message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * opcua_interfaces__msg__ActuatorReadRequest__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
opcua_interfaces__msg__ActuatorReadRequest *
opcua_interfaces__msg__ActuatorReadRequest__create();

/// Destroy msg/ActuatorReadRequest message.
/**
 * It calls
 * opcua_interfaces__msg__ActuatorReadRequest__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorReadRequest__destroy(opcua_interfaces__msg__ActuatorReadRequest * msg);

/// Check for msg/ActuatorReadRequest message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorReadRequest__are_equal(const opcua_interfaces__msg__ActuatorReadRequest * lhs, const opcua_interfaces__msg__ActuatorReadRequest * rhs);

/// Copy a msg/ActuatorReadRequest message.
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
opcua_interfaces__msg__ActuatorReadRequest__copy(
  const opcua_interfaces__msg__ActuatorReadRequest * input,
  opcua_interfaces__msg__ActuatorReadRequest * output);

/// Initialize array of msg/ActuatorReadRequest messages.
/**
 * It allocates the memory for the number of elements and calls
 * opcua_interfaces__msg__ActuatorReadRequest__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorReadRequest__Sequence__init(opcua_interfaces__msg__ActuatorReadRequest__Sequence * array, size_t size);

/// Finalize array of msg/ActuatorReadRequest messages.
/**
 * It calls
 * opcua_interfaces__msg__ActuatorReadRequest__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorReadRequest__Sequence__fini(opcua_interfaces__msg__ActuatorReadRequest__Sequence * array);

/// Create array of msg/ActuatorReadRequest messages.
/**
 * It allocates the memory for the array and calls
 * opcua_interfaces__msg__ActuatorReadRequest__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
opcua_interfaces__msg__ActuatorReadRequest__Sequence *
opcua_interfaces__msg__ActuatorReadRequest__Sequence__create(size_t size);

/// Destroy array of msg/ActuatorReadRequest messages.
/**
 * It calls
 * opcua_interfaces__msg__ActuatorReadRequest__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
void
opcua_interfaces__msg__ActuatorReadRequest__Sequence__destroy(opcua_interfaces__msg__ActuatorReadRequest__Sequence * array);

/// Check for msg/ActuatorReadRequest message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces
bool
opcua_interfaces__msg__ActuatorReadRequest__Sequence__are_equal(const opcua_interfaces__msg__ActuatorReadRequest__Sequence * lhs, const opcua_interfaces__msg__ActuatorReadRequest__Sequence * rhs);

/// Copy an array of msg/ActuatorReadRequest messages.
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
opcua_interfaces__msg__ActuatorReadRequest__Sequence__copy(
  const opcua_interfaces__msg__ActuatorReadRequest__Sequence * input,
  opcua_interfaces__msg__ActuatorReadRequest__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__FUNCTIONS_H_
