// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from wzlscheduler_interfaces:srv/LoadObject.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__LOAD_OBJECT__TRAITS_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__LOAD_OBJECT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "wzlscheduler_interfaces/srv/detail/load_object__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'coordinates'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace wzlscheduler_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const LoadObject_Request & msg,
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
  const LoadObject_Request & msg,
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

inline std::string to_yaml(const LoadObject_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace wzlscheduler_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use wzlscheduler_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const wzlscheduler_interfaces::srv::LoadObject_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::srv::LoadObject_Request & msg)
{
  return wzlscheduler_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::srv::LoadObject_Request>()
{
  return "wzlscheduler_interfaces::srv::LoadObject_Request";
}

template<>
inline const char * name<wzlscheduler_interfaces::srv::LoadObject_Request>()
{
  return "wzlscheduler_interfaces/srv/LoadObject_Request";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::srv::LoadObject_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::srv::LoadObject_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<wzlscheduler_interfaces::srv::LoadObject_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace wzlscheduler_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const LoadObject_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: result
  {
    out << "result: ";
    rosidl_generator_traits::value_to_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LoadObject_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result: ";
    rosidl_generator_traits::value_to_yaml(msg.result, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LoadObject_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace wzlscheduler_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use wzlscheduler_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const wzlscheduler_interfaces::srv::LoadObject_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::srv::LoadObject_Response & msg)
{
  return wzlscheduler_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::srv::LoadObject_Response>()
{
  return "wzlscheduler_interfaces::srv::LoadObject_Response";
}

template<>
inline const char * name<wzlscheduler_interfaces::srv::LoadObject_Response>()
{
  return "wzlscheduler_interfaces/srv/LoadObject_Response";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::srv::LoadObject_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::srv::LoadObject_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<wzlscheduler_interfaces::srv::LoadObject_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<wzlscheduler_interfaces::srv::LoadObject>()
{
  return "wzlscheduler_interfaces::srv::LoadObject";
}

template<>
inline const char * name<wzlscheduler_interfaces::srv::LoadObject>()
{
  return "wzlscheduler_interfaces/srv/LoadObject";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::srv::LoadObject>
  : std::integral_constant<
    bool,
    has_fixed_size<wzlscheduler_interfaces::srv::LoadObject_Request>::value &&
    has_fixed_size<wzlscheduler_interfaces::srv::LoadObject_Response>::value
  >
{
};

template<>
struct has_bounded_size<wzlscheduler_interfaces::srv::LoadObject>
  : std::integral_constant<
    bool,
    has_bounded_size<wzlscheduler_interfaces::srv::LoadObject_Request>::value &&
    has_bounded_size<wzlscheduler_interfaces::srv::LoadObject_Response>::value
  >
{
};

template<>
struct is_service<wzlscheduler_interfaces::srv::LoadObject>
  : std::true_type
{
};

template<>
struct is_service_request<wzlscheduler_interfaces::srv::LoadObject_Request>
  : std::true_type
{
};

template<>
struct is_service_response<wzlscheduler_interfaces::srv::LoadObject_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__LOAD_OBJECT__TRAITS_HPP_
