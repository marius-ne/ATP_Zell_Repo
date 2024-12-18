// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPoses.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/msg/detail/labeled_poses__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace msg
{

namespace builder
{

class Init_LabeledPoses_elements
{
public:
  Init_LabeledPoses_elements()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::msg::LabeledPoses elements(::wzlscheduler_interfaces::msg::LabeledPoses::_elements_type arg)
  {
    msg_.elements = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledPoses msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::msg::LabeledPoses>()
{
  return wzlscheduler_interfaces::msg::builder::Init_LabeledPoses_elements();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__BUILDER_HPP_
