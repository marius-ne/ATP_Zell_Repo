// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from wzlscheduler_interfaces:msg/LabeledPointCloud.idl
// generated code does not contain a copyright notice
#include "wzlscheduler_interfaces/msg/detail/labeled_point_cloud__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `label`
#include "rosidl_runtime_c/string_functions.h"
// Member `poseorigin`
// Member `posecad`
#include "geometry_msgs/msg/detail/pose__functions.h"
// Member `pointcloud`
#include "sensor_msgs/msg/detail/point_cloud2__functions.h"

bool
wzlscheduler_interfaces__msg__LabeledPointCloud__init(wzlscheduler_interfaces__msg__LabeledPointCloud * msg)
{
  if (!msg) {
    return false;
  }
  // label
  if (!rosidl_runtime_c__String__init(&msg->label)) {
    wzlscheduler_interfaces__msg__LabeledPointCloud__fini(msg);
    return false;
  }
  // poseorigin
  if (!geometry_msgs__msg__Pose__init(&msg->poseorigin)) {
    wzlscheduler_interfaces__msg__LabeledPointCloud__fini(msg);
    return false;
  }
  // posecad
  if (!geometry_msgs__msg__Pose__init(&msg->posecad)) {
    wzlscheduler_interfaces__msg__LabeledPointCloud__fini(msg);
    return false;
  }
  // pointcloud
  if (!sensor_msgs__msg__PointCloud2__init(&msg->pointcloud)) {
    wzlscheduler_interfaces__msg__LabeledPointCloud__fini(msg);
    return false;
  }
  return true;
}

void
wzlscheduler_interfaces__msg__LabeledPointCloud__fini(wzlscheduler_interfaces__msg__LabeledPointCloud * msg)
{
  if (!msg) {
    return;
  }
  // label
  rosidl_runtime_c__String__fini(&msg->label);
  // poseorigin
  geometry_msgs__msg__Pose__fini(&msg->poseorigin);
  // posecad
  geometry_msgs__msg__Pose__fini(&msg->posecad);
  // pointcloud
  sensor_msgs__msg__PointCloud2__fini(&msg->pointcloud);
}

bool
wzlscheduler_interfaces__msg__LabeledPointCloud__are_equal(const wzlscheduler_interfaces__msg__LabeledPointCloud * lhs, const wzlscheduler_interfaces__msg__LabeledPointCloud * rhs)
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
  // poseorigin
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->poseorigin), &(rhs->poseorigin)))
  {
    return false;
  }
  // posecad
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->posecad), &(rhs->posecad)))
  {
    return false;
  }
  // pointcloud
  if (!sensor_msgs__msg__PointCloud2__are_equal(
      &(lhs->pointcloud), &(rhs->pointcloud)))
  {
    return false;
  }
  return true;
}

bool
wzlscheduler_interfaces__msg__LabeledPointCloud__copy(
  const wzlscheduler_interfaces__msg__LabeledPointCloud * input,
  wzlscheduler_interfaces__msg__LabeledPointCloud * output)
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
  // poseorigin
  if (!geometry_msgs__msg__Pose__copy(
      &(input->poseorigin), &(output->poseorigin)))
  {
    return false;
  }
  // posecad
  if (!geometry_msgs__msg__Pose__copy(
      &(input->posecad), &(output->posecad)))
  {
    return false;
  }
  // pointcloud
  if (!sensor_msgs__msg__PointCloud2__copy(
      &(input->pointcloud), &(output->pointcloud)))
  {
    return false;
  }
  return true;
}

wzlscheduler_interfaces__msg__LabeledPointCloud *
wzlscheduler_interfaces__msg__LabeledPointCloud__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__LabeledPointCloud * msg = (wzlscheduler_interfaces__msg__LabeledPointCloud *)allocator.allocate(sizeof(wzlscheduler_interfaces__msg__LabeledPointCloud), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wzlscheduler_interfaces__msg__LabeledPointCloud));
  bool success = wzlscheduler_interfaces__msg__LabeledPointCloud__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wzlscheduler_interfaces__msg__LabeledPointCloud__destroy(wzlscheduler_interfaces__msg__LabeledPointCloud * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wzlscheduler_interfaces__msg__LabeledPointCloud__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__init(wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__LabeledPointCloud * data = NULL;

  if (size) {
    data = (wzlscheduler_interfaces__msg__LabeledPointCloud *)allocator.zero_allocate(size, sizeof(wzlscheduler_interfaces__msg__LabeledPointCloud), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wzlscheduler_interfaces__msg__LabeledPointCloud__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wzlscheduler_interfaces__msg__LabeledPointCloud__fini(&data[i - 1]);
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
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__fini(wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * array)
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
      wzlscheduler_interfaces__msg__LabeledPointCloud__fini(&array->data[i]);
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

wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence *
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * array = (wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence *)allocator.allocate(sizeof(wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__destroy(wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__are_equal(const wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * lhs, const wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wzlscheduler_interfaces__msg__LabeledPointCloud__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence__copy(
  const wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * input,
  wzlscheduler_interfaces__msg__LabeledPointCloud__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wzlscheduler_interfaces__msg__LabeledPointCloud);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wzlscheduler_interfaces__msg__LabeledPointCloud * data =
      (wzlscheduler_interfaces__msg__LabeledPointCloud *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wzlscheduler_interfaces__msg__LabeledPointCloud__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wzlscheduler_interfaces__msg__LabeledPointCloud__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wzlscheduler_interfaces__msg__LabeledPointCloud__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
