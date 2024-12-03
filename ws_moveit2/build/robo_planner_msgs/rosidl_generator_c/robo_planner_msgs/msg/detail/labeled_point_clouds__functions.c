// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robo_planner_msgs:msg/LabeledPointClouds.idl
// generated code does not contain a copyright notice
#include "robo_planner_msgs/msg/detail/labeled_point_clouds__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `elements`
#include "robo_planner_msgs/msg/detail/labeled_point_cloud__functions.h"

bool
robo_planner_msgs__msg__LabeledPointClouds__init(robo_planner_msgs__msg__LabeledPointClouds * msg)
{
  if (!msg) {
    return false;
  }
  // elements
  if (!robo_planner_msgs__msg__LabeledPointCloud__Sequence__init(&msg->elements, 0)) {
    robo_planner_msgs__msg__LabeledPointClouds__fini(msg);
    return false;
  }
  return true;
}

void
robo_planner_msgs__msg__LabeledPointClouds__fini(robo_planner_msgs__msg__LabeledPointClouds * msg)
{
  if (!msg) {
    return;
  }
  // elements
  robo_planner_msgs__msg__LabeledPointCloud__Sequence__fini(&msg->elements);
}

bool
robo_planner_msgs__msg__LabeledPointClouds__are_equal(const robo_planner_msgs__msg__LabeledPointClouds * lhs, const robo_planner_msgs__msg__LabeledPointClouds * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // elements
  if (!robo_planner_msgs__msg__LabeledPointCloud__Sequence__are_equal(
      &(lhs->elements), &(rhs->elements)))
  {
    return false;
  }
  return true;
}

bool
robo_planner_msgs__msg__LabeledPointClouds__copy(
  const robo_planner_msgs__msg__LabeledPointClouds * input,
  robo_planner_msgs__msg__LabeledPointClouds * output)
{
  if (!input || !output) {
    return false;
  }
  // elements
  if (!robo_planner_msgs__msg__LabeledPointCloud__Sequence__copy(
      &(input->elements), &(output->elements)))
  {
    return false;
  }
  return true;
}

robo_planner_msgs__msg__LabeledPointClouds *
robo_planner_msgs__msg__LabeledPointClouds__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__msg__LabeledPointClouds * msg = (robo_planner_msgs__msg__LabeledPointClouds *)allocator.allocate(sizeof(robo_planner_msgs__msg__LabeledPointClouds), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robo_planner_msgs__msg__LabeledPointClouds));
  bool success = robo_planner_msgs__msg__LabeledPointClouds__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robo_planner_msgs__msg__LabeledPointClouds__destroy(robo_planner_msgs__msg__LabeledPointClouds * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robo_planner_msgs__msg__LabeledPointClouds__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robo_planner_msgs__msg__LabeledPointClouds__Sequence__init(robo_planner_msgs__msg__LabeledPointClouds__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__msg__LabeledPointClouds * data = NULL;

  if (size) {
    data = (robo_planner_msgs__msg__LabeledPointClouds *)allocator.zero_allocate(size, sizeof(robo_planner_msgs__msg__LabeledPointClouds), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robo_planner_msgs__msg__LabeledPointClouds__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robo_planner_msgs__msg__LabeledPointClouds__fini(&data[i - 1]);
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
robo_planner_msgs__msg__LabeledPointClouds__Sequence__fini(robo_planner_msgs__msg__LabeledPointClouds__Sequence * array)
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
      robo_planner_msgs__msg__LabeledPointClouds__fini(&array->data[i]);
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

robo_planner_msgs__msg__LabeledPointClouds__Sequence *
robo_planner_msgs__msg__LabeledPointClouds__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__msg__LabeledPointClouds__Sequence * array = (robo_planner_msgs__msg__LabeledPointClouds__Sequence *)allocator.allocate(sizeof(robo_planner_msgs__msg__LabeledPointClouds__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robo_planner_msgs__msg__LabeledPointClouds__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robo_planner_msgs__msg__LabeledPointClouds__Sequence__destroy(robo_planner_msgs__msg__LabeledPointClouds__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robo_planner_msgs__msg__LabeledPointClouds__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robo_planner_msgs__msg__LabeledPointClouds__Sequence__are_equal(const robo_planner_msgs__msg__LabeledPointClouds__Sequence * lhs, const robo_planner_msgs__msg__LabeledPointClouds__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robo_planner_msgs__msg__LabeledPointClouds__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robo_planner_msgs__msg__LabeledPointClouds__Sequence__copy(
  const robo_planner_msgs__msg__LabeledPointClouds__Sequence * input,
  robo_planner_msgs__msg__LabeledPointClouds__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robo_planner_msgs__msg__LabeledPointClouds);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robo_planner_msgs__msg__LabeledPointClouds * data =
      (robo_planner_msgs__msg__LabeledPointClouds *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robo_planner_msgs__msg__LabeledPointClouds__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robo_planner_msgs__msg__LabeledPointClouds__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robo_planner_msgs__msg__LabeledPointClouds__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
