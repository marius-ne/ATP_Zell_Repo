// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from opcua_interfaces:msg/ActuatorWrite.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__STRUCT_H_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__STRUCT_H_

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

/// Struct defined in msg/ActuatorWrite in the package opcua_interfaces.
typedef struct opcua_interfaces__msg__ActuatorWrite
{
  rosidl_runtime_c__String actuator_id;
  int8_t actuator_write_type;
  bool actuator_command_bool1;
  bool actuator_command_bool2;
} opcua_interfaces__msg__ActuatorWrite;

// Struct for a sequence of opcua_interfaces__msg__ActuatorWrite.
typedef struct opcua_interfaces__msg__ActuatorWrite__Sequence
{
  opcua_interfaces__msg__ActuatorWrite * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} opcua_interfaces__msg__ActuatorWrite__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__STRUCT_H_
