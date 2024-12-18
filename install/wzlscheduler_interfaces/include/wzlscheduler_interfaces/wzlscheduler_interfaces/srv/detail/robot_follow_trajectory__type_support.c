// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from wzlscheduler_interfaces:srv/RobotFollowTrajectory.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__rosidl_typesupport_introspection_c.h"
#include "wzlscheduler_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__functions.h"
#include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__struct.h"


// Include directives for member types
// Member `supportpoints`
#include "geometry_msgs/msg/pose.h"
// Member `supportpoints`
#include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__init(message_memory);
}

void wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_fini_function(void * message_memory)
{
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__fini(message_memory);
}

size_t wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__size_function__RobotFollowTrajectory_Request__supportpoints(
  const void * untyped_member)
{
  const geometry_msgs__msg__Pose__Sequence * member =
    (const geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  return member->size;
}

const void * wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__get_const_function__RobotFollowTrajectory_Request__supportpoints(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Pose__Sequence * member =
    (const geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  return &member->data[index];
}

void * wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__get_function__RobotFollowTrajectory_Request__supportpoints(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Pose__Sequence * member =
    (geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  return &member->data[index];
}

void wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__fetch_function__RobotFollowTrajectory_Request__supportpoints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Pose * item =
    ((const geometry_msgs__msg__Pose *)
    wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__get_const_function__RobotFollowTrajectory_Request__supportpoints(untyped_member, index));
  geometry_msgs__msg__Pose * value =
    (geometry_msgs__msg__Pose *)(untyped_value);
  *value = *item;
}

void wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__assign_function__RobotFollowTrajectory_Request__supportpoints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Pose * item =
    ((geometry_msgs__msg__Pose *)
    wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__get_function__RobotFollowTrajectory_Request__supportpoints(untyped_member, index));
  const geometry_msgs__msg__Pose * value =
    (const geometry_msgs__msg__Pose *)(untyped_value);
  *item = *value;
}

bool wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__resize_function__RobotFollowTrajectory_Request__supportpoints(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Pose__Sequence * member =
    (geometry_msgs__msg__Pose__Sequence *)(untyped_member);
  geometry_msgs__msg__Pose__Sequence__fini(member);
  return geometry_msgs__msg__Pose__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_message_member_array[1] = {
  {
    "supportpoints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request, supportpoints),  // bytes offset in struct
    NULL,  // default value
    wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__size_function__RobotFollowTrajectory_Request__supportpoints,  // size() function pointer
    wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__get_const_function__RobotFollowTrajectory_Request__supportpoints,  // get_const(index) function pointer
    wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__get_function__RobotFollowTrajectory_Request__supportpoints,  // get(index) function pointer
    wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__fetch_function__RobotFollowTrajectory_Request__supportpoints,  // fetch(index, &value) function pointer
    wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__assign_function__RobotFollowTrajectory_Request__supportpoints,  // assign(index, value) function pointer
    wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__resize_function__RobotFollowTrajectory_Request__supportpoints  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_message_members = {
  "wzlscheduler_interfaces__srv",  // message namespace
  "RobotFollowTrajectory_Request",  // message name
  1,  // number of fields
  sizeof(wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request),
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_message_member_array,  // message members
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_message_type_support_handle = {
  0,
  &wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_wzlscheduler_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, RobotFollowTrajectory_Request)() {
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  if (!wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_message_type_support_handle.typesupport_identifier) {
    wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &wzlscheduler_interfaces__srv__RobotFollowTrajectory_Request__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "wzlscheduler_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__functions.h"
// already included above
// #include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__init(message_memory);
}

void wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_fini_function(void * message_memory)
{
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_message_member_array[1] = {
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_message_members = {
  "wzlscheduler_interfaces__srv",  // message namespace
  "RobotFollowTrajectory_Response",  // message name
  1,  // number of fields
  sizeof(wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response),
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_message_member_array,  // message members
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_message_type_support_handle = {
  0,
  &wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_wzlscheduler_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, RobotFollowTrajectory_Response)() {
  if (!wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_message_type_support_handle.typesupport_identifier) {
    wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &wzlscheduler_interfaces__srv__RobotFollowTrajectory_Response__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "wzlscheduler_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "wzlscheduler_interfaces/srv/detail/robot_follow_trajectory__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers wzlscheduler_interfaces__srv__detail__robot_follow_trajectory__rosidl_typesupport_introspection_c__RobotFollowTrajectory_service_members = {
  "wzlscheduler_interfaces__srv",  // service namespace
  "RobotFollowTrajectory",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // wzlscheduler_interfaces__srv__detail__robot_follow_trajectory__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Request_message_type_support_handle,
  NULL  // response message
  // wzlscheduler_interfaces__srv__detail__robot_follow_trajectory__rosidl_typesupport_introspection_c__RobotFollowTrajectory_Response_message_type_support_handle
};

static rosidl_service_type_support_t wzlscheduler_interfaces__srv__detail__robot_follow_trajectory__rosidl_typesupport_introspection_c__RobotFollowTrajectory_service_type_support_handle = {
  0,
  &wzlscheduler_interfaces__srv__detail__robot_follow_trajectory__rosidl_typesupport_introspection_c__RobotFollowTrajectory_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, RobotFollowTrajectory_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, RobotFollowTrajectory_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_wzlscheduler_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, RobotFollowTrajectory)() {
  if (!wzlscheduler_interfaces__srv__detail__robot_follow_trajectory__rosidl_typesupport_introspection_c__RobotFollowTrajectory_service_type_support_handle.typesupport_identifier) {
    wzlscheduler_interfaces__srv__detail__robot_follow_trajectory__rosidl_typesupport_introspection_c__RobotFollowTrajectory_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)wzlscheduler_interfaces__srv__detail__robot_follow_trajectory__rosidl_typesupport_introspection_c__RobotFollowTrajectory_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, RobotFollowTrajectory_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, RobotFollowTrajectory_Response)()->data;
  }

  return &wzlscheduler_interfaces__srv__detail__robot_follow_trajectory__rosidl_typesupport_introspection_c__RobotFollowTrajectory_service_type_support_handle;
}
