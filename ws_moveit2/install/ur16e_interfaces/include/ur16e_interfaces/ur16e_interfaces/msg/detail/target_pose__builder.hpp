// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ur16e_interfaces:msg/TargetPose.idl
// generated code does not contain a copyright notice

#ifndef UR16E_INTERFACES__MSG__DETAIL__TARGET_POSE__BUILDER_HPP_
#define UR16E_INTERFACES__MSG__DETAIL__TARGET_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ur16e_interfaces/msg/detail/target_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ur16e_interfaces
{

namespace msg
{

namespace builder
{

class Init_TargetPose_coordinates
{
public:
  explicit Init_TargetPose_coordinates(::ur16e_interfaces::msg::TargetPose & msg)
  : msg_(msg)
  {}
  ::ur16e_interfaces::msg::TargetPose coordinates(::ur16e_interfaces::msg::TargetPose::_coordinates_type arg)
  {
    msg_.coordinates = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur16e_interfaces::msg::TargetPose msg_;
};

class Init_TargetPose_name
{
public:
  Init_TargetPose_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TargetPose_coordinates name(::ur16e_interfaces::msg::TargetPose::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_TargetPose_coordinates(msg_);
  }

private:
  ::ur16e_interfaces::msg::TargetPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur16e_interfaces::msg::TargetPose>()
{
  return ur16e_interfaces::msg::builder::Init_TargetPose_name();
}

}  // namespace ur16e_interfaces

#endif  // UR16E_INTERFACES__MSG__DETAIL__TARGET_POSE__BUILDER_HPP_
