// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robo_planner_msgs:msg/LabeledPointClouds.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__STRUCT_HPP_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'elements'
#include "robo_planner_msgs/msg/detail/labeled_point_cloud__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robo_planner_msgs__msg__LabeledPointClouds __attribute__((deprecated))
#else
# define DEPRECATED__robo_planner_msgs__msg__LabeledPointClouds __declspec(deprecated)
#endif

namespace robo_planner_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LabeledPointClouds_
{
  using Type = LabeledPointClouds_<ContainerAllocator>;

  explicit LabeledPointClouds_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit LabeledPointClouds_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _elements_type =
    std::vector<robo_planner_msgs::msg::LabeledPointCloud_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robo_planner_msgs::msg::LabeledPointCloud_<ContainerAllocator>>>;
  _elements_type elements;

  // setters for named parameter idiom
  Type & set__elements(
    const std::vector<robo_planner_msgs::msg::LabeledPointCloud_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robo_planner_msgs::msg::LabeledPointCloud_<ContainerAllocator>>> & _arg)
  {
    this->elements = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator> *;
  using ConstRawPtr =
    const robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robo_planner_msgs__msg__LabeledPointClouds
    std::shared_ptr<robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robo_planner_msgs__msg__LabeledPointClouds
    std::shared_ptr<robo_planner_msgs::msg::LabeledPointClouds_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LabeledPointClouds_ & other) const
  {
    if (this->elements != other.elements) {
      return false;
    }
    return true;
  }
  bool operator!=(const LabeledPointClouds_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LabeledPointClouds_

// alias to use template instance with default allocator
using LabeledPointClouds =
  robo_planner_msgs::msg::LabeledPointClouds_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__LABELED_POINT_CLOUDS__STRUCT_HPP_
