// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from wzlscheduler_interfaces:msg/LabeledPose.idl
// generated code does not contain a copyright notice
#include "wzlscheduler_interfaces/msg/detail/labeled_pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `label`
#include "rosidl_runtime_c/string_functions.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__functions.h"

bool
wzlscheduler_interfaces__msg__LabeledPose__init(wzlscheduler_interfaces__msg__LabeledPose * msg)
{
  if (!msg) {
    return false;
  }
  // label
  if (!rosidl_runtime_c__String__init(&msg->label)) {
    wzlscheduler_interfaces__msg__LabeledPose__fini(msg);
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__init(&msg->pose)) {
    wzlscheduler_interfaces__msg__LabeledPose__fini(msg);
    return false;
  }
  // drillholeindexx
  // drillholeindexy
  return true;
}

void
wzlscheduler_interfaces__msg__LabeledPose__fini(wzlscheduler_interfaces__msg__LabeledPose * msg)
{
  if (!msg) {
    return;
  }
  // label
  rosidl_runtime_c__String__fini(&msg->label);
  // pose
  geometry_msgs__msg__Pose__fini(&msg->pose);
  // drillholeindexx
  // drillholeindexy
}

bool
wzlscheduler_interfaces__msg__LabeledPose__are_equal(const wzlscheduler_interfaces__msg__LabeledPose * lhs, const wzlscheduler_interfaces__msg__LabeledPose * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // label
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->label), &(rhs->label)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  // drillholeindexx
  if (lhs->drillholeindexx != rhs->drillholeindexx) {
    return false;
  }
  // drillholeindexy
  if (lhs->drillholeindexy != rhs->drillholeindexy) {
    return false;
  }
  return true;
}

bool
wzlscheduler_interfaces__msg__LabeledPose__copy(
  const wzlscheduler_interfaces__msg__LabeledPose * input,
  wzlscheduler_interfaces__msg__LabeledPose * output)
{
  if (!input || !output) {
    return false;
  }
  // label
  if (!rosidl_runtime_c__String__copy(
      &(input->label), &(output->label)))
  {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  // drillholeindexx
  output->drillholeindexx = input->drillholeindexx;
  // drillholeindexy
  output->drillholeindexy = input->drillholeindexy;
  return true;
}

wzlscheduler_interfaces__msg__LabeledPose *
wzlscheduler_interfaces__msg__LabeledPose__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__LabeledPose * msg = (wzlscheduler_interfaces__msg__LabeledPose *)allocator.allocate(sizeof(wzlscheduler_interfaces__msg__LabeledPose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wzlscheduler_interfaces__msg__LabeledPose));
  bool success = wzlscheduler_interfaces__msg__LabeledPose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wzlscheduler_interfaces__msg__LabeledPose__destroy(wzlscheduler_interfaces__msg__LabeledPose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wzlscheduler_interfaces__msg__LabeledPose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wzlscheduler_interfaces__msg__LabeledPose__Sequence__init(wzlscheduler_interfaces__msg__LabeledPose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__LabeledPose * data = NULL;

  if (size) {
    data = (wzlscheduler_interfaces__msg__LabeledPose *)allocator.zero_allocate(size, sizeof(wzlscheduler_interfaces__msg__LabeledPose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wzlscheduler_interfaces__msg__LabeledPose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wzlscheduler_interfaces__msg__LabeledPose__fini(&data[i - 1]);
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
wzlscheduler_interfaces__msg__LabeledPose__Sequence__fini(wzlscheduler_interfaces__msg__LabeledPose__Sequence * array)
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
      wzlscheduler_interfaces__msg__LabeledPose__fini(&array->data[i]);
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

wzlscheduler_interfaces__msg__LabeledPose__Sequence *
wzlscheduler_interfaces__msg__LabeledPose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__LabeledPose__Sequence * array = (wzlscheduler_interfaces__msg__LabeledPose__Sequence *)allocator.allocate(sizeof(wzlscheduler_interfaces__msg__LabeledPose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wzlscheduler_interfaces__msg__LabeledPose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wzlscheduler_interfaces__msg__LabeledPose__Sequence__destroy(wzlscheduler_interfaces__msg__LabeledPose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wzlscheduler_interfaces__msg__LabeledPose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wzlscheduler_interfaces__msg__LabeledPose__Sequence__are_equal(const wzlscheduler_interfaces__msg__LabeledPose__Sequence * lhs, const wzlscheduler_interfaces__msg__LabeledPose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wzlscheduler_interfaces__msg__LabeledPose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wzlscheduler_interfaces__msg__LabeledPose__Sequence__copy(
  const wzlscheduler_interfaces__msg__LabeledPose__Sequence * input,
  wzlscheduler_interfaces__msg__LabeledPose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wzlscheduler_interfaces__msg__LabeledPose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wzlscheduler_interfaces__msg__LabeledPose * data =
      (wzlscheduler_interfaces__msg__LabeledPose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wzlscheduler_interfaces__msg__LabeledPose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wzlscheduler_interfaces__msg__LabeledPose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wzlscheduler_interfaces__msg__LabeledPose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
