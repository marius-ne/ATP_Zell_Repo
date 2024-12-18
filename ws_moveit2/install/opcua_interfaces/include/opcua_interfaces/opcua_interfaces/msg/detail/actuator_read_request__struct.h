// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from opcua_interfaces:msg/ActuatorReadRequest.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__STRUCT_H_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'actuator_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ActuatorReadRequest in the package opcua_interfaces.
typedef struct opcua_interfaces__msg__ActuatorReadRequest
{
  rosidl_runtime_c__String actuator_id;
  int8_t actuator_read_type;
} opcua_interfaces__msg__ActuatorReadRequest;

// Struct for a sequence of opcua_interfaces__msg__ActuatorReadRequest.
typedef struct opcua_interfaces__msg__ActuatorReadRequest__Sequence
{
  opcua_interfaces__msg__ActuatorReadRequest * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} opcua_interfaces__msg__ActuatorReadRequest__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__STRUCT_H_
