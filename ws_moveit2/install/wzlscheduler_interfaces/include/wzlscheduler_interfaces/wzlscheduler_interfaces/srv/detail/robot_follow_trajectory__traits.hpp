// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from wzlscheduler_interfaces:srv/RobotFollowTrajectory.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_FOLLOW_TRAJECTORY__TRAITS_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_FOLLOW_TRAJECTORY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'supportpoints'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace wzlscheduler_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const RobotFollowTrajectory_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: supportpoints
  {
    if (msg.supportpoints.size() == 0) {
      out << "supportpoints: []";
    } else {
      out << "supportpoints: [";
      size_t pending_items = msg.supportpoints.size();
      for (auto item : msg.supportpoints) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotFollowTrajectory_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: supportpoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.supportpoints.size() == 0) {
      out << "supportpoints: []\n";
    } else {
      out << "supportpoints:\n";
      for (auto item : msg.supportpoints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotFollowTrajectory_Request & msg, bool use_flow_style = false)
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
  const wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request & msg)
{
  return wzlscheduler_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request>()
{
  return "wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request";
}

template<>
inline const char * name<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request>()
{
  return "wzlscheduler_interfaces/srv/RobotFollowTrajectory_Request";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace wzlscheduler_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const RobotFollowTrajectory_Response & msg,
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
  const RobotFollowTrajectory_Response & msg,
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

inline std::string to_yaml(const RobotFollowTrajectory_Response & msg, bool use_flow_style = false)
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
  const wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response & msg)
{
  return wzlscheduler_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response>()
{
  return "wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response";
}

template<>
inline const char * name<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response>()
{
  return "wzlscheduler_interfaces/srv/RobotFollowTrajectory_Response";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<wzlscheduler_interfaces::srv::RobotFollowTrajectory>()
{
  return "wzlscheduler_interfaces::srv::RobotFollowTrajectory";
}

template<>
inline const char * name<wzlscheduler_interfaces::srv::RobotFollowTrajectory>()
{
  return "wzlscheduler_interfaces/srv/RobotFollowTrajectory";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::srv::RobotFollowTrajectory>
  : std::integral_constant<
    bool,
    has_fixed_size<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request>::value &&
    has_fixed_size<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response>::value
  >
{
};

template<>
struct has_bounded_size<wzlscheduler_interfaces::srv::RobotFollowTrajectory>
  : std::integral_constant<
    bool,
    has_bounded_size<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request>::value &&
    has_bounded_size<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response>::value
  >
{
};

template<>
struct is_service<wzlscheduler_interfaces::srv::RobotFollowTrajectory>
  : std::true_type
{
};

template<>
struct is_service_request<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request>
  : std::true_type
{
};

template<>
struct is_service_response<wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_FOLLOW_TRAJECTORY__TRAITS_HPP_
