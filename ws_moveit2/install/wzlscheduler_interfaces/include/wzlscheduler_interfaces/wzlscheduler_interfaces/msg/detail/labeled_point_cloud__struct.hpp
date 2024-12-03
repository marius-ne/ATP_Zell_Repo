// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wzlscheduler_interfaces:msg/LabeledPointCloud.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__STRUCT_HPP_
#define WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'poseorigin'
// Member 'posecad'
#include "geometry_msgs/msg/detail/pose__struct.hpp"
// Member 'pointcloud'
#include "sensor_msgs/msg/detail/point_cloud2__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__msg__LabeledPointCloud __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__msg__LabeledPointCloud __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LabeledPointCloud_
{
  using Type = LabeledPointCloud_<ContainerAllocator>;

  explicit LabeledPointCloud_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : poseorigin(_init),
    posecad(_init),
    pointcloud(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->label = "";
    }
  }

  explicit LabeledPointCloud_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : label(_alloc),
    poseorigin(_alloc, _init),
    posecad(_alloc, _init),
    pointcloud(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->label = "";
    }
  }

  // field types and members
  using _label_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _label_type label;
  using _poseorigin_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _poseorigin_type poseorigin;
  using _posecad_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _posecad_type posecad;
  using _pointcloud_type =
    sensor_msgs::msg::PointCloud2_<ContainerAllocator>;
  _pointcloud_type pointcloud;

  // setters for named parameter idiom
  Type & set__label(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->label = _arg;
    return *this;
  }
  Type & set__poseorigin(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->poseorigin = _arg;
    return *this;
  }
  Type & set__posecad(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->posecad = _arg;
    return *this;
  }
  Type & set__pointcloud(
    const sensor_msgs::msg::PointCloud2_<ContainerAllocator> & _arg)
  {
    this->pointcloud = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__msg__LabeledPointCloud
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__msg__LabeledPointCloud
    std::shared_ptr<wzlscheduler_interfaces::msg::LabeledPointCloud_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LabeledPointCloud_ & other) const
  {
    if (this->label != other.label) {
      return false;
    }
    if (this->poseorigin != other.poseorigin) {
      return false;
    }
    if (this->posecad != other.posecad) {
      return false;
    }
    if (this->pointcloud != other.pointcloud) {
      return false;
    }
    return true;
  }
  bool operator!=(const LabeledPointCloud_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LabeledPointCloud_

// alias to use template instance with default allocator
using LabeledPointCloud =
  wzlscheduler_interfaces::msg::LabeledPointCloud_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__MSG__DETAIL__LABELED_POINT_CLOUD__STRUCT_HPP_
