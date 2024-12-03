// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robo_planner_msgs:srv/FollowTrajectory.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__SRV__DETAIL__FOLLOW_TRAJECTORY__BUILDER_HPP_
#define ROBO_PLANNER_MSGS__SRV__DETAIL__FOLLOW_TRAJECTORY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robo_planner_msgs/srv/detail/follow_trajectory__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robo_planner_msgs
{

namespace srv
{

namespace builder
{

class Init_FollowTrajectory_Request_value
{
public:
  explicit Init_FollowTrajectory_Request_value(::robo_planner_msgs::srv::FollowTrajectory_Request & msg)
  : msg_(msg)
  {}
  ::robo_planner_msgs::srv::FollowTrajectory_Request value(::robo_planner_msgs::srv::FollowTrajectory_Request::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robo_planner_msgs::srv::FollowTrajectory_Request msg_;
};

class Init_FollowTrajectory_Request_supportpoints
{
public:
  Init_FollowTrajectory_Request_supportpoints()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowTrajectory_Request_value supportpoints(::robo_planner_msgs::srv::FollowTrajectory_Request::_supportpoints_type arg)
  {
    msg_.supportpoints = std::move(arg);
    return Init_FollowTrajectory_Request_value(msg_);
  }

private:
  ::robo_planner_msgs::srv::FollowTrajectory_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::srv::FollowTrajectory_Request>()
{
  return robo_planner_msgs::srv::builder::Init_FollowTrajectory_Request_supportpoints();
}

}  // namespace robo_planner_msgs


namespace robo_planner_msgs
{

namespace srv
{

namespace builder
{

class Init_FollowTrajectory_Response_result
{
public:
  Init_FollowTrajectory_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robo_planner_msgs::srv::FollowTrajectory_Response result(::robo_planner_msgs::srv::FollowTrajectory_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robo_planner_msgs::srv::FollowTrajectory_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::srv::FollowTrajectory_Response>()
{
  return robo_planner_msgs::srv::builder::Init_FollowTrajectory_Response_result();
}

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__SRV__DETAIL__FOLLOW_TRAJECTORY__BUILDER_HPP_
