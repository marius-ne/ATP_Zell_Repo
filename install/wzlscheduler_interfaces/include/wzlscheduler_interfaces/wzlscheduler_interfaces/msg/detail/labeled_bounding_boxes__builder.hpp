// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledBoundingBoxes.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOXES__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOXES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/msg/detail/labeled_bounding_boxes__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace msg
{

namespace builder
{

class Init_LabeledBoundingBoxes_elements
{
public:
  Init_LabeledBoundingBoxes_elements()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::wzlscheduler_interfaces::msg::LabeledBoundingBoxes elements(::wzlscheduler_interfaces::msg::LabeledBoundingBoxes::_elements_type arg)
  {
    msg_.elements = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledBoundingBoxes msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::msg::LabeledBoundingBoxes>()
{
  return wzlscheduler_interfaces::msg::builder::Init_LabeledBoundingBoxes_elements();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOXES__BUILDER_HPP_
