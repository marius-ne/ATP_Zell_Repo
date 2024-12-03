// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from opcua_interfaces:msg/ActuatorWrite.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__TRAITS_HPP_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "opcua_interfaces/msg/detail/actuator_write__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace opcua_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ActuatorWrite & msg,
  std::ostream & out)
{
  out << "{";
  // member: actuator_id
  {
    out << "actuator_id: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_id, out);
    out << ", ";
  }

  // member: actuator_write_type
  {
    out << "actuator_write_type: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_write_type, out);
    out << ", ";
  }

  // member: actuator_command_bool1
  {
    out << "actuator_command_bool1: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_command_bool1, out);
    out << ", ";
  }

  // member: actuator_command_bool2
  {
    out << "actuator_command_bool2: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_command_bool2, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ActuatorWrite & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: actuator_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "actuator_id: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_id, out);
    out << "\n";
  }

  // member: actuator_write_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "actuator_write_type: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_write_type, out);
    out << "\n";
  }

  // member: actuator_command_bool1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "actuator_command_bool1: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_command_bool1, out);
    out << "\n";
  }

  // member: actuator_command_bool2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "actuator_command_bool2: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_command_bool2, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ActuatorWrite & msg, bool use_flow_style = false)
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

}  // namespace opcua_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use opcua_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const opcua_interfaces::msg::ActuatorWrite & msg,
  std::ostream & out, size_t indentation = 0)
{
  opcua_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use opcua_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const opcua_interfaces::msg::ActuatorWrite & msg)
{
  return opcua_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<opcua_interfaces::msg::ActuatorWrite>()
{
  return "opcua_interfaces::msg::ActuatorWrite";
}

template<>
inline const char * name<opcua_interfaces::msg::ActuatorWrite>()
{
  return "opcua_interfaces/msg/ActuatorWrite";
}

template<>
struct has_fixed_size<opcua_interfaces::msg::ActuatorWrite>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<opcua_interfaces::msg::ActuatorWrite>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<opcua_interfaces::msg::ActuatorWrite>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_WRITE__TRAITS_HPP_
