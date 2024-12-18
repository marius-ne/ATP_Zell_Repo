// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robo_planner_msgs:srv/GripperChange.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE__BUILDER_HPP_
#define ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robo_planner_msgs/srv/detail/gripper_change__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robo_planner_msgs
{

namespace srv
{

namespace builder
{

class Init_GripperChange_Request_subtaskgripperhangeplace
{
public:
  explicit Init_GripperChange_Request_subtaskgripperhangeplace(::robo_planner_msgs::srv::GripperChange_Request & msg)
  : msg_(msg)
  {}
  ::robo_planner_msgs::srv::GripperChange_Request subtaskgripperhangeplace(::robo_planner_msgs::srv::GripperChange_Request::_subtaskgripperhangeplace_type arg)
  {
    msg_.subtaskgripperhangeplace = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robo_planner_msgs::srv::GripperChange_Request msg_;
};

class Init_GripperChange_Request_subtaskgripperhangepick
{
public:
  Init_GripperChange_Request_subtaskgripperhangepick()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GripperChange_Request_subtaskgripperhangeplace subtaskgripperhangepick(::robo_planner_msgs::srv::GripperChange_Request::_subtaskgripperhangepick_type arg)
  {
    msg_.subtaskgripperhangepick = std::move(arg);
    return Init_GripperChange_Request_subtaskgripperhangeplace(msg_);
  }

private:
  ::robo_planner_msgs::srv::GripperChange_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::srv::GripperChange_Request>()
{
  return robo_planner_msgs::srv::builder::Init_GripperChange_Request_subtaskgripperhangepick();
}

}  // namespace robo_planner_msgs


namespace robo_planner_msgs
{

namespace srv
{

namespace builder
{

class Init_GripperChange_Response_result
{
public:
  Init_GripperChange_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robo_planner_msgs::srv::GripperChange_Response result(::robo_planner_msgs::srv::GripperChange_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robo_planner_msgs::srv::GripperChange_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::srv::GripperChange_Response>()
{
  return robo_planner_msgs::srv::builder::Init_GripperChange_Response_result();
}

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE__BUILDER_HPP_
