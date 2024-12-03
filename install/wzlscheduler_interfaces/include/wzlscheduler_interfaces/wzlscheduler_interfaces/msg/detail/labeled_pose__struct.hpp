// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPose.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSE__STRUCT_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__msg__LabeledPose __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__msg__LabeledPose __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LabeledPose_
{
  using Type = LabeledPose_<ContainerAllocator>;

  explicit LabeledPose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->label = "";
      this->drillholeindexx = 0l;
      this->drillholeindexy = 0l;
    }
  }

  explicit LabeledPose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : label(_alloc),
    pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->label = "";
      this->drillholeindexx = 0l;
      this->drillholeindexy = 0l;
    }
  }

  // field types and members
  using _label_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _label_type label;
  using _pose_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _pose_type pose;
  using _drillholeindexx_type =
    int32_t;
  _drillholeindexx_type drillholeindexx;
  using _drillholeindexy_type =
    int32_t;
  _drillholeindexy_type drillholeindexy;

  // setters for named parameter idiom
  Type & set__label(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->label = _arg;
    return *this;
  }
  Type & set__pose(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__drillholeindexx(
    const int32_t & _arg)
  {
    this->drillholeindexx = _arg;
    return *this;
  }
  Type & set__drillholeindexy(
    const int32_t & _arg)
  {
    this->drillholeindexy = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__msg__LabeledPose
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__msg__LabeledPose
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LabeledPose_ & other) const
  {
    if (this->label != other.label) {
      return false;
    }
    if (this->pose != other.pose) {
      return false;
    }
    if (this->drillholeindexx != other.drillholeindexx) {
      return false;
    }
    if (this->drillholeindexy != other.drillholeindexy) {
      return false;
    }
    return true;
  }
  bool operator!=(const LabeledPose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LabeledPose_

// alias to use template instance with default allocator
using LabeledPose =
  wzlscheduler_interfaces::msg::LabeledPose_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSE__STRUCT_HPP_
