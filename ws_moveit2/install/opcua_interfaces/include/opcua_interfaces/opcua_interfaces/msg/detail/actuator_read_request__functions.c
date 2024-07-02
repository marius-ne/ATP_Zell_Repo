// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from opcua_interfaces:msg/ActuatorReadRequest.idl
// generated code does not contain a copyright notice
#include "opcua_interfaces/msg/detail/actuator_read_request__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `actuator_id`
#include "rosidl_runtime_c/string_functions.h"

bool
opcua_interfaces__msg__ActuatorReadRequest__init(opcua_interfaces__msg__ActuatorReadRequest * msg)
{
  if (!msg) {
    return false;
  }
  // actuator_id
  if (!rosidl_runtime_c__String__init(&msg->actuator_id)) {
    opcua_interfaces__msg__ActuatorReadRequest__fini(msg);
    return false;
  }
  // actuator_read_type
  return true;
}

void
opcua_interfaces__msg__ActuatorReadRequest__fini(opcua_interfaces__msg__ActuatorReadRequest * msg)
{
  if (!msg) {
    return;
  }
  // actuator_id
  rosidl_runtime_c__String__fini(&msg->actuator_id);
  // actuator_read_type
}

bool
opcua_interfaces__msg__ActuatorReadRequest__are_equal(const opcua_interfaces__msg__ActuatorReadRequest * lhs, const opcua_interfaces__msg__ActuatorReadRequest * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // actuator_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->actuator_id), &(rhs->actuator_id)))
  {
    return false;
  }
  // actuator_read_type
  if (lhs->actuator_read_type != rhs->actuator_read_type) {
    return false;
  }
  return true;
}

bool
opcua_interfaces__msg__ActuatorReadRequest__copy(
  const opcua_interfaces__msg__ActuatorReadRequest * input,
  opcua_interfaces__msg__ActuatorReadRequest * output)
{
  if (!input || !output) {
    return false;
  }
  // actuator_id
  if (!rosidl_runtime_c__String__copy(
      &(input->actuator_id), &(output->actuator_id)))
  {
    return false;
  }
  // actuator_read_type
  output->actuator_read_type = input->actuator_read_type;
  return true;
}

opcua_interfaces__msg__ActuatorReadRequest *
opcua_interfaces__msg__ActuatorReadRequest__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  opcua_interfaces__msg__ActuatorReadRequest * msg = (opcua_interfaces__msg__ActuatorReadRequest *)allocator.allocate(sizeof(opcua_interfaces__msg__ActuatorReadRequest), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(opcua_interfaces__msg__ActuatorReadRequest));
  bool success = opcua_interfaces__msg__ActuatorReadRequest__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
opcua_interfaces__msg__ActuatorReadRequest__destroy(opcua_interfaces__msg__ActuatorReadRequest * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    opcua_interfaces__msg__ActuatorReadRequest__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
opcua_interfaces__msg__ActuatorReadRequest__Sequence__init(opcua_interfaces__msg__ActuatorReadRequest__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  opcua_interfaces__msg__ActuatorReadRequest * data = NULL;

  if (size) {
    data = (opcua_interfaces__msg__ActuatorReadRequest *)allocator.zero_allocate(size, sizeof(opcua_interfaces__msg__ActuatorReadRequest), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = opcua_interfaces__msg__ActuatorReadRequest__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        opcua_interfaces__msg__ActuatorReadRequest__fini(&data[i - 1]);
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
opcua_interfaces__msg__ActuatorReadRequest__Sequence__fini(opcua_interfaces__msg__ActuatorReadRequest__Sequence * array)
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
      opcua_interfaces__msg__ActuatorReadRequest__fini(&array->data[i]);
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

opcua_interfaces__msg__ActuatorReadRequest__Sequence *
opcua_interfaces__msg__ActuatorReadRequest__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  opcua_interfaces__msg__ActuatorReadRequest__Sequence * array = (opcua_interfaces__msg__ActuatorReadRequest__Sequence *)allocator.allocate(sizeof(opcua_interfaces__msg__ActuatorReadRequest__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = opcua_interfaces__msg__ActuatorReadRequest__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
opcua_interfaces__msg__ActuatorReadRequest__Sequence__destroy(opcua_interfaces__msg__ActuatorReadRequest__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    opcua_interfaces__msg__ActuatorReadRequest__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
opcua_interfaces__msg__ActuatorReadRequest__Sequence__are_equal(const opcua_interfaces__msg__ActuatorReadRequest__Sequence * lhs, const opcua_interfaces__msg__ActuatorReadRequest__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!opcua_interfaces__msg__ActuatorReadRequest__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
opcua_interfaces__msg__ActuatorReadRequest__Sequence__copy(
  const opcua_interfaces__msg__ActuatorReadRequest__Sequence * input,
  opcua_interfaces__msg__ActuatorReadRequest__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(opcua_interfaces__msg__ActuatorReadRequest);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    opcua_interfaces__msg__ActuatorReadRequest * data =
      (opcua_interfaces__msg__ActuatorReadRequest *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!opcua_interfaces__msg__ActuatorReadRequest__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          opcua_interfaces__msg__ActuatorReadRequest__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!opcua_interfaces__msg__ActuatorReadRequest__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
