// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from robo_planner_msgs:srv/SetRobotValueVelocity.idl
// generated code does not contain a copyright notice
#include "robo_planner_msgs/srv/detail/set_robot_value_velocity__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "robo_planner_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "robo_planner_msgs/srv/detail/set_robot_value_velocity__struct.h"
#include "robo_planner_msgs/srv/detail/set_robot_value_velocity__functions.h"
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


using _SetRobotValueVelocity_Request__ros_msg_type = robo_planner_msgs__srv__SetRobotValueVelocity_Request;

static bool _SetRobotValueVelocity_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SetRobotValueVelocity_Request__ros_msg_type * ros_message = static_cast<const _SetRobotValueVelocity_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: dummyinput
  {
    cdr << ros_message->dummyinput;
  }

  return true;
}

static bool _SetRobotValueVelocity_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SetRobotValueVelocity_Request__ros_msg_type * ros_message = static_cast<_SetRobotValueVelocity_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: dummyinput
  {
    cdr >> ros_message->dummyinput;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robo_planner_msgs
size_t get_serialized_size_robo_planner_msgs__srv__SetRobotValueVelocity_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SetRobotValueVelocity_Request__ros_msg_type * ros_message = static_cast<const _SetRobotValueVelocity_Request__ros_msg_type *>(untyped_ros_message);
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

static uint32_t _SetRobotValueVelocity_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_robo_planner_msgs__srv__SetRobotValueVelocity_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robo_planner_msgs
size_t max_serialized_size_robo_planner_msgs__srv__SetRobotValueVelocity_Request(
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
    using DataType = robo_planner_msgs__srv__SetRobotValueVelocity_Request;
    is_plain =
      (
      offsetof(DataType, dummyinput) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SetRobotValueVelocity_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_robo_planner_msgs__srv__SetRobotValueVelocity_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SetRobotValueVelocity_Request = {
  "robo_planner_msgs::srv",
  "SetRobotValueVelocity_Request",
  _SetRobotValueVelocity_Request__cdr_serialize,
  _SetRobotValueVelocity_Request__cdr_deserialize,
  _SetRobotValueVelocity_Request__get_serialized_size,
  _SetRobotValueVelocity_Request__max_serialized_size
};

static rosidl_message_type_support_t _SetRobotValueVelocity_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SetRobotValueVelocity_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robo_planner_msgs, srv, SetRobotValueVelocity_Request)() {
  return &_SetRobotValueVelocity_Request__type_support;
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
// #include "robo_planner_msgs/srv/detail/set_robot_value_velocity__struct.h"
// already included above
// #include "robo_planner_msgs/srv/detail/set_robot_value_velocity__functions.h"
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


using _SetRobotValueVelocity_Response__ros_msg_type = robo_planner_msgs__srv__SetRobotValueVelocity_Response;

static bool _SetRobotValueVelocity_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SetRobotValueVelocity_Response__ros_msg_type * ros_message = static_cast<const _SetRobotValueVelocity_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: result
  {
    cdr << ros_message->result;
  }

  return true;
}

static bool _SetRobotValueVelocity_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SetRobotValueVelocity_Response__ros_msg_type * ros_message = static_cast<_SetRobotValueVelocity_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: result
  {
    cdr >> ros_message->result;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robo_planner_msgs
size_t get_serialized_size_robo_planner_msgs__srv__SetRobotValueVelocity_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SetRobotValueVelocity_Response__ros_msg_type * ros_message = static_cast<const _SetRobotValueVelocity_Response__ros_msg_type *>(untyped_ros_message);
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

static uint32_t _SetRobotValueVelocity_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_robo_planner_msgs__srv__SetRobotValueVelocity_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robo_planner_msgs
size_t max_serialized_size_robo_planner_msgs__srv__SetRobotValueVelocity_Response(
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
    using DataType = robo_planner_msgs__srv__SetRobotValueVelocity_Response;
    is_plain =
      (
      offsetof(DataType, result) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SetRobotValueVelocity_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_robo_planner_msgs__srv__SetRobotValueVelocity_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SetRobotValueVelocity_Response = {
  "robo_planner_msgs::srv",
  "SetRobotValueVelocity_Response",
  _SetRobotValueVelocity_Response__cdr_serialize,
  _SetRobotValueVelocity_Response__cdr_deserialize,
  _SetRobotValueVelocity_Response__get_serialized_size,
  _SetRobotValueVelocity_Response__max_serialized_size
};

static rosidl_message_type_support_t _SetRobotValueVelocity_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SetRobotValueVelocity_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robo_planner_msgs, srv, SetRobotValueVelocity_Response)() {
  return &_SetRobotValueVelocity_Response__type_support;
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
#include "robo_planner_msgs/srv/set_robot_value_velocity.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t SetRobotValueVelocity__callbacks = {
  "robo_planner_msgs::srv",
  "SetRobotValueVelocity",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robo_planner_msgs, srv, SetRobotValueVelocity_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robo_planner_msgs, srv, SetRobotValueVelocity_Response)(),
};

static rosidl_service_type_support_t SetRobotValueVelocity__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &SetRobotValueVelocity__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robo_planner_msgs, srv, SetRobotValueVelocity)() {
  return &SetRobotValueVelocity__handle;
}

#if defined(__cplusplus)
}
#endif
