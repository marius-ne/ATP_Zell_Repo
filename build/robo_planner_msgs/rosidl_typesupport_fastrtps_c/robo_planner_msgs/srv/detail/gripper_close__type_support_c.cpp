// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from robo_planner_msgs:srv/GripperClose.idl
// generated code does not contain a copyright notice
#include "robo_planner_msgs/srv/detail/gripper_close__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "robo_planner_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "robo_planner_msgs/srv/detail/gripper_close__struct.h"
#include "robo_planner_msgs/srv/detail/gripper_close__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _GripperClose_Request__ros_msg_type = robo_planner_msgs__srv__GripperClose_Request;

static bool _GripperClose_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GripperClose_Request__ros_msg_type * ros_message = static_cast<const _GripperClose_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: dummyinput
  {
    cdr << ros_message->dummyinput;
  }

  return true;
}

static bool _GripperClose_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GripperClose_Request__ros_msg_type * ros_message = static_cast<_GripperClose_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: dummyinput
  {
    cdr >> ros_message->dummyinput;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robo_planner_msgs
size_t get_serialized_size_robo_planner_msgs__srv__GripperClose_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GripperClose_Request__ros_msg_type * ros_message = static_cast<const _GripperClose_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name dummyinput
  {
    size_t item_size = sizeof(ros_message->dummyinput);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _GripperClose_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_robo_planner_msgs__srv__GripperClose_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robo_planner_msgs
size_t max_serialized_size_robo_planner_msgs__srv__GripperClose_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: dummyinput
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robo_planner_msgs__srv__GripperClose_Request;
    is_plain =
      (
      offsetof(DataType, dummyinput) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _GripperClose_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_robo_planner_msgs__srv__GripperClose_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_GripperClose_Request = {
  "robo_planner_msgs::srv",
  "GripperClose_Request",
  _GripperClose_Request__cdr_serialize,
  _GripperClose_Request__cdr_deserialize,
  _GripperClose_Request__get_serialized_size,
  _GripperClose_Request__max_serialized_size
};

static rosidl_message_type_support_t _GripperClose_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GripperClose_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robo_planner_msgs, srv, GripperClose_Request)() {
  return &_GripperClose_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "robo_planner_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "robo_planner_msgs/srv/detail/gripper_close__struct.h"
// already included above
// #include "robo_planner_msgs/srv/detail/gripper_close__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _GripperClose_Response__ros_msg_type = robo_planner_msgs__srv__GripperClose_Response;

static bool _GripperClose_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GripperClose_Response__ros_msg_type * ros_message = static_cast<const _GripperClose_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: result
  {
    cdr << ros_message->result;
  }

  return true;
}

static bool _GripperClose_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GripperClose_Response__ros_msg_type * ros_message = static_cast<_GripperClose_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: result
  {
    cdr >> ros_message->result;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robo_planner_msgs
size_t get_serialized_size_robo_planner_msgs__srv__GripperClose_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GripperClose_Response__ros_msg_type * ros_message = static_cast<const _GripperClose_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name result
  {
    size_t item_size = sizeof(ros_message->result);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _GripperClose_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_robo_planner_msgs__srv__GripperClose_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robo_planner_msgs
size_t max_serialized_size_robo_planner_msgs__srv__GripperClose_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: result
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robo_planner_msgs__srv__GripperClose_Response;
    is_plain =
      (
      offsetof(DataType, result) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _GripperClose_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_robo_planner_msgs__srv__GripperClose_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_GripperClose_Response = {
  "robo_planner_msgs::srv",
  "GripperClose_Response",
  _GripperClose_Response__cdr_serialize,
  _GripperClose_Response__cdr_deserialize,
  _GripperClose_Response__get_serialized_size,
  _GripperClose_Response__max_serialized_size
};

static rosidl_message_type_support_t _GripperClose_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GripperClose_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robo_planner_msgs, srv, GripperClose_Response)() {
  return &_GripperClose_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "robo_planner_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "robo_planner_msgs/srv/gripper_close.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t GripperClose__callbacks = {
  "robo_planner_msgs::srv",
  "GripperClose",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robo_planner_msgs, srv, GripperClose_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robo_planner_msgs, srv, GripperClose_Response)(),
};

static rosidl_service_type_support_t GripperClose__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &GripperClose__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robo_planner_msgs, srv, GripperClose)() {
  return &GripperClose__handle;
}

#if defined(__cplusplus)
}
#endif
