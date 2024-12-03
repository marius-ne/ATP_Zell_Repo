// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:srv/RobotMoveToPosition.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/srv/detail/robot_move_to_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_RobotMoveToPosition_Request_pose
{
public:
  explicit Init_RobotMoveToPosition_Request_pose(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request pose(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request msg_;
};

class Init_RobotMoveToPosition_Request_movetype
{
public:
  Init_RobotMoveToPosition_Request_movetype()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotMoveToPosition_Request_pose movetype(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request::_movetype_type arg)
  {
    msg_.movetype = std::move(arg);
    return Init_RobotMoveToPosition_Request_pose(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::RobotMoveToPosition_Request>()
{
  return wzlscheduler_interfaces::srv::builder::Init_RobotMoveToPosition_Request_movetype();
}

}  // namespace wzlscheduler_interfaces


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_RobotMoveToPosition_Response_result
{
public:
  Init_RobotMoveToPosition_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Response result(::wzlscheduler_interfaces::srv::RobotMoveToPosition_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotMoveToPosition_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::RobotMoveToPosition_Response>()
{
  return wzlscheduler_interfaces::srv::builder::Init_RobotMoveToPosition_Response_result();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_MOVE_TO_POSITION__BUILDER_HPP_
