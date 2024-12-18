// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from opcua_interfaces_io_link:msg/SensorRead.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__STRUCT_H_
#define OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'sensor_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/SensorRead in the package opcua_interfaces_io_link.
typedef struct opcua_interfaces_io_link__msg__SensorRead
{
  rosidl_runtime_c__String sensor_id;
  int8_t sensor_read_type;
  bool sensor_value_bool;
  uint16_t sensor_value_int;
} opcua_interfaces_io_link__msg__SensorRead;

// Struct for a sequence of opcua_interfaces_io_link__msg__SensorRead.
typedef struct opcua_interfaces_io_link__msg__SensorRead__Sequence
{
  opcua_interfaces_io_link__msg__SensorRead * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} opcua_interfaces_io_link__msg__SensorRead__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__STRUCT_H_
