// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from wzlscheduler_interfaces:srv/RobotSetVelocity.idl
// generated code does not contain a copyright notice
#include "wzlscheduler_interfaces/srv/detail/robot_set_velocity__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__init(wzlscheduler_interfaces__srv__RobotSetVelocity_Request * msg)
{
  if (!msg) {
    return false;
  }
  // value
  return true;
}

void
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__fini(wzlscheduler_interfaces__srv__RobotSetVelocity_Request * msg)
{
  if (!msg) {
    return;
  }
  // value
}

bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__are_equal(const wzlscheduler_interfaces__srv__RobotSetVelocity_Request * lhs, const wzlscheduler_interfaces__srv__RobotSetVelocity_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // value
  if (lhs->value != rhs->value) {
    return false;
  }
  return true;
}

bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__copy(
  const wzlscheduler_interfaces__srv__RobotSetVelocity_Request * input,
  wzlscheduler_interfaces__srv__RobotSetVelocity_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // value
  output->value = input->value;
  return true;
}

wzlscheduler_interfaces__srv__RobotSetVelocity_Request *
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__srv__RobotSetVelocity_Request * msg = (wzlscheduler_interfaces__srv__RobotSetVelocity_Request *)allocator.allocate(sizeof(wzlscheduler_interfaces__srv__RobotSetVelocity_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wzlscheduler_interfaces__srv__RobotSetVelocity_Request));
  bool success = wzlscheduler_interfaces__srv__RobotSetVelocity_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__destroy(wzlscheduler_interfaces__srv__RobotSetVelocity_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wzlscheduler_interfaces__srv__RobotSetVelocity_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence__init(wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__srv__RobotSetVelocity_Request * data = NULL;

  if (size) {
    data = (wzlscheduler_interfaces__srv__RobotSetVelocity_Request *)allocator.zero_allocate(size, sizeof(wzlscheduler_interfaces__srv__RobotSetVelocity_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wzlscheduler_interfaces__srv__RobotSetVelocity_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wzlscheduler_interfaces__srv__RobotSetVelocity_Request__fini(&data[i - 1]);
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
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence__fini(wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence * array)
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
      wzlscheduler_interfaces__srv__RobotSetVelocity_Request__fini(&array->data[i]);
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

wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence *
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence * array = (wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence *)allocator.allocate(sizeof(wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence__destroy(wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence__are_equal(const wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence * lhs, const wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wzlscheduler_interfaces__srv__RobotSetVelocity_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence__copy(
  const wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence * input,
  wzlscheduler_interfaces__srv__RobotSetVelocity_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wzlscheduler_interfaces__srv__RobotSetVelocity_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wzlscheduler_interfaces__srv__RobotSetVelocity_Request * data =
      (wzlscheduler_interfaces__srv__RobotSetVelocity_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wzlscheduler_interfaces__srv__RobotSetVelocity_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wzlscheduler_interfaces__srv__RobotSetVelocity_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wzlscheduler_interfaces__srv__RobotSetVelocity_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__init(wzlscheduler_interfaces__srv__RobotSetVelocity_Response * msg)
{
  if (!msg) {
    return false;
  }
  // result
  return true;
}

void
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__fini(wzlscheduler_interfaces__srv__RobotSetVelocity_Response * msg)
{
  if (!msg) {
    return;
  }
  // result
}

bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__are_equal(const wzlscheduler_interfaces__srv__RobotSetVelocity_Response * lhs, const wzlscheduler_interfaces__srv__RobotSetVelocity_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // result
  if (lhs->result != rhs->result) {
    return false;
  }
  return true;
}

bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__copy(
  const wzlscheduler_interfaces__srv__RobotSetVelocity_Response * input,
  wzlscheduler_interfaces__srv__RobotSetVelocity_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // result
  output->result = input->result;
  return true;
}

wzlscheduler_interfaces__srv__RobotSetVelocity_Response *
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__srv__RobotSetVelocity_Response * msg = (wzlscheduler_interfaces__srv__RobotSetVelocity_Response *)allocator.allocate(sizeof(wzlscheduler_interfaces__srv__RobotSetVelocity_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wzlscheduler_interfaces__srv__RobotSetVelocity_Response));
  bool success = wzlscheduler_interfaces__srv__RobotSetVelocity_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__destroy(wzlscheduler_interfaces__srv__RobotSetVelocity_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wzlscheduler_interfaces__srv__RobotSetVelocity_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence__init(wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__srv__RobotSetVelocity_Response * data = NULL;

  if (size) {
    data = (wzlscheduler_interfaces__srv__RobotSetVelocity_Response *)allocator.zero_allocate(size, sizeof(wzlscheduler_interfaces__srv__RobotSetVelocity_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wzlscheduler_interfaces__srv__RobotSetVelocity_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wzlscheduler_interfaces__srv__RobotSetVelocity_Response__fini(&data[i - 1]);
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
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence__fini(wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence * array)
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
      wzlscheduler_interfaces__srv__RobotSetVelocity_Response__fini(&array->data[i]);
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

wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence *
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence * array = (wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence *)allocator.allocate(sizeof(wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence__destroy(wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence__are_equal(const wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence * lhs, const wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wzlscheduler_interfaces__srv__RobotSetVelocity_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence__copy(
  const wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence * input,
  wzlscheduler_interfaces__srv__RobotSetVelocity_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wzlscheduler_interfaces__srv__RobotSetVelocity_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wzlscheduler_interfaces__srv__RobotSetVelocity_Response * data =
      (wzlscheduler_interfaces__srv__RobotSetVelocity_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wzlscheduler_interfaces__srv__RobotSetVelocity_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wzlscheduler_interfaces__srv__RobotSetVelocity_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wzlscheduler_interfaces__srv__RobotSetVelocity_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
