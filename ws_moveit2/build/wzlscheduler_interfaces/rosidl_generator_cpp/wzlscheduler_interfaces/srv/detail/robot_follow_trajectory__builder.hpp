// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:srv/RobotFollowTrajectory.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_FOLLOW_TRAJECTORY__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_FOLLOW_TRAJECTORY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_RobotFollowTrajectory_Request_supportpoints
{
public:
  Init_RobotFollowTrajectory_Request_supportpoints()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request supportpoints(::wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request::_supportpoints_type arg)
  {
    msg_.supportpoints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::RobotFollowTrajectory_Request>()
{
  return wzlscheduler_interfaces::srv::builder::Init_RobotFollowTrajectory_Request_supportpoints();
}

}  // namespace wzlscheduler_interfaces


namespace wzlscheduler_interfaces
{

namespace srv
{

namespace builder
{

class Init_RobotFollowTrajectory_Response_result
{
public:
  Init_RobotFollowTrajectory_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response result(::wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::srv::RobotFollowTrajectory_Response>()
{
  return wzlscheduler_interfaces::srv::builder::Init_RobotFollowTrajectory_Response_result();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__ROBOT_FOLLOW_TRAJECTORY__BUILDER_HPP_
