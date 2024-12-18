// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from wzlscheduler_interfaces:msg/SceneObjectRemove.idl
// generated code does not contain a copyright notice
#include "wzlscheduler_interfaces/msg/detail/scene_object_remove__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

bool
wzlscheduler_interfaces__msg__SceneObjectRemove__init(wzlscheduler_interfaces__msg__SceneObjectRemove * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    wzlscheduler_interfaces__msg__SceneObjectRemove__fini(msg);
    return false;
  }
  return true;
}

void
wzlscheduler_interfaces__msg__SceneObjectRemove__fini(wzlscheduler_interfaces__msg__SceneObjectRemove * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
}

bool
wzlscheduler_interfaces__msg__SceneObjectRemove__are_equal(const wzlscheduler_interfaces__msg__SceneObjectRemove * lhs, const wzlscheduler_interfaces__msg__SceneObjectRemove * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->name), &(rhs->name)))
  {
    return false;
  }
  return true;
}

bool
wzlscheduler_interfaces__msg__SceneObjectRemove__copy(
  const wzlscheduler_interfaces__msg__SceneObjectRemove * input,
  wzlscheduler_interfaces__msg__SceneObjectRemove * output)
{
  if (!input || !output) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__copy(
      &(input->name), &(output->name)))
  {
    return false;
  }
  return true;
}

wzlscheduler_interfaces__msg__SceneObjectRemove *
wzlscheduler_interfaces__msg__SceneObjectRemove__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__SceneObjectRemove * msg = (wzlscheduler_interfaces__msg__SceneObjectRemove *)allocator.allocate(sizeof(wzlscheduler_interfaces__msg__SceneObjectRemove), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wzlscheduler_interfaces__msg__SceneObjectRemove));
  bool success = wzlscheduler_interfaces__msg__SceneObjectRemove__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wzlscheduler_interfaces__msg__SceneObjectRemove__destroy(wzlscheduler_interfaces__msg__SceneObjectRemove * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wzlscheduler_interfaces__msg__SceneObjectRemove__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence__init(wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__SceneObjectRemove * data = NULL;

  if (size) {
    data = (wzlscheduler_interfaces__msg__SceneObjectRemove *)allocator.zero_allocate(size, sizeof(wzlscheduler_interfaces__msg__SceneObjectRemove), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wzlscheduler_interfaces__msg__SceneObjectRemove__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wzlscheduler_interfaces__msg__SceneObjectRemove__fini(&data[i - 1]);
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
wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence__fini(wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence * array)
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
      wzlscheduler_interfaces__msg__SceneObjectRemove__fini(&array->data[i]);
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

wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence *
wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence * array = (wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence *)allocator.allocate(sizeof(wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence__destroy(wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence__are_equal(const wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence * lhs, const wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wzlscheduler_interfaces__msg__SceneObjectRemove__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence__copy(
  const wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence * input,
  wzlscheduler_interfaces__msg__SceneObjectRemove__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wzlscheduler_interfaces__msg__SceneObjectRemove);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wzlscheduler_interfaces__msg__SceneObjectRemove * data =
      (wzlscheduler_interfaces__msg__SceneObjectRemove *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wzlscheduler_interfaces__msg__SceneObjectRemove__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wzlscheduler_interfaces__msg__SceneObjectRemove__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wzlscheduler_interfaces__msg__SceneObjectRemove__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
