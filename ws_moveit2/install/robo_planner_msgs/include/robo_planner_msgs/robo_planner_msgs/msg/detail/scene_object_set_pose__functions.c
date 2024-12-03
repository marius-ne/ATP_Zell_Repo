// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robo_planner_msgs:msg/SceneObjectSetPose.idl
// generated code does not contain a copyright notice
#include "robo_planner_msgs/msg/detail/scene_object_set_pose__functions.h"

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
robo_planner_msgs__msg__SceneObjectSetPose__init(robo_planner_msgs__msg__SceneObjectSetPose * msg)
{
  if (!msg) {
    return false;
  }
  // name
  if (!rosidl_runtime_c__String__init(&msg->name)) {
    robo_planner_msgs__msg__SceneObjectSetPose__fini(msg);
    return false;
  }
  // coordinates
  if (!geometry_msgs__msg__Pose__init(&msg->coordinates)) {
    robo_planner_msgs__msg__SceneObjectSetPose__fini(msg);
    return false;
  }
  return true;
}

void
robo_planner_msgs__msg__SceneObjectSetPose__fini(robo_planner_msgs__msg__SceneObjectSetPose * msg)
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
robo_planner_msgs__msg__SceneObjectSetPose__are_equal(const robo_planner_msgs__msg__SceneObjectSetPose * lhs, const robo_planner_msgs__msg__SceneObjectSetPose * rhs)
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
robo_planner_msgs__msg__SceneObjectSetPose__copy(
  const robo_planner_msgs__msg__SceneObjectSetPose * input,
  robo_planner_msgs__msg__SceneObjectSetPose * output)
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

robo_planner_msgs__msg__SceneObjectSetPose *
robo_planner_msgs__msg__SceneObjectSetPose__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__msg__SceneObjectSetPose * msg = (robo_planner_msgs__msg__SceneObjectSetPose *)allocator.allocate(sizeof(robo_planner_msgs__msg__SceneObjectSetPose), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robo_planner_msgs__msg__SceneObjectSetPose));
  bool success = robo_planner_msgs__msg__SceneObjectSetPose__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robo_planner_msgs__msg__SceneObjectSetPose__destroy(robo_planner_msgs__msg__SceneObjectSetPose * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robo_planner_msgs__msg__SceneObjectSetPose__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__init(robo_planner_msgs__msg__SceneObjectSetPose__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__msg__SceneObjectSetPose * data = NULL;

  if (size) {
    data = (robo_planner_msgs__msg__SceneObjectSetPose *)allocator.zero_allocate(size, sizeof(robo_planner_msgs__msg__SceneObjectSetPose), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robo_planner_msgs__msg__SceneObjectSetPose__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robo_planner_msgs__msg__SceneObjectSetPose__fini(&data[i - 1]);
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
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__fini(robo_planner_msgs__msg__SceneObjectSetPose__Sequence * array)
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
      robo_planner_msgs__msg__SceneObjectSetPose__fini(&array->data[i]);
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

robo_planner_msgs__msg__SceneObjectSetPose__Sequence *
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robo_planner_msgs__msg__SceneObjectSetPose__Sequence * array = (robo_planner_msgs__msg__SceneObjectSetPose__Sequence *)allocator.allocate(sizeof(robo_planner_msgs__msg__SceneObjectSetPose__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robo_planner_msgs__msg__SceneObjectSetPose__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__destroy(robo_planner_msgs__msg__SceneObjectSetPose__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robo_planner_msgs__msg__SceneObjectSetPose__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__are_equal(const robo_planner_msgs__msg__SceneObjectSetPose__Sequence * lhs, const robo_planner_msgs__msg__SceneObjectSetPose__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robo_planner_msgs__msg__SceneObjectSetPose__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robo_planner_msgs__msg__SceneObjectSetPose__Sequence__copy(
  const robo_planner_msgs__msg__SceneObjectSetPose__Sequence * input,
  robo_planner_msgs__msg__SceneObjectSetPose__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robo_planner_msgs__msg__SceneObjectSetPose);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robo_planner_msgs__msg__SceneObjectSetPose * data =
      (robo_planner_msgs__msg__SceneObjectSetPose *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robo_planner_msgs__msg__SceneObjectSetPose__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robo_planner_msgs__msg__SceneObjectSetPose__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robo_planner_msgs__msg__SceneObjectSetPose__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
