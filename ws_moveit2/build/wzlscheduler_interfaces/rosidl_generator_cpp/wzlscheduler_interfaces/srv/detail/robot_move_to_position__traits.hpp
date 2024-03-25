// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from wzlscheduler_interfaces:srv/RobotMoveToPosition.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__TRAITS_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "wzlscheduler_interfaces/srv/detail/robot_move_to_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace wzlscheduler_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const RobotMoveToPosition_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: posx
  {
    out << "posx: ";
    rosidl_generator_traits::value_to_yaml(msg.posx, out);
    out << ", ";
  }

  // member: posy
  {
    out << "posy: ";
    rosidl_generator_traits::value_to_yaml(msg.posy, out);
    out << ", ";
  }

  // member: posz
  {
    out << "posz: ";
    rosidl_generator_traits::value_to_yaml(msg.posz, out);
    out << ", ";
  }

  // member: rotx
  {
    out << "rotx: ";
    rosidl_generator_traits::value_to_yaml(msg.rotx, out);
    out << ", ";
  }

  // member: roty
  {
    out << "roty: ";
    rosidl_generator_traits::value_to_yaml(msg.roty, out);
    out << ", ";
  }

  // member: rotz
  {
    out << "rotz: ";
    rosidl_generator_traits::value_to_yaml(msg.rotz, out);
    out << ", ";
  }

  // member: movetype
  {
    out << "movetype: ";
    rosidl_generator_traits::value_to_yaml(msg.movetype, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotMoveToPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: posx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "posx: ";
    rosidl_generator_traits::value_to_yaml(msg.posx, out);
    out << "\n";
  }

  // member: posy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "posy: ";
    rosidl_generator_traits::value_to_yaml(msg.posy, out);
    out << "\n";
  }

  // member: posz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "posz: ";
    rosidl_generator_traits::value_to_yaml(msg.posz, out);
    out << "\n";
  }

  // member: rotx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rotx: ";
    rosidl_generator_traits::value_to_yaml(msg.rotx, out);
    out << "\n";
  }

  // member: roty
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "roty: ";
    rosidl_generator_traits::value_to_yaml(msg.roty, out);
    out << "\n";
  }

  // member: rotz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rotz: ";
    rosidl_generator_traits::value_to_yaml(msg.rotz, out);
    out << "\n";
  }

  // member: movetype
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "movetype: ";
    rosidl_generator_traits::value_to_yaml(msg.movetype, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotMoveToPosition_Request & msg, bool use_flow_style = false)
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
  const wzlscheduler_interfaces::srv::RobotMoveToPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::srv::RobotMoveToPosition_Request & msg)
{
  return wzlscheduler_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request>()
{
  return "wzlscheduler_interfaces::srv::RobotMoveToPosition_Request";
}

template<>
inline const char * name<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request>()
{
  return "wzlscheduler_interfaces/srv/RobotMoveToPosition_Request";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace wzlscheduler_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const RobotMoveToPosition_Response & msg,
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
  const RobotMoveToPosition_Response & msg,
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

inline std::string to_yaml(const RobotMoveToPosition_Response & msg, bool use_flow_style = false)
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
  const wzlscheduler_interfaces::srv::RobotMoveToPosition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  wzlscheduler_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use wzlscheduler_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const wzlscheduler_interfaces::srv::RobotMoveToPosition_Response & msg)
{
  return wzlscheduler_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response>()
{
  return "wzlscheduler_interfaces::srv::RobotMoveToPosition_Response";
}

template<>
inline const char * name<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response>()
{
  return "wzlscheduler_interfaces/srv/RobotMoveToPosition_Response";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<wzlscheduler_interfaces::srv::RobotMoveToPosition>()
{
  return "wzlscheduler_interfaces::srv::RobotMoveToPosition";
}

template<>
inline const char * name<wzlscheduler_interfaces::srv::RobotMoveToPosition>()
{
  return "wzlscheduler_interfaces/srv/RobotMoveToPosition";
}

template<>
struct has_fixed_size<wzlscheduler_interfaces::srv::RobotMoveToPosition>
  : std::integral_constant<
    bool,
    has_fixed_size<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request>::value &&
    has_fixed_size<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response>::value
  >
{
};

template<>
struct has_bounded_size<wzlscheduler_interfaces::srv::RobotMoveToPosition>
  : std::integral_constant<
    bool,
    has_bounded_size<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request>::value &&
    has_bounded_size<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response>::value
  >
{
};

template<>
struct is_service<wzlscheduler_interfaces::srv::RobotMoveToPosition>
  : std::true_type
{
};

template<>
struct is_service_request<wzlscheduler_interfaces::srv::RobotMoveToPosition_Request>
  : std::true_type
{
};

template<>
struct is_service_response<wzlscheduler_interfaces::srv::RobotMoveToPosition_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__TRAITS_HPP_
