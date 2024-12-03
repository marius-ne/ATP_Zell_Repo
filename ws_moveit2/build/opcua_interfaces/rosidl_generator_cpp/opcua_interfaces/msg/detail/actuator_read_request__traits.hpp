// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from opcua_interfaces:msg/ActuatorReadRequest.idl
// generated code does not contain a copyright notice

#ifndef OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__TRAITS_HPP_
#define OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "opcua_interfaces/msg/detail/actuator_read_request__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace opcua_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ActuatorReadRequest & msg,
  std::ostream & out)
{
  out << "{";
  // member: actuator_id
  {
    out << "actuator_id: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_id, out);
    out << ", ";
  }

  // member: actuator_read_type
  {
    out << "actuator_read_type: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_read_type, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ActuatorReadRequest & msg,
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

  // member: actuator_read_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "actuator_read_type: ";
    rosidl_generator_traits::value_to_yaml(msg.actuator_read_type, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ActuatorReadRequest & msg, bool use_flow_style = false)
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
  const opcua_interfaces::msg::ActuatorReadRequest & msg,
  std::ostream & out, size_t indentation = 0)
{
  opcua_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use opcua_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const opcua_interfaces::msg::ActuatorReadRequest & msg)
{
  return opcua_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<opcua_interfaces::msg::ActuatorReadRequest>()
{
  return "opcua_interfaces::msg::ActuatorReadRequest";
}

template<>
inline const char * name<opcua_interfaces::msg::ActuatorReadRequest>()
{
  return "opcua_interfaces/msg/ActuatorReadRequest";
}

template<>
struct has_fixed_size<opcua_interfaces::msg::ActuatorReadRequest>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<opcua_interfaces::msg::ActuatorReadRequest>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<opcua_interfaces::msg::ActuatorReadRequest>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OPCUA_INTERFACES__MSG__DETAIL__ACTUATOR_READ_REQUEST__TRAITS_HPP_
