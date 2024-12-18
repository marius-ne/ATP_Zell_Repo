// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from opcua_interfaces_io_link:msg/SensorRead.idl
// generated code does not contain a copyright notice
#include "opcua_interfaces_io_link/msg/detail/sensor_read__rosidl_typesupport_fastrtps_cpp.hpp"
#include "opcua_interfaces_io_link/msg/detail/sensor_read__struct.hpp"

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

namespace opcua_interfaces_io_link
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link
cdr_serialize(
  const opcua_interfaces_io_link::msg::SensorRead & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: sensor_id
  cdr << ros_message.sensor_id;
  // Member: sensor_read_type
  cdr << ros_message.sensor_read_type;
  // Member: sensor_value_bool
  cdr << (ros_message.sensor_value_bool ? true : false);
  // Member: sensor_value_int
  cdr << ros_message.sensor_value_int;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  opcua_interfaces_io_link::msg::SensorRead & ros_message)
{
  // Member: sensor_id
  cdr >> ros_message.sensor_id;

  // Member: sensor_read_type
  cdr >> ros_message.sensor_read_type;

  // Member: sensor_value_bool
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.sensor_value_bool = tmp ? true : false;
  }

  // Member: sensor_value_int
  cdr >> ros_message.sensor_value_int;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link
get_serialized_size(
  const opcua_interfaces_io_link::msg::SensorRead & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: sensor_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.sensor_id.size() + 1);
  // Member: sensor_read_type
  {
    size_t item_size = sizeof(ros_message.sensor_read_type);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: sensor_value_bool
  {
    size_t item_size = sizeof(ros_message.sensor_value_bool);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: sensor_value_int
  {
    size_t item_size = sizeof(ros_message.sensor_value_int);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_opcua_interfaces_io_link
max_serialized_size_SensorRead(
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


  // Member: sensor_id
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

  // Member: sensor_read_type
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: sensor_value_bool
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: sensor_value_int
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = opcua_interfaces_io_link::msg::SensorRead;
    is_plain =
      (
      offsetof(DataType, sensor_value_int) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _SensorRead__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const opcua_interfaces_io_link::msg::SensorRead *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _SensorRead__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<opcua_interfaces_io_link::msg::SensorRead *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _SensorRead__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const opcua_interfaces_io_link::msg::SensorRead *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _SensorRead__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_SensorRead(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _SensorRead__callbacks = {
  "opcua_interfaces_io_link::msg",
  "SensorRead",
  _SensorRead__cdr_serialize,
  _SensorRead__cdr_deserialize,
  _SensorRead__get_serialized_size,
  _SensorRead__max_serialized_size
};

static rosidl_message_type_support_t _SensorRead__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SensorRead__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace opcua_interfaces_io_link

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_opcua_interfaces_io_link
const rosidl_message_type_support_t *
get_message_type_support_handle<opcua_interfaces_io_link::msg::SensorRead>()
{
  return &opcua_interfaces_io_link::msg::typesupport_fastrtps_cpp::_SensorRead__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, opcua_interfaces_io_link, msg, SensorRead)() {
  return &opcua_interfaces_io_link::msg::typesupport_fastrtps_cpp::_SensorRead__handle;
}

#ifdef __cplusplus
}
#endif
