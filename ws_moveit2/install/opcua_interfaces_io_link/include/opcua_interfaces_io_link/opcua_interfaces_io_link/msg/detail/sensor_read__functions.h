// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from opcua_interfaces_io_link:msg/SensorRead.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__FUNCTIONS_H_
#define OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "opcua_interfaces_io_link/msg/rosidl_generator_c__visibility_control.h"

#include "opcua_interfaces_io_link/msg/detail/sensor_read__struct.h"

/// Initialize msg/SensorRead message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * opcua_interfaces_io_link__msg__SensorRead
 * )) before or use
 * opcua_interfaces_io_link__msg__SensorRead__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
bool
opcua_interfaces_io_link__msg__SensorRead__init(opcua_interfaces_io_link__msg__SensorRead * msg);

/// Finalize msg/SensorRead message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
void
opcua_interfaces_io_link__msg__SensorRead__fini(opcua_interfaces_io_link__msg__SensorRead * msg);

/// Create msg/SensorRead message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * opcua_interfaces_io_link__msg__SensorRead__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
opcua_interfaces_io_link__msg__SensorRead *
opcua_interfaces_io_link__msg__SensorRead__create();

/// Destroy msg/SensorRead message.
/**
 * It calls
 * opcua_interfaces_io_link__msg__SensorRead__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
void
opcua_interfaces_io_link__msg__SensorRead__destroy(opcua_interfaces_io_link__msg__SensorRead * msg);

/// Check for msg/SensorRead message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
bool
opcua_interfaces_io_link__msg__SensorRead__are_equal(const opcua_interfaces_io_link__msg__SensorRead * lhs, const opcua_interfaces_io_link__msg__SensorRead * rhs);

/// Copy a msg/SensorRead message.
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
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
bool
opcua_interfaces_io_link__msg__SensorRead__copy(
  const opcua_interfaces_io_link__msg__SensorRead * input,
  opcua_interfaces_io_link__msg__SensorRead * output);

/// Initialize array of msg/SensorRead messages.
/**
 * It allocates the memory for the number of elements and calls
 * opcua_interfaces_io_link__msg__SensorRead__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
bool
opcua_interfaces_io_link__msg__SensorRead__Sequence__init(opcua_interfaces_io_link__msg__SensorRead__Sequence * array, size_t size);

/// Finalize array of msg/SensorRead messages.
/**
 * It calls
 * opcua_interfaces_io_link__msg__SensorRead__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
void
opcua_interfaces_io_link__msg__SensorRead__Sequence__fini(opcua_interfaces_io_link__msg__SensorRead__Sequence * array);

/// Create array of msg/SensorRead messages.
/**
 * It allocates the memory for the array and calls
 * opcua_interfaces_io_link__msg__SensorRead__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
opcua_interfaces_io_link__msg__SensorRead__Sequence *
opcua_interfaces_io_link__msg__SensorRead__Sequence__create(size_t size);

/// Destroy array of msg/SensorRead messages.
/**
 * It calls
 * opcua_interfaces_io_link__msg__SensorRead__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
void
opcua_interfaces_io_link__msg__SensorRead__Sequence__destroy(opcua_interfaces_io_link__msg__SensorRead__Sequence * array);

/// Check for msg/SensorRead message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
bool
opcua_interfaces_io_link__msg__SensorRead__Sequence__are_equal(const opcua_interfaces_io_link__msg__SensorRead__Sequence * lhs, const opcua_interfaces_io_link__msg__SensorRead__Sequence * rhs);

/// Copy an array of msg/SensorRead messages.
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
ROSIDL_GENERATOR_C_PUBLIC_opcua_interfaces_io_link
bool
opcua_interfaces_io_link__msg__SensorRead__Sequence__copy(
  const opcua_interfaces_io_link__msg__SensorRead__Sequence * input,
  opcua_interfaces_io_link__msg__SensorRead__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__FUNCTIONS_H_
