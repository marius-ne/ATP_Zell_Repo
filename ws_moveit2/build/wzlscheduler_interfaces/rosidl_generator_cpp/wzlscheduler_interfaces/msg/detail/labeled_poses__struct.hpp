// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPoses.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__STRUCT_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'elements'
#include "wzlscheduler_interfaces/msg/detail/labeled_pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__msg__LabeledPoses __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__msg__LabeledPoses __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LabeledPoses_
{
  using Type = LabeledPoses_<ContainerAllocator>;

  explicit LabeledPoses_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : elements(_init)
  {
    (void)_init;
  }

  explicit LabeledPoses_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : elements(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _elements_type =
    wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator>;
  _elements_type elements;

  // setters for named parameter idiom
  Type & set__elements(
    const wzlscheduler_interfaces::msg::LabeledPose_<ContainerAllocator> & _arg)
  {
    this->elements = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__msg__LabeledPoses
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__msg__LabeledPoses
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPoses_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LabeledPoses_ & other) const
  {
    if (this->elements != other.elements) {
      return false;
    }
    return true;
  }
  bool operator!=(const LabeledPoses_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LabeledPoses_

// alias to use template instance with default allocator
using LabeledPoses =
  wzlscheduler_interfaces::msg::LabeledPoses_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POSES__STRUCT_HPP_
