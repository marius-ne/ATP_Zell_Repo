// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robo_planner_msgs:msg/LabeledPointClouds.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__BUILDER_HPP_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robo_planner_msgs/msg/detail/labeled_point_clouds__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robo_planner_msgs
{

namespace msg
{

namespace builder
{

class Init_LabeledPointClouds_elements
{
public:
  Init_LabeledPointClouds_elements()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robo_planner_msgs::msg::LabeledPointClouds elements(::robo_planner_msgs::msg::LabeledPointClouds::_elements_type arg)
  {
    msg_.elements = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robo_planner_msgs::msg::LabeledPointClouds msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::msg::LabeledPointClouds>()
{
  return robo_planner_msgs::msg::builder::Init_LabeledPointClouds_elements();
}

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__BUILDER_HPP_
