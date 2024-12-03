// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPose.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSE__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/msg/detail/labeled_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace msg
{

namespace builder
{

class Init_LabeledPose_drillholeindexy
{
public:
  explicit Init_LabeledPose_drillholeindexy(::wzlscheduler_interfaces::msg::LabeledPose & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::msg::LabeledPose drillholeindexy(::wzlscheduler_interfaces::msg::LabeledPose::_drillholeindexy_type arg)
  {
    msg_.drillholeindexy = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledPose msg_;
};

class Init_LabeledPose_drillholeindexx
{
public:
  explicit Init_LabeledPose_drillholeindexx(::wzlscheduler_interfaces::msg::LabeledPose & msg)
  : msg_(msg)
  {}
  Init_LabeledPose_drillholeindexy drillholeindexx(::wzlscheduler_interfaces::msg::LabeledPose::_drillholeindexx_type arg)
  {
    msg_.drillholeindexx = std::move(arg);
    return Init_LabeledPose_drillholeindexy(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledPose msg_;
};

class Init_LabeledPose_pose
{
public:
  explicit Init_LabeledPose_pose(::wzlscheduler_interfaces::msg::LabeledPose & msg)
  : msg_(msg)
  {}
  Init_LabeledPose_drillholeindexx pose(::wzlscheduler_interfaces::msg::LabeledPose::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_LabeledPose_drillholeindexx(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledPose msg_;
};

class Init_LabeledPose_label
{
public:
  Init_LabeledPose_label()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LabeledPose_pose label(::wzlscheduler_interfaces::msg::LabeledPose::_label_type arg)
  {
    msg_.label = std::move(arg);
    return Init_LabeledPose_pose(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::msg::LabeledPose>()
{
  return wzlscheduler_interfaces::msg::builder::Init_LabeledPose_label();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSE__BUILDER_HPP_
