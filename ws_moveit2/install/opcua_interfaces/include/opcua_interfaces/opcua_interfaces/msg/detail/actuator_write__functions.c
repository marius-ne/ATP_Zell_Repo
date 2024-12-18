// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from opcua_interfaces:msg/ActuatorWrite.idl
// generated code does not contain a copyright notice
#include "opcua_interfaces/msg/detail/actuator_write__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `actuator_id`
#include "rosidl_runtime_c/string_functions.h"

bool
opcua_interfaces__msg__ActuatorWrite__init(opcua_interfaces__msg__ActuatorWrite * msg)
{
  if (!msg) {
    return false;
  }
  // actuator_id
  if (!rosidl_runtime_c__String__init(&msg->actuator_id)) {
    opcua_interfaces__msg__ActuatorWrite__fini(msg);
    return false;
  }
  // actuator_write_type
  // actuator_command_bool1
  // actuator_command_bool2
  return true;
}

void
opcua_interfaces__msg__ActuatorWrite__fini(opcua_interfaces__msg__ActuatorWrite * msg)
{
  if (!msg) {
    return;
  }
  // actuator_id
  rosidl_runtime_c__String__fini(&msg->actuator_id);
  // actuator_write_type
  // actuator_command_bool1
  // actuator_command_bool2
}

bool
opcua_interfaces__msg__ActuatorWrite__are_equal(const opcua_interfaces__msg__ActuatorWrite * lhs, const opcua_interfaces__msg__ActuatorWrite * rhs)
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
  // actuator_write_type
  if (lhs->actuator_write_type != rhs->actuator_write_type) {
    return false;
  }
  // actuator_command_bool1
  if (lhs->actuator_command_bool1 != rhs->actuator_command_bool1) {
    return false;
  }
  // actuator_command_bool2
  if (lhs->actuator_command_bool2 != rhs->actuator_command_bool2) {
    return false;
  }
  return true;
}

bool
opcua_interfaces__msg__ActuatorWrite__copy(
  const opcua_interfaces__msg__ActuatorWrite * input,
  opcua_interfaces__msg__ActuatorWrite * output)
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
  // actuator_write_type
  output->actuator_write_type = input->actuator_write_type;
  // actuator_command_bool1
  output->actuator_command_bool1 = input->actuator_command_bool1;
  // actuator_command_bool2
  output->actuator_command_bool2 = input->actuator_command_bool2;
  return true;
}

opcua_interfaces__msg__ActuatorWrite *
opcua_interfaces__msg__ActuatorWrite__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  opcua_interfaces__msg__ActuatorWrite * msg = (opcua_interfaces__msg__ActuatorWrite *)allocator.allocate(sizeof(opcua_interfaces__msg__ActuatorWrite), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(opcua_interfaces__msg__ActuatorWrite));
  bool success = opcua_interfaces__msg__ActuatorWrite__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
opcua_interfaces__msg__ActuatorWrite__destroy(opcua_interfaces__msg__ActuatorWrite * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    opcua_interfaces__msg__ActuatorWrite__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
opcua_interfaces__msg__ActuatorWrite__Sequence__init(opcua_interfaces__msg__ActuatorWrite__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  opcua_interfaces__msg__ActuatorWrite * data = NULL;

  if (size) {
    data = (opcua_interfaces__msg__ActuatorWrite *)allocator.zero_allocate(size, sizeof(opcua_interfaces__msg__ActuatorWrite), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = opcua_interfaces__msg__ActuatorWrite__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        opcua_interfaces__msg__ActuatorWrite__fini(&data[i - 1]);
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
opcua_interfaces__msg__ActuatorWrite__Sequence__fini(opcua_interfaces__msg__ActuatorWrite__Sequence * array)
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
      opcua_interfaces__msg__ActuatorWrite__fini(&array->data[i]);
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

opcua_interfaces__msg__ActuatorWrite__Sequence *
opcua_interfaces__msg__ActuatorWrite__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  opcua_interfaces__msg__ActuatorWrite__Sequence * array = (opcua_interfaces__msg__ActuatorWrite__Sequence *)allocator.allocate(sizeof(opcua_interfaces__msg__ActuatorWrite__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = opcua_interfaces__msg__ActuatorWrite__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
opcua_interfaces__msg__ActuatorWrite__Sequence__destroy(opcua_interfaces__msg__ActuatorWrite__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    opcua_interfaces__msg__ActuatorWrite__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
opcua_interfaces__msg__ActuatorWrite__Sequence__are_equal(const opcua_interfaces__msg__ActuatorWrite__Sequence * lhs, const opcua_interfaces__msg__ActuatorWrite__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!opcua_interfaces__msg__ActuatorWrite__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
opcua_interfaces__msg__ActuatorWrite__Sequence__copy(
  const opcua_interfaces__msg__ActuatorWrite__Sequence * input,
  opcua_interfaces__msg__ActuatorWrite__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(opcua_interfaces__msg__ActuatorWrite);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    opcua_interfaces__msg__ActuatorWrite * data =
      (opcua_interfaces__msg__ActuatorWrite *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!opcua_interfaces__msg__ActuatorWrite__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          opcua_interfaces__msg__ActuatorWrite__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!opcua_interfaces__msg__ActuatorWrite__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
