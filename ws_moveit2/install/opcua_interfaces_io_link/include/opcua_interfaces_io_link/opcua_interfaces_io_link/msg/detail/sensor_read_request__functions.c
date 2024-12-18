// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from opcua_interfaces_io_link:msg/SensorReadRequest.idl
// generated code does not contain a copyright notice
#include "opcua_interfaces_io_link/msg/detail/sensor_read_request__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `sensor_id`
#include "rosidl_runtime_c/string_functions.h"

bool
opcua_interfaces_io_link__msg__SensorReadRequest__init(opcua_interfaces_io_link__msg__SensorReadRequest * msg)
{
  if (!msg) {
    return false;
  }
  // sensor_id
  if (!rosidl_runtime_c__String__init(&msg->sensor_id)) {
    opcua_interfaces_io_link__msg__SensorReadRequest__fini(msg);
    return false;
  }
  // sensor_read_type
  return true;
}

void
opcua_interfaces_io_link__msg__SensorReadRequest__fini(opcua_interfaces_io_link__msg__SensorReadRequest * msg)
{
  if (!msg) {
    return;
  }
  // sensor_id
  rosidl_runtime_c__String__fini(&msg->sensor_id);
  // sensor_read_type
}

bool
opcua_interfaces_io_link__msg__SensorReadRequest__are_equal(const opcua_interfaces_io_link__msg__SensorReadRequest * lhs, const opcua_interfaces_io_link__msg__SensorReadRequest * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // sensor_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->sensor_id), &(rhs->sensor_id)))
  {
    return false;
  }
  // sensor_read_type
  if (lhs->sensor_read_type != rhs->sensor_read_type) {
    return false;
  }
  return true;
}

bool
opcua_interfaces_io_link__msg__SensorReadRequest__copy(
  const opcua_interfaces_io_link__msg__SensorReadRequest * input,
  opcua_interfaces_io_link__msg__SensorReadRequest * output)
{
  if (!input || !output) {
    return false;
  }
  // sensor_id
  if (!rosidl_runtime_c__String__copy(
      &(input->sensor_id), &(output->sensor_id)))
  {
    return false;
  }
  // sensor_read_type
  output->sensor_read_type = input->sensor_read_type;
  return true;
}

opcua_interfaces_io_link__msg__SensorReadRequest *
opcua_interfaces_io_link__msg__SensorReadRequest__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  opcua_interfaces_io_link__msg__SensorReadRequest * msg = (opcua_interfaces_io_link__msg__SensorReadRequest *)allocator.allocate(sizeof(opcua_interfaces_io_link__msg__SensorReadRequest), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(opcua_interfaces_io_link__msg__SensorReadRequest));
  bool success = opcua_interfaces_io_link__msg__SensorReadRequest__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
opcua_interfaces_io_link__msg__SensorReadRequest__destroy(opcua_interfaces_io_link__msg__SensorReadRequest * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    opcua_interfaces_io_link__msg__SensorReadRequest__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
opcua_interfaces_io_link__msg__SensorReadRequest__Sequence__init(opcua_interfaces_io_link__msg__SensorReadRequest__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  opcua_interfaces_io_link__msg__SensorReadRequest * data = NULL;

  if (size) {
    data = (opcua_interfaces_io_link__msg__SensorReadRequest *)allocator.zero_allocate(size, sizeof(opcua_interfaces_io_link__msg__SensorReadRequest), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = opcua_interfaces_io_link__msg__SensorReadRequest__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        opcua_interfaces_io_link__msg__SensorReadRequest__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
opcua_interfaces_io_link__msg__SensorReadRequest__Sequence__fini(opcua_interfaces_io_link__msg__SensorReadRequest__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      opcua_interfaces_io_link__msg__SensorReadRequest__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

opcua_interfaces_io_link__msg__SensorReadRequest__Sequence *
opcua_interfaces_io_link__msg__SensorReadRequest__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  opcua_interfaces_io_link__msg__SensorReadRequest__Sequence * array = (opcua_interfaces_io_link__msg__SensorReadRequest__Sequence *)allocator.allocate(sizeof(opcua_interfaces_io_link__msg__SensorReadRequest__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = opcua_interfaces_io_link__msg__SensorReadRequest__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
opcua_interfaces_io_link__msg__SensorReadRequest__Sequence__destroy(opcua_interfaces_io_link__msg__SensorReadRequest__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    opcua_interfaces_io_link__msg__SensorReadRequest__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
opcua_interfaces_io_link__msg__SensorReadRequest__Sequence__are_equal(const opcua_interfaces_io_link__msg__SensorReadRequest__Sequence * lhs, const opcua_interfaces_io_link__msg__SensorReadRequest__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!opcua_interfaces_io_link__msg__SensorReadRequest__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
opcua_interfaces_io_link__msg__SensorReadRequest__Sequence__copy(
  const opcua_interfaces_io_link__msg__SensorReadRequest__Sequence * input,
  opcua_interfaces_io_link__msg__SensorReadRequest__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(opcua_interfaces_io_link__msg__SensorReadRequest);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    opcua_interfaces_io_link__msg__SensorReadRequest * data =
      (opcua_interfaces_io_link__msg__SensorReadRequest *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!opcua_interfaces_io_link__msg__SensorReadRequest__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          opcua_interfaces_io_link__msg__SensorReadRequest__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!opcua_interfaces_io_link__msg__SensorReadRequest__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
