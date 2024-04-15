// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ur16e_interfaces:msg/LoadObject.idl
// generated code does not contain a copyright notice

#ifndef UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__TRAITS_HPP_
#define UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "ur16e_interfaces/msg/detail/load_object__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'coordinates'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace ur16e_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LoadObject & msg,
  std::ostream & out)
{
  out << "{";
  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: coordinates
  {
    out << "coordinates: ";
    to_flow_style_yaml(msg.coordinates, out);
    out << ", ";
  }

  // member: scale
  {
    out << "scale: ";
    rosidl_generator_traits::value_to_yaml(msg.scale, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LoadObject & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: coordinates
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coordinates:\n";
    to_block_style_yaml(msg.coordinates, out, indentation + 2);
  }

  // member: scale
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "scale: ";
    rosidl_generator_traits::value_to_yaml(msg.scale, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LoadObject & msg, bool use_flow_style = false)
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

}  // namespace ur16e_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use ur16e_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const ur16e_interfaces::msg::LoadObject & msg,
  std::ostream & out, size_t indentation = 0)
{
  ur16e_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use ur16e_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const ur16e_interfaces::msg::LoadObject & msg)
{
  return ur16e_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<ur16e_interfaces::msg::LoadObject>()
{
  return "ur16e_interfaces::msg::LoadObject";
}

template<>
inline const char * name<ur16e_interfaces::msg::LoadObject>()
{
  return "ur16e_interfaces/msg/LoadObject";
}

template<>
struct has_fixed_size<ur16e_interfaces::msg::LoadObject>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ur16e_interfaces::msg::LoadObject>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ur16e_interfaces::msg::LoadObject>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UR16E_INTERFACES__MSG__DETAIL__LOAD_OBJECT__TRAITS_HPP_
