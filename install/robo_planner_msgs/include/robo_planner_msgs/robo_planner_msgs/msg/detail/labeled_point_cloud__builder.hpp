// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robo_planner_msgs:msg/LabeledPointCloud.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUD__BUILDER_HPP_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robo_planner_msgs/msg/detail/labeled_point_cloud__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robo_planner_msgs
{

namespace msg
{

namespace builder
{

class Init_LabeledPointCloud_pointcloud
{
public:
  explicit Init_LabeledPointCloud_pointcloud(::robo_planner_msgs::msg::LabeledPointCloud & msg)
  : msg_(msg)
  {}
  ::robo_planner_msgs::msg::LabeledPointCloud pointcloud(::robo_planner_msgs::msg::LabeledPointCloud::_pointcloud_type arg)
  {
    msg_.pointcloud = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robo_planner_msgs::msg::LabeledPointCloud msg_;
};

class Init_LabeledPointCloud_posecad
{
public:
  explicit Init_LabeledPointCloud_posecad(::robo_planner_msgs::msg::LabeledPointCloud & msg)
  : msg_(msg)
  {}
  Init_LabeledPointCloud_pointcloud posecad(::robo_planner_msgs::msg::LabeledPointCloud::_posecad_type arg)
  {
    msg_.posecad = std::move(arg);
    return Init_LabeledPointCloud_pointcloud(msg_);
  }

private:
  ::robo_planner_msgs::msg::LabeledPointCloud msg_;
};

class Init_LabeledPointCloud_poseorigin
{
public:
  explicit Init_LabeledPointCloud_poseorigin(::robo_planner_msgs::msg::LabeledPointCloud & msg)
  : msg_(msg)
  {}
  Init_LabeledPointCloud_posecad poseorigin(::robo_planner_msgs::msg::LabeledPointCloud::_poseorigin_type arg)
  {
    msg_.poseorigin = std::move(arg);
    return Init_LabeledPointCloud_posecad(msg_);
  }

private:
  ::robo_planner_msgs::msg::LabeledPointCloud msg_;
};

class Init_LabeledPointCloud_label
{
public:
  Init_LabeledPointCloud_label()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LabeledPointCloud_poseorigin label(::robo_planner_msgs::msg::LabeledPointCloud::_label_type arg)
  {
    msg_.label = std::move(arg);
    return Init_LabeledPointCloud_poseorigin(msg_);
  }

private:
  ::robo_planner_msgs::msg::LabeledPointCloud msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robo_planner_msgs::msg::LabeledPointCloud>()
{
  return robo_planner_msgs::msg::builder::Init_LabeledPointCloud_label();
}

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUD__BUILDER_HPP_
