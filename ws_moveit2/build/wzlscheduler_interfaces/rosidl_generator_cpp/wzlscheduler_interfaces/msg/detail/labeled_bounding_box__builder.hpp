// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledBoundingBox.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOX__BUILDER_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOX__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "wzlscheduler_interfaces/msg/detail/labeled_bounding_box__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace wzlscheduler_interfaces
{

namespace msg
{

namespace builder
{

class Init_LabeledBoundingBox_height
{
public:
  explicit Init_LabeledBoundingBox_height(::wzlscheduler_interfaces::msg::LabeledBoundingBox & msg)
  : msg_(msg)
  {}
  ::wzlscheduler_interfaces::msg::LabeledBoundingBox height(::wzlscheduler_interfaces::msg::LabeledBoundingBox::_height_type arg)
  {
    msg_.height = std::move(arg);
    return std::move(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledBoundingBox msg_;
};

class Init_LabeledBoundingBox_width
{
public:
  explicit Init_LabeledBoundingBox_width(::wzlscheduler_interfaces::msg::LabeledBoundingBox & msg)
  : msg_(msg)
  {}
  Init_LabeledBoundingBox_height width(::wzlscheduler_interfaces::msg::LabeledBoundingBox::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_LabeledBoundingBox_height(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledBoundingBox msg_;
};

class Init_LabeledBoundingBox_y
{
public:
  explicit Init_LabeledBoundingBox_y(::wzlscheduler_interfaces::msg::LabeledBoundingBox & msg)
  : msg_(msg)
  {}
  Init_LabeledBoundingBox_width y(::wzlscheduler_interfaces::msg::LabeledBoundingBox::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_LabeledBoundingBox_width(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledBoundingBox msg_;
};

class Init_LabeledBoundingBox_x
{
public:
  explicit Init_LabeledBoundingBox_x(::wzlscheduler_interfaces::msg::LabeledBoundingBox & msg)
  : msg_(msg)
  {}
  Init_LabeledBoundingBox_y x(::wzlscheduler_interfaces::msg::LabeledBoundingBox::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_LabeledBoundingBox_y(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledBoundingBox msg_;
};

class Init_LabeledBoundingBox_label
{
public:
  Init_LabeledBoundingBox_label()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LabeledBoundingBox_x label(::wzlscheduler_interfaces::msg::LabeledBoundingBox::_label_type arg)
  {
    msg_.label = std::move(arg);
    return Init_LabeledBoundingBox_x(msg_);
  }

private:
  ::wzlscheduler_interfaces::msg::LabeledBoundingBox msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::wzlscheduler_interfaces::msg::LabeledBoundingBox>()
{
  return wzlscheduler_interfaces::msg::builder::Init_LabeledBoundingBox_label();
}

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOX__BUILDER_HPP_
