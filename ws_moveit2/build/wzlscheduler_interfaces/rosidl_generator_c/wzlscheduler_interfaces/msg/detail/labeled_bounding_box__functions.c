// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from wzlscheduler_interfaces:msg/LabeledBoundingBox.idl
// generated code does not contain a copyright notice
#include "wzlscheduler_interfaces/msg/detail/labeled_bounding_box__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `label`
#include "rosidl_runtime_c/string_functions.h"

bool
wzlscheduler_interfaces__msg__LabeledBoundingBox__init(wzlscheduler_interfaces__msg__LabeledBoundingBox * msg)
{
  if (!msg) {
    return false;
  }
  // label
  if (!rosidl_runtime_c__String__init(&msg->label)) {
    wzlscheduler_interfaces__msg__LabeledBoundingBox__fini(msg);
    return false;
  }
  // x
  // y
  // width
  // height
  return true;
}

void
wzlscheduler_interfaces__msg__LabeledBoundingBox__fini(wzlscheduler_interfaces__msg__LabeledBoundingBox * msg)
{
  if (!msg) {
    return;
  }
  // label
  rosidl_runtime_c__String__fini(&msg->label);
  // x
  // y
  // width
  // height
}

bool
wzlscheduler_interfaces__msg__LabeledBoundingBox__are_equal(const wzlscheduler_interfaces__msg__LabeledBoundingBox * lhs, const wzlscheduler_interfaces__msg__LabeledBoundingBox * rhs)
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
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  return true;
}

bool
wzlscheduler_interfaces__msg__LabeledBoundingBox__copy(
  const wzlscheduler_interfaces__msg__LabeledBoundingBox * input,
  wzlscheduler_interfaces__msg__LabeledBoundingBox * output)
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
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // width
  output->width = input->width;
  // height
  output->height = input->height;
  return true;
}

wzlscheduler_interfaces__msg__LabeledBoundingBox *
wzlscheduler_interfaces__msg__LabeledBoundingBox__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__LabeledBoundingBox * msg = (wzlscheduler_interfaces__msg__LabeledBoundingBox *)allocator.allocate(sizeof(wzlscheduler_interfaces__msg__LabeledBoundingBox), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(wzlscheduler_interfaces__msg__LabeledBoundingBox));
  bool success = wzlscheduler_interfaces__msg__LabeledBoundingBox__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
wzlscheduler_interfaces__msg__LabeledBoundingBox__destroy(wzlscheduler_interfaces__msg__LabeledBoundingBox * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    wzlscheduler_interfaces__msg__LabeledBoundingBox__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence__init(wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__LabeledBoundingBox * data = NULL;

  if (size) {
    data = (wzlscheduler_interfaces__msg__LabeledBoundingBox *)allocator.zero_allocate(size, sizeof(wzlscheduler_interfaces__msg__LabeledBoundingBox), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = wzlscheduler_interfaces__msg__LabeledBoundingBox__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        wzlscheduler_interfaces__msg__LabeledBoundingBox__fini(&data[i - 1]);
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
wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence__fini(wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence * array)
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
      wzlscheduler_interfaces__msg__LabeledBoundingBox__fini(&array->data[i]);
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

wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence *
wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence * array = (wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence *)allocator.allocate(sizeof(wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence__destroy(wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence__are_equal(const wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence * lhs, const wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!wzlscheduler_interfaces__msg__LabeledBoundingBox__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence__copy(
  const wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence * input,
  wzlscheduler_interfaces__msg__LabeledBoundingBox__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(wzlscheduler_interfaces__msg__LabeledBoundingBox);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    wzlscheduler_interfaces__msg__LabeledBoundingBox * data =
      (wzlscheduler_interfaces__msg__LabeledBoundingBox *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!wzlscheduler_interfaces__msg__LabeledBoundingBox__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          wzlscheduler_interfaces__msg__LabeledBoundingBox__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!wzlscheduler_interfaces__msg__LabeledBoundingBox__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
