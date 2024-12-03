// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from opcua_interfaces:msg/ActuatorWrite.idl
// generated code does not contain a copyright notice
#include "opcua_interfaces/msg/detail/actuator_write__rosidl_typesupport_fastrtps_cpp.hpp"
#include "opcua_interfaces/msg/detail/actuator_write__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace opcua_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces
cdr_serialize(
  const opcua_interfaces::msg::ActuatorWrite & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: actuator_id
  cdr << ros_message.actuator_id;
  // Member: actuator_write_type
  cdr << ros_message.actuator_write_type;
  // Member: actuator_command_bool1
  cdr << (ros_message.actuator_command_bool1 ? true : false);
  // Member: actuator_command_bool2
  cdr << (ros_message.actuator_command_bool2 ? true : false);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  opcua_interfaces::msg::ActuatorWrite & ros_message)
{
  // Member: actuator_id
  cdr >> ros_message.actuator_id;

  // Member: actuator_write_type
  cdr >> ros_message.actuator_write_type;

  // Member: actuator_command_bool1
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.actuator_command_bool1 = tmp ? true : false;
  }

  // Member: actuator_command_bool2
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.actuator_command_bool2 = tmp ? true : false;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces
get_serialized_size(
  const opcua_interfaces::msg::ActuatorWrite & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: actuator_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.actuator_id.size() + 1);
  // Member: actuator_write_type
  {
    size_t item_size = sizeof(ros_message.actuator_write_type);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: actuator_command_bool1
  {
    size_t item_size = sizeof(ros_message.actuator_command_bool1);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: actuator_command_bool2
  {
    size_t item_size = sizeof(ros_message.actuator_command_bool2);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces
max_serialized_size_ActuatorWrite(
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


  // Member: actuator_id
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: actuator_write_type
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: actuator_command_bool1
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: actuator_command_bool2
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = opcua_interfaces::msg::ActuatorWrite;
    is_plain =
      (
      offsetof(DataType, actuator_command_bool2) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ActuatorWrite__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const opcua_interfaces::msg::ActuatorWrite *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ActuatorWrite__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<opcua_interfaces::msg::ActuatorWrite *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ActuatorWrite__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const opcua_interfaces::msg::ActuatorWrite *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ActuatorWrite__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ActuatorWrite(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ActuatorWrite__callbacks = {
  "opcua_interfaces::msg",
  "ActuatorWrite",
  _ActuatorWrite__cdr_serialize,
  _ActuatorWrite__cdr_deserialize,
  _ActuatorWrite__get_serialized_size,
  _ActuatorWrite__max_serialized_size
};

static rosidl_message_type_support_t _ActuatorWrite__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ActuatorWrite__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace opcua_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_opcua_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<opcua_interfaces::msg::ActuatorWrite>()
{
  return &opcua_interfaces::msg::typesupport_fastrtps_cpp::_ActuatorWrite__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, opcua_interfaces, msg, ActuatorWrite)() {
  return &opcua_interfaces::msg::typesupport_fastrtps_cpp::_ActuatorWrite__handle;
}

#ifdef __cplusplus
}
#endif
