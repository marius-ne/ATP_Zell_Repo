// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledBoundingBoxes.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOXES__STRUCT_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOXES__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'elements'
#include "wzlscheduler_interfaces/msg/detail/labeled_bounding_box__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__msg__LabeledBoundingBoxes __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__msg__LabeledBoundingBoxes __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LabeledBoundingBoxes_
{
  using Type = LabeledBoundingBoxes_<ContainerAllocator>;

  explicit LabeledBoundingBoxes_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit LabeledBoundingBoxes_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _elements_type =
    std::vector<wzlscheduler_interfaces::msg::LabeledBoundingBox_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<wzlscheduler_interfaces::msg::LabeledBoundingBox_<ContainerAllocator>>>;
  _elements_type elements;

  // setters for named parameter idiom
  Type & set__elements(
    const std::vector<wzlscheduler_interfaces::msg::LabeledBoundingBox_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<wzlscheduler_interfaces::msg::LabeledBoundingBox_<ContainerAllocator>>> & _arg)
  {
    this->elements = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__msg__LabeledBoundingBoxes
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__msg__LabeledBoundingBoxes
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LabeledBoundingBoxes_ & other) const
  {
    if (this->elements != other.elements) {
      return false;
    }
    return true;
  }
  bool operator!=(const LabeledBoundingBoxes_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LabeledBoundingBoxes_

// alias to use template instance with default allocator
using LabeledBoundingBoxes =
  wzlscheduler_interfaces::msg::LabeledBoundingBoxes_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_BOUNDING_BOXES__STRUCT_HPP_
