// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ur16e_interfaces:msg/LoadObject.idl
// generated code does not contain a copyright notice
#include "ur16e_interfaces/msg/detail/load_object__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"
// Member `coordinates`
#include "geometry_msgs/msg/detail/pose__functions.h"

bool
ur16e_interfaces__msg__LoadObject__init(ur16e_interfaces__msg__LoadObject * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    ur16e_interfaces__msg__LoadObject__fini(msg);
    return false;
  }
  // coordinates
  if (!geometry_msgs__msg__Pose__init(&msg->coordinates)) {
    ur16e_interfaces__msg__LoadObject__fini(msg);
    return false;
  }
  // scale
  return true;
}

void
ur16e_interfaces__msg__LoadObject__fini(ur16e_interfaces__msg__LoadObject * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // coordinates
  geometry_msgs__msg__Pose__fini(&msg->coordinates);
  // scale
}

bool
ur16e_interfaces__msg__LoadObject__are_equal(const ur16e_interfaces__msg__LoadObject * lhs, const ur16e_interfaces__msg__LoadObject * rhs)
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
  // coordinates
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->coordinates), &(rhs->coordinates)))
  {
    return false;
  }
  // scale
  if (lhs->scale != rhs->scale) {
    return false;
  }
  return true;
}

bool
ur16e_interfaces__msg__LoadObject__copy(
  const ur16e_interfaces__msg__LoadObject * input,
  ur16e_interfaces__msg__LoadObject * output)
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
  // coordinates
  if (!geometry_msgs__msg__Pose__copy(
      &(input->coordinates), &(output->coordinates)))
  {
    return false;
  }
  // scale
  output->scale = input->scale;
  return true;
}

ur16e_interfaces__msg__LoadObject *
ur16e_interfaces__msg__LoadObject__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ur16e_interfaces__msg__LoadObject * msg = (ur16e_interfaces__msg__LoadObject *)allocator.allocate(sizeof(ur16e_interfaces__msg__LoadObject), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ur16e_interfaces__msg__LoadObject));
  bool success = ur16e_interfaces__msg__LoadObject__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ur16e_interfaces__msg__LoadObject__destroy(ur16e_interfaces__msg__LoadObject * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ur16e_interfaces__msg__LoadObject__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ur16e_interfaces__msg__LoadObject__Sequence__init(ur16e_interfaces__msg__LoadObject__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ur16e_interfaces__msg__LoadObject * data = NULL;

  if (size) {
    data = (ur16e_interfaces__msg__LoadObject *)allocator.zero_allocate(size, sizeof(ur16e_interfaces__msg__LoadObject), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ur16e_interfaces__msg__LoadObject__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ur16e_interfaces__msg__LoadObject__fini(&data[i - 1]);
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
ur16e_interfaces__msg__LoadObject__Sequence__fini(ur16e_interfaces__msg__LoadObject__Sequence * array)
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
      ur16e_interfaces__msg__LoadObject__fini(&array->data[i]);
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

ur16e_interfaces__msg__LoadObject__Sequence *
ur16e_interfaces__msg__LoadObject__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ur16e_interfaces__msg__LoadObject__Sequence * array = (ur16e_interfaces__msg__LoadObject__Sequence *)allocator.allocate(sizeof(ur16e_interfaces__msg__LoadObject__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ur16e_interfaces__msg__LoadObject__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ur16e_interfaces__msg__LoadObject__Sequence__destroy(ur16e_interfaces__msg__LoadObject__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ur16e_interfaces__msg__LoadObject__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ur16e_interfaces__msg__LoadObject__Sequence__are_equal(const ur16e_interfaces__msg__LoadObject__Sequence * lhs, const ur16e_interfaces__msg__LoadObject__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ur16e_interfaces__msg__LoadObject__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ur16e_interfaces__msg__LoadObject__Sequence__copy(
  const ur16e_interfaces__msg__LoadObject__Sequence * input,
  ur16e_interfaces__msg__LoadObject__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ur16e_interfaces__msg__LoadObject);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ur16e_interfaces__msg__LoadObject * data =
      (ur16e_interfaces__msg__LoadObject *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ur16e_interfaces__msg__LoadObject__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ur16e_interfaces__msg__LoadObject__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ur16e_interfaces__msg__LoadObject__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
