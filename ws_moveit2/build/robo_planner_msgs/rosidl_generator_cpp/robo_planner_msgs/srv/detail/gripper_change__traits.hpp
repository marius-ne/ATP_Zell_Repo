// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robo_planner_msgs:srv/GripperChange.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE__TRAITS_HPP_
#define ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robo_planner_msgs/srv/detail/gripper_change__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robo_planner_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GripperChange_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: subtaskgripperhangepick
  {
    out << "subtaskgripperhangepick: ";
    rosidl_generator_traits::value_to_yaml(msg.subtaskgripperhangepick, out);
    out << ", ";
  }

  // member: subtaskgripperhangeplace
  {
    out << "subtaskgripperhangeplace: ";
    rosidl_generator_traits::value_to_yaml(msg.subtaskgripperhangeplace, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GripperChange_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: subtaskgripperhangepick
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "subtaskgripperhangepick: ";
    rosidl_generator_traits::value_to_yaml(msg.subtaskgripperhangepick, out);
    out << "\n";
  }

  // member: subtaskgripperhangeplace
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "subtaskgripperhangeplace: ";
    rosidl_generator_traits::value_to_yaml(msg.subtaskgripperhangeplace, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GripperChange_Request & msg, bool use_flow_style = false)
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

}  // namespace robo_planner_msgs

namespace rosidl_generator_traits
{

[[deprecated("use robo_planner_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robo_planner_msgs::srv::GripperChange_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  robo_planner_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robo_planner_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const robo_planner_msgs::srv::GripperChange_Request & msg)
{
  return robo_planner_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robo_planner_msgs::srv::GripperChange_Request>()
{
  return "robo_planner_msgs::srv::GripperChange_Request";
}

template<>
inline const char * name<robo_planner_msgs::srv::GripperChange_Request>()
{
  return "robo_planner_msgs/srv/GripperChange_Request";
}

template<>
struct has_fixed_size<robo_planner_msgs::srv::GripperChange_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robo_planner_msgs::srv::GripperChange_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robo_planner_msgs::srv::GripperChange_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace robo_planner_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GripperChange_Response & msg,
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
  const GripperChange_Response & msg,
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

inline std::string to_yaml(const GripperChange_Response & msg, bool use_flow_style = false)
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

}  // namespace robo_planner_msgs

namespace rosidl_generator_traits
{

[[deprecated("use robo_planner_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robo_planner_msgs::srv::GripperChange_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  robo_planner_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robo_planner_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const robo_planner_msgs::srv::GripperChange_Response & msg)
{
  return robo_planner_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robo_planner_msgs::srv::GripperChange_Response>()
{
  return "robo_planner_msgs::srv::GripperChange_Response";
}

template<>
inline const char * name<robo_planner_msgs::srv::GripperChange_Response>()
{
  return "robo_planner_msgs/srv/GripperChange_Response";
}

template<>
struct has_fixed_size<robo_planner_msgs::srv::GripperChange_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robo_planner_msgs::srv::GripperChange_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robo_planner_msgs::srv::GripperChange_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<robo_planner_msgs::srv::GripperChange>()
{
  return "robo_planner_msgs::srv::GripperChange";
}

template<>
inline const char * name<robo_planner_msgs::srv::GripperChange>()
{
  return "robo_planner_msgs/srv/GripperChange";
}

template<>
struct has_fixed_size<robo_planner_msgs::srv::GripperChange>
  : std::integral_constant<
    bool,
    has_fixed_size<robo_planner_msgs::srv::GripperChange_Request>::value &&
    has_fixed_size<robo_planner_msgs::srv::GripperChange_Response>::value
  >
{
};

template<>
struct has_bounded_size<robo_planner_msgs::srv::GripperChange>
  : std::integral_constant<
    bool,
    has_bounded_size<robo_planner_msgs::srv::GripperChange_Request>::value &&
    has_bounded_size<robo_planner_msgs::srv::GripperChange_Response>::value
  >
{
};

template<>
struct is_service<robo_planner_msgs::srv::GripperChange>
  : std::true_type
{
};

template<>
struct is_service_request<robo_planner_msgs::srv::GripperChange_Request>
  : std::true_type
{
};

template<>
struct is_service_response<robo_planner_msgs::srv::GripperChange_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE__TRAITS_HPP_
