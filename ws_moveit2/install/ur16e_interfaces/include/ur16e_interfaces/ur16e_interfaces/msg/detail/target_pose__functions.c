// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ur16e_interfaces:msg/TargetPose.idl
// generated code does not contain a copyright notice
#include "ur16e_interfaces/msg/detail/target_pose__functions.h"

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
ur16e_interfaces__msg__TargetPose__init(ur16e_interfaces__msg__TargetPose * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    ur16e_interfaces__msg__TargetPose__fini(msg);
    return false;
  }
  // coordinates
  if (!geometry_msgs__msg__Pose__init(&msg->coordinates)) {
    ur16e_interfaces__msg__TargetPose__fini(msg);
    return false;
  }
  return true;
}

void
ur16e_interfaces__msg__TargetPose__fini(ur16e_interfaces__msg__TargetPose * msg)
{
  if (!msg) {
    return;
  }
  // name
  rosidl_runtime_c__String__fini(&msg->name);
  // coordinates
  geometry_msgs__msg__Pose__fini(&msg->coordinates);
}

bool
ur16e_interfaces__msg__TargetPose__are_equal(const ur16e_interfaces__msg__TargetPose * lhs, const ur16e_interfaces__msg__TargetPose * rhs)
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
  return true;
}

bool
ur16e_interfaces__msg__TargetPose__copy(
  const ur16e_interfaces__msg__TargetPose * input,
  ur16e_interfaces__msg__TargetPose * output)
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
  return true;
}

ur16e_interfaces__msg__TargetPose *
ur16e_interfaces__msg__TargetPose__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ur16e_interfaces__msg__TargetPose * msg = (ur16e_interfaces__msg__TargetPose *)allocator.allocate(sizeof(ur16e_interfaces__msg__TargetPose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ur16e_interfaces__msg__TargetPose));
  bool success = ur16e_interfaces__msg__TargetPose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ur16e_interfaces__msg__TargetPose__destroy(ur16e_interfaces__msg__TargetPose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ur16e_interfaces__msg__TargetPose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ur16e_interfaces__msg__TargetPose__Sequence__init(ur16e_interfaces__msg__TargetPose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ur16e_interfaces__msg__TargetPose * data = NULL;

  if (size) {
    data = (ur16e_interfaces__msg__TargetPose *)allocator.zero_allocate(size, sizeof(ur16e_interfaces__msg__TargetPose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ur16e_interfaces__msg__TargetPose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ur16e_interfaces__msg__TargetPose__fini(&data[i - 1]);
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
ur16e_interfaces__msg__TargetPose__Sequence__fini(ur16e_interfaces__msg__TargetPose__Sequence * array)
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
      ur16e_interfaces__msg__TargetPose__fini(&array->data[i]);
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

ur16e_interfaces__msg__TargetPose__Sequence *
ur16e_interfaces__msg__TargetPose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ur16e_interfaces__msg__TargetPose__Sequence * array = (ur16e_interfaces__msg__TargetPose__Sequence *)allocator.allocate(sizeof(ur16e_interfaces__msg__TargetPose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ur16e_interfaces__msg__TargetPose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ur16e_interfaces__msg__TargetPose__Sequence__destroy(ur16e_interfaces__msg__TargetPose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ur16e_interfaces__msg__TargetPose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ur16e_interfaces__msg__TargetPose__Sequence__are_equal(const ur16e_interfaces__msg__TargetPose__Sequence * lhs, const ur16e_interfaces__msg__TargetPose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ur16e_interfaces__msg__TargetPose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ur16e_interfaces__msg__TargetPose__Sequence__copy(
  const ur16e_interfaces__msg__TargetPose__Sequence * input,
  ur16e_interfaces__msg__TargetPose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ur16e_interfaces__msg__TargetPose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ur16e_interfaces__msg__TargetPose * data =
      (ur16e_interfaces__msg__TargetPose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ur16e_interfaces__msg__TargetPose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ur16e_interfaces__msg__TargetPose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ur16e_interfaces__msg__TargetPose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
