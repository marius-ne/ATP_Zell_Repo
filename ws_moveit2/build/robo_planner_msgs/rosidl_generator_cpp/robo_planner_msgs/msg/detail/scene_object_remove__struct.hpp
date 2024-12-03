// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robo_planner_msgs:msg/SceneObjectRemove.idl
// generated code does not contain a copyright notice

#ifndef ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_REMOVE__STRUCT_HPP_
#define ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_REMOVE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robo_planner_msgs__msg__SceneObjectRemove __attribute__((deprecated))
#else
# define DEPRECATED__robo_planner_msgs__msg__SceneObjectRemove __declspec(deprecated)
#endif

namespace robo_planner_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SceneObjectRemove_
{
  using Type = SceneObjectRemove_<ContainerAllocator>;

  explicit SceneObjectRemove_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
    }
  }

  explicit SceneObjectRemove_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator> *;
  using ConstRawPtr =
    const robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robo_planner_msgs__msg__SceneObjectRemove
    std::shared_ptr<robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robo_planner_msgs__msg__SceneObjectRemove
    std::shared_ptr<robo_planner_msgs::msg::SceneObjectRemove_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SceneObjectRemove_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    return true;
  }
  bool operator!=(const SceneObjectRemove_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SceneObjectRemove_

// alias to use template instance with default allocator
using SceneObjectRemove =
  robo_planner_msgs::msg::SceneObjectRemove_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robo_planner_msgs

#endif  // ROBO_PLANNER_MSGS__MSG__DETAIL__SCENE_OBJECT_REMOVE__STRUCT_HPP_
