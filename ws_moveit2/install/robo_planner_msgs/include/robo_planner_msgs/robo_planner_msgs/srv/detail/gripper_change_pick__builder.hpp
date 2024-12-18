// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robo_planner_msgs:srv/GripperChangePick.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE_PICK__BUILDER_HPP_
#define ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE_PICK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robo_planner_msgs/srv/detail/gripper_change_pick__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robo_planner_msgs
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::srv::GripperChangePick_Request>()
{
  return ::robo_planner_msgs::srv::GripperChangePick_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace robo_planner_msgs


namespace robo_planner_msgs
{

namespace srv
{

namespace builder
{

class Init_GripperChangePick_Response_result
{
public:
  Init_GripperChangePick_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robo_planner_msgs::srv::GripperChangePick_Response result(::robo_planner_msgs::srv::GripperChangePick_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robo_planner_msgs::srv::GripperChangePick_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::srv::GripperChangePick_Response>()
{
  return robo_planner_msgs::srv::builder::Init_GripperChangePick_Response_result();
}

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__SRV__DETAIL__GRIPPER_CHANGE_PICK__BUILDER_HPP_
