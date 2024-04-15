// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ur16e_interfaces:msg/TargetPose.idl
// generated code does not contain a copyright notice

#ifndef UR16E_INTERFACES__MSG__DETAIL__TARGET_POSE__STRUCT_HPP_
#define UR16E_INTERFACES__MSG__DETAIL__TARGET_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'coordinates'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__ur16e_interfaces__msg__TargetPose __attribute__((deprecated))
#else
# define DEPRECATED__ur16e_interfaces__msg__TargetPose __declspec(deprecated)
#endif

namespace ur16e_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TargetPose_
{
  using Type = TargetPose_<ContainerAllocator>;

  explicit TargetPose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : coordinates(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
    }
  }

  explicit TargetPose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc),
    coordinates(_alloc, _init)
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
  using _coordinates_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _coordinates_type coordinates;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__coordinates(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->coordinates = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ur16e_interfaces::msg::TargetPose_<ContainerAllocator> *;
  using ConstRawPtr =
    const ur16e_interfaces::msg::TargetPose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ur16e_interfaces::msg::TargetPose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ur16e_interfaces::msg::TargetPose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ur16e_interfaces::msg::TargetPose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ur16e_interfaces::msg::TargetPose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ur16e_interfaces::msg::TargetPose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ur16e_interfaces::msg::TargetPose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ur16e_interfaces::msg::TargetPose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ur16e_interfaces::msg::TargetPose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ur16e_interfaces__msg__TargetPose
    std::shared_ptr<ur16e_interfaces::msg::TargetPose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ur16e_interfaces__msg__TargetPose
    std::shared_ptr<ur16e_interfaces::msg::TargetPose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TargetPose_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->coordinates != other.coordinates) {
      return false;
    }
    return true;
  }
  bool operator!=(const TargetPose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TargetPose_

// alias to use template instance with default allocator
using TargetPose =
  ur16e_interfaces::msg::TargetPose_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ur16e_interfaces

#endif  // UR16E_INTERFACES__MSG__DETAIL__TARGET_POSE__STRUCT_HPP_
