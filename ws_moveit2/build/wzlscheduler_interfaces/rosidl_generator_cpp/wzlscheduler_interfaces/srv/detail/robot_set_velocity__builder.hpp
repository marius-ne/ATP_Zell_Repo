// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:srv/RobotSetVelocity.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_SET_VELOCITY__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_SET_VELOCITY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/srv/detail/robot_set_velocity__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_RobotSetVelocity_Request_type
{
public:
  explicit Init_RobotSetVelocity_Request_type(::wzlscheduler_interfaces::srv::RobotSetVelocity_Request & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::srv::RobotSetVelocity_Request type(::wzlscheduler_interfaces::srv::RobotSetVelocity_Request::_type_type arg)
  {
    msg_.type = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotSetVelocity_Request msg_;
};

class Init_RobotSetVelocity_Request_accelerationscalingfactor
{
public:
  explicit Init_RobotSetVelocity_Request_accelerationscalingfactor(::wzlscheduler_interfaces::srv::RobotSetVelocity_Request & msg)
  : msg_(msg)
  {}
  Init_RobotSetVelocity_Request_type accelerationscalingfactor(::wzlscheduler_interfaces::srv::RobotSetVelocity_Request::_accelerationscalingfactor_type arg)
  {
    msg_.accelerationscalingfactor = std::move(arg);
    return Init_RobotSetVelocity_Request_type(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotSetVelocity_Request msg_;
};

class Init_RobotSetVelocity_Request_velocityscalingfactor
{
public:
  Init_RobotSetVelocity_Request_velocityscalingfactor()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotSetVelocity_Request_accelerationscalingfactor velocityscalingfactor(::wzlscheduler_interfaces::srv::RobotSetVelocity_Request::_velocityscalingfactor_type arg)
  {
    msg_.velocityscalingfactor = std::move(arg);
    return Init_RobotSetVelocity_Request_accelerationscalingfactor(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotSetVelocity_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::RobotSetVelocity_Request>()
{
  return wzlscheduler_interfaces::srv::builder::Init_RobotSetVelocity_Request_velocityscalingfactor();
}

}  // namespace wzlscheduler_interfaces


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_RobotSetVelocity_Response_result
{
public:
  Init_RobotSetVelocity_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::srv::RobotSetVelocity_Response result(::wzlscheduler_interfaces::srv::RobotSetVelocity_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotSetVelocity_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::RobotSetVelocity_Response>()
{
  return wzlscheduler_interfaces::srv::builder::Init_RobotSetVelocity_Response_result();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_SET_VELOCITY__BUILDER_HPP_
