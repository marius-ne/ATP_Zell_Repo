// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPointCloud.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/msg/detail/labeled_point_cloud__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace msg
{

namespace builder
{

class Init_LabeledPointCloud_pointcloud
{
public:
  explicit Init_LabeledPointCloud_pointcloud(::wzlscheduler_interfaces::msg::LabeledPointCloud & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::msg::LabeledPointCloud pointcloud(::wzlscheduler_interfaces::msg::LabeledPointCloud::_pointcloud_type arg)
  {
    msg_.pointcloud = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledPointCloud msg_;
};

class Init_LabeledPointCloud_posecad
{
public:
  explicit Init_LabeledPointCloud_posecad(::wzlscheduler_interfaces::msg::LabeledPointCloud & msg)
  : msg_(msg)
  {}
  Init_LabeledPointCloud_pointcloud posecad(::wzlscheduler_interfaces::msg::LabeledPointCloud::_posecad_type arg)
  {
    msg_.posecad = std::move(arg);
    return Init_LabeledPointCloud_pointcloud(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledPointCloud msg_;
};

class Init_LabeledPointCloud_poseorigin
{
public:
  explicit Init_LabeledPointCloud_poseorigin(::wzlscheduler_interfaces::msg::LabeledPointCloud & msg)
  : msg_(msg)
  {}
  Init_LabeledPointCloud_posecad poseorigin(::wzlscheduler_interfaces::msg::LabeledPointCloud::_poseorigin_type arg)
  {
    msg_.poseorigin = std::move(arg);
    return Init_LabeledPointCloud_posecad(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledPointCloud msg_;
};

class Init_LabeledPointCloud_label
{
public:
  Init_LabeledPointCloud_label()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LabeledPointCloud_poseorigin label(::wzlscheduler_interfaces::msg::LabeledPointCloud::_label_type arg)
  {
    msg_.label = std::move(arg);
    return Init_LabeledPointCloud_poseorigin(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledPointCloud msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::msg::LabeledPointCloud>()
{
  return wzlscheduler_interfaces::msg::builder::Init_LabeledPointCloud_label();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__BUILDER_HPP_
