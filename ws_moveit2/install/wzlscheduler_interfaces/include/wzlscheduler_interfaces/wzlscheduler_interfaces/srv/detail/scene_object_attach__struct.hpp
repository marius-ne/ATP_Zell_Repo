// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from wzlscheduler_interfaces:srv/SceneObjectAttach.idl
// generated code does not contain a copyright notice

#ifndef WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ATTACH__STRUCT_HPP_
#define WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ATTACH__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAttach_Request __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAttach_Request __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SceneObjectAttach_Request_
{
  using Type = SceneObjectAttach_Request_<ContainerAllocator>;

  explicit SceneObjectAttach_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->parentkey = "";
    }
  }

  explicit SceneObjectAttach_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc),
    parentkey(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->parentkey = "";
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _parentkey_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _parentkey_type parentkey;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__parentkey(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->parentkey = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAttach_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAttach_Request
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SceneObjectAttach_Request_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->parentkey != other.parentkey) {
      return false;
    }
    return true;
  }
  bool operator!=(const SceneObjectAttach_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SceneObjectAttach_Request_

// alias to use template instance with default allocator
using SceneObjectAttach_Request =
  wzlscheduler_interfaces::srv::SceneObjectAttach_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces


#ifndef _WIN32
# define DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAttach_Response __attribute__((deprecated))
#else
# define DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAttach_Response __declspec(deprecated)
#endif

namespace wzlscheduler_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SceneObjectAttach_Response_
{
  using Type = SceneObjectAttach_Response_<ContainerAllocator>;

  explicit SceneObjectAttach_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0l;
    }
  }

  explicit SceneObjectAttach_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0l;
    }
  }

  // field types and members
  using _result_type =
    int32_t;
  _result_type result;

  // setters for named parameter idiom
  Type & set__result(
    const int32_t & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAttach_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__wzlscheduler_interfaces__srv__SceneObjectAttach_Response
    std::shared_ptr<wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SceneObjectAttach_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const SceneObjectAttach_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SceneObjectAttach_Response_

// alias to use template instance with default allocator
using SceneObjectAttach_Response =
  wzlscheduler_interfaces::srv::SceneObjectAttach_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace wzlscheduler_interfaces

namespace wzlscheduler_interfaces
{

namespace srv
{

struct SceneObjectAttach
{
  using Request = wzlscheduler_interfaces::srv::SceneObjectAttach_Request;
  using Response = wzlscheduler_interfaces::srv::SceneObjectAttach_Response;
};

}  // namespace srv

}  // namespace wzlscheduler_interfaces

#endif  // WZLSCHEDULER_INTERFACES__SRV__DETAIL__SCENE_OBJECT_ATTACH__STRUCT_HPP_
