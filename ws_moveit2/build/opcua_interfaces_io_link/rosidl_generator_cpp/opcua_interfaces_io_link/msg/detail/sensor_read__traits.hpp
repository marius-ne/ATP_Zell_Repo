// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from opcua_interfaces_io_link:msg/SensorRead.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__TRAITS_HPP_
#define OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "opcua_interfaces_io_link/msg/detail/sensor_read__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace opcua_interfaces_io_link
{

namespace msg
{

inline void to_flow_style_yaml(
  const SensorRead & msg,
  std::ostream & out)
{
  out << "{";
  // member: sensor_id
  {
    out << "sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_id, out);
    out << ", ";
  }

  // member: sensor_read_type
  {
    out << "sensor_read_type: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_read_type, out);
    out << ", ";
  }

  // member: sensor_value_bool
  {
    out << "sensor_value_bool: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_value_bool, out);
    out << ", ";
  }

  // member: sensor_value_int
  {
    out << "sensor_value_int: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_value_int, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SensorRead & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: sensor_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sensor_id: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_id, out);
    out << "\n";
  }

  // member: sensor_read_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sensor_read_type: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_read_type, out);
    out << "\n";
  }

  // member: sensor_value_bool
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sensor_value_bool: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_value_bool, out);
    out << "\n";
  }

  // member: sensor_value_int
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sensor_value_int: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_value_int, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SensorRead & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace opcua_interfaces_io_link

namespace rosidl_generator_traits
{

[[deprecated("use opcua_interfaces_io_link::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const opcua_interfaces_io_link::msg::SensorRead & msg,
  std::ostream & out, size_t indentation = 0)
{
  opcua_interfaces_io_link::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use opcua_interfaces_io_link::msg::to_yaml() instead")]]
inline std::string to_yaml(const opcua_interfaces_io_link::msg::SensorRead & msg)
{
  return opcua_interfaces_io_link::msg::to_yaml(msg);
}

template<>
inline const char * data_type<opcua_interfaces_io_link::msg::SensorRead>()
{
  return "opcua_interfaces_io_link::msg::SensorRead";
}

template<>
inline const char * name<opcua_interfaces_io_link::msg::SensorRead>()
{
  return "opcua_interfaces_io_link/msg/SensorRead";
}

template<>
struct has_fixed_size<opcua_interfaces_io_link::msg::SensorRead>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<opcua_interfaces_io_link::msg::SensorRead>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<opcua_interfaces_io_link::msg::SensorRead>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OPCUA_INTERFACES_IO_LINK__MSG__DETAIL__SENSOR_READ__TRAITS_HPP_
