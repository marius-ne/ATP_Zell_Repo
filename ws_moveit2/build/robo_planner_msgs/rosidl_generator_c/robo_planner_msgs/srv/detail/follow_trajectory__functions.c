// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robo_planner_msgs:srv/FollowTrajectory.idl
// generated code does not contain a copyright notice
#include "robo_planner_msgs/srv/detail/follow_trajectory__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `supportpoints`
#include "geometry_msgs/msg/detail/pose__functions.h"

bool
robo_planner_msgs__srv__FollowTrajectory_Request__init(robo_planner_msgs__srv__FollowTrajectory_Request * msg)
{
  if (!msg) {
    return false;
  }
  // supportpoints
  if (!geometry_msgs__msg__Pose__Sequence__init(&msg->supportpoints, 0)) {
    robo_planner_msgs__srv__FollowTrajectory_Request__fini(msg);
    return false;
  }
  // value
  return true;
}

void
robo_planner_msgs__srv__FollowTrajectory_Request__fini(robo_planner_msgs__srv__FollowTrajectory_Request * msg)
{
  if (!msg) {
    return;
  }
  // supportpoints
  geometry_msgs__msg__Pose__Sequence__fini(&msg->supportpoints);
  // value
}

bool
robo_planner_msgs__srv__FollowTrajectory_Request__are_equal(const robo_planner_msgs__srv__FollowTrajectory_Request * lhs, const robo_planner_msgs__srv__FollowTrajectory_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // supportpoints
  if (!geometry_msgs__msg__Pose__Sequence__are_equal(
      &(lhs->supportpoints), &(rhs->supportpoints)))
  {
    return false;
  }
  // value
  if (lhs->value != rhs->value) {
    return false;
  }
  return true;
}

bool
robo_planner_msgs__srv__FollowTrajectory_Request__copy(
  const robo_planner_msgs__srv__FollowTrajectory_Request * input,
  robo_planner_msgs__srv__FollowTrajectory_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // supportpoints
  if (!geometry_msgs__msg__Pose__Sequence__copy(
      &(input->supportpoints), &(output->supportpoints)))
  {
    return false;
  }
  // value
  output->value = input->value;
  return true;
}

robo_planner_msgs__srv__FollowTrajectory_Request *
robo_planner_msgs__srv__FollowTrajectory_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__srv__FollowTrajectory_Request * msg = (robo_planner_msgs__srv__FollowTrajectory_Request *)allocator.allocate(sizeof(robo_planner_msgs__srv__FollowTrajectory_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robo_planner_msgs__srv__FollowTrajectory_Request));
  bool success = robo_planner_msgs__srv__FollowTrajectory_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robo_planner_msgs__srv__FollowTrajectory_Request__destroy(robo_planner_msgs__srv__FollowTrajectory_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robo_planner_msgs__srv__FollowTrajectory_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robo_planner_msgs__srv__FollowTrajectory_Request__Sequence__init(robo_planner_msgs__srv__FollowTrajectory_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__srv__FollowTrajectory_Request * data = NULL;

  if (size) {
    data = (robo_planner_msgs__srv__FollowTrajectory_Request *)allocator.zero_allocate(size, sizeof(robo_planner_msgs__srv__FollowTrajectory_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robo_planner_msgs__srv__FollowTrajectory_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robo_planner_msgs__srv__FollowTrajectory_Request__fini(&data[i - 1]);
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
robo_planner_msgs__srv__FollowTrajectory_Request__Sequence__fini(robo_planner_msgs__srv__FollowTrajectory_Request__Sequence * array)
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
      robo_planner_msgs__srv__FollowTrajectory_Request__fini(&array->data[i]);
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

robo_planner_msgs__srv__FollowTrajectory_Request__Sequence *
robo_planner_msgs__srv__FollowTrajectory_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__srv__FollowTrajectory_Request__Sequence * array = (robo_planner_msgs__srv__FollowTrajectory_Request__Sequence *)allocator.allocate(sizeof(robo_planner_msgs__srv__FollowTrajectory_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robo_planner_msgs__srv__FollowTrajectory_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robo_planner_msgs__srv__FollowTrajectory_Request__Sequence__destroy(robo_planner_msgs__srv__FollowTrajectory_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robo_planner_msgs__srv__FollowTrajectory_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robo_planner_msgs__srv__FollowTrajectory_Request__Sequence__are_equal(const robo_planner_msgs__srv__FollowTrajectory_Request__Sequence * lhs, const robo_planner_msgs__srv__FollowTrajectory_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robo_planner_msgs__srv__FollowTrajectory_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robo_planner_msgs__srv__FollowTrajectory_Request__Sequence__copy(
  const robo_planner_msgs__srv__FollowTrajectory_Request__Sequence * input,
  robo_planner_msgs__srv__FollowTrajectory_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robo_planner_msgs__srv__FollowTrajectory_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robo_planner_msgs__srv__FollowTrajectory_Request * data =
      (robo_planner_msgs__srv__FollowTrajectory_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robo_planner_msgs__srv__FollowTrajectory_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robo_planner_msgs__srv__FollowTrajectory_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robo_planner_msgs__srv__FollowTrajectory_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
robo_planner_msgs__srv__FollowTrajectory_Response__init(robo_planner_msgs__srv__FollowTrajectory_Response * msg)
{
  if (!msg) {
    return false;
  }
  // result
  return true;
}

void
robo_planner_msgs__srv__FollowTrajectory_Response__fini(robo_planner_msgs__srv__FollowTrajectory_Response * msg)
{
  if (!msg) {
    return;
  }
  // result
}

bool
robo_planner_msgs__srv__FollowTrajectory_Response__are_equal(const robo_planner_msgs__srv__FollowTrajectory_Response * lhs, const robo_planner_msgs__srv__FollowTrajectory_Response * rhs)
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
robo_planner_msgs__srv__FollowTrajectory_Response__copy(
  const robo_planner_msgs__srv__FollowTrajectory_Response * input,
  robo_planner_msgs__srv__FollowTrajectory_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // result
  output->result = input->result;
  return true;
}

robo_planner_msgs__srv__FollowTrajectory_Response *
robo_planner_msgs__srv__FollowTrajectory_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__srv__FollowTrajectory_Response * msg = (robo_planner_msgs__srv__FollowTrajectory_Response *)allocator.allocate(sizeof(robo_planner_msgs__srv__FollowTrajectory_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robo_planner_msgs__srv__FollowTrajectory_Response));
  bool success = robo_planner_msgs__srv__FollowTrajectory_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robo_planner_msgs__srv__FollowTrajectory_Response__destroy(robo_planner_msgs__srv__FollowTrajectory_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robo_planner_msgs__srv__FollowTrajectory_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robo_planner_msgs__srv__FollowTrajectory_Response__Sequence__init(robo_planner_msgs__srv__FollowTrajectory_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__srv__FollowTrajectory_Response * data = NULL;

  if (size) {
    data = (robo_planner_msgs__srv__FollowTrajectory_Response *)allocator.zero_allocate(size, sizeof(robo_planner_msgs__srv__FollowTrajectory_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robo_planner_msgs__srv__FollowTrajectory_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robo_planner_msgs__srv__FollowTrajectory_Response__fini(&data[i - 1]);
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
robo_planner_msgs__srv__FollowTrajectory_Response__Sequence__fini(robo_planner_msgs__srv__FollowTrajectory_Response__Sequence * array)
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
      robo_planner_msgs__srv__FollowTrajectory_Response__fini(&array->data[i]);
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

robo_planner_msgs__srv__FollowTrajectory_Response__Sequence *
robo_planner_msgs__srv__FollowTrajectory_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__srv__FollowTrajectory_Response__Sequence * array = (robo_planner_msgs__srv__FollowTrajectory_Response__Sequence *)allocator.allocate(sizeof(robo_planner_msgs__srv__FollowTrajectory_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robo_planner_msgs__srv__FollowTrajectory_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robo_planner_msgs__srv__FollowTrajectory_Response__Sequence__destroy(robo_planner_msgs__srv__FollowTrajectory_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robo_planner_msgs__srv__FollowTrajectory_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robo_planner_msgs__srv__FollowTrajectory_Response__Sequence__are_equal(const robo_planner_msgs__srv__FollowTrajectory_Response__Sequence * lhs, const robo_planner_msgs__srv__FollowTrajectory_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robo_planner_msgs__srv__FollowTrajectory_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robo_planner_msgs__srv__FollowTrajectory_Response__Sequence__copy(
  const robo_planner_msgs__srv__FollowTrajectory_Response__Sequence * input,
  robo_planner_msgs__srv__FollowTrajectory_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robo_planner_msgs__srv__FollowTrajectory_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robo_planner_msgs__srv__FollowTrajectory_Response * data =
      (robo_planner_msgs__srv__FollowTrajectory_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robo_planner_msgs__srv__FollowTrajectory_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robo_planner_msgs__srv__FollowTrajectory_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robo_planner_msgs__srv__FollowTrajectory_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
