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

class Init_RobotSetVelocity_Request_value
{
public:
  Init_RobotSetVelocity_Request_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::srv::RobotSetVelocity_Request value(::wzlscheduler_interfaces::srv::RobotSetVelocity_Request::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
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
  return wzlscheduler_interfaces::srv::builder::Init_RobotSetVelocity_Request_value();
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
