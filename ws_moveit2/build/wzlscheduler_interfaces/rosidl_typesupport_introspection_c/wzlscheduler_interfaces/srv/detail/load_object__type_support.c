// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from wzlscheduler_interfaces:srv/LoadObject.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "wzlscheduler_interfaces/srv/detail/load_object__rosidl_typesupport_introspection_c.h"
#include "wzlscheduler_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "wzlscheduler_interfaces/srv/detail/load_object__functions.h"
#include "wzlscheduler_interfaces/srv/detail/load_object__struct.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"
// Member `coordinates`
#include "geometry_msgs/msg/pose.h"
// Member `coordinates`
#include "geometry_msgs/msg/detail/pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  wzlscheduler_interfaces__srv__LoadObject_Request__init(message_memory);
}

void wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_fini_function(void * message_memory)
{
  wzlscheduler_interfaces__srv__LoadObject_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_message_member_array[3] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces__srv__LoadObject_Request, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "coordinates",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces__srv__LoadObject_Request, coordinates),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "scale",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces__srv__LoadObject_Request, scale),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_message_members = {
  "wzlscheduler_interfaces__srv",  // message namespace
  "LoadObject_Request",  // message name
  3,  // number of fields
  sizeof(wzlscheduler_interfaces__srv__LoadObject_Request),
  wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_message_member_array,  // message members
  wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_message_type_support_handle = {
  0,
  &wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_wzlscheduler_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, LoadObject_Request)() {
  wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Pose)();
  if (!wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_message_type_support_handle.typesupport_identifier) {
    wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &wzlscheduler_interfaces__srv__LoadObject_Request__rosidl_typesupport_introspection_c__LoadObject_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "wzlscheduler_interfaces/srv/detail/load_object__rosidl_typesupport_introspection_c.h"
// already included above
// #include "wzlscheduler_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "wzlscheduler_interfaces/srv/detail/load_object__functions.h"
// already included above
// #include "wzlscheduler_interfaces/srv/detail/load_object__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  wzlscheduler_interfaces__srv__LoadObject_Response__init(message_memory);
}

void wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_fini_function(void * message_memory)
{
  wzlscheduler_interfaces__srv__LoadObject_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_message_member_array[1] = {
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(wzlscheduler_interfaces__srv__LoadObject_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_message_members = {
  "wzlscheduler_interfaces__srv",  // message namespace
  "LoadObject_Response",  // message name
  1,  // number of fields
  sizeof(wzlscheduler_interfaces__srv__LoadObject_Response),
  wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_message_member_array,  // message members
  wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_message_type_support_handle = {
  0,
  &wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_wzlscheduler_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, LoadObject_Response)() {
  if (!wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_message_type_support_handle.typesupport_identifier) {
    wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &wzlscheduler_interfaces__srv__LoadObject_Response__rosidl_typesupport_introspection_c__LoadObject_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "wzlscheduler_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "wzlscheduler_interfaces/srv/detail/load_object__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers wzlscheduler_interfaces__srv__detail__load_object__rosidl_typesupport_introspection_c__LoadObject_service_members = {
  "wzlscheduler_interfaces__srv",  // service namespace
  "LoadObject",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // wzlscheduler_interfaces__srv__detail__load_object__rosidl_typesupport_introspection_c__LoadObject_Request_message_type_support_handle,
  NULL  // response message
  // wzlscheduler_interfaces__srv__detail__load_object__rosidl_typesupport_introspection_c__LoadObject_Response_message_type_support_handle
};

static rosidl_service_type_support_t wzlscheduler_interfaces__srv__detail__load_object__rosidl_typesupport_introspection_c__LoadObject_service_type_support_handle = {
  0,
  &wzlscheduler_interfaces__srv__detail__load_object__rosidl_typesupport_introspection_c__LoadObject_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, LoadObject_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, LoadObject_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_wzlscheduler_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, LoadObject)() {
  if (!wzlscheduler_interfaces__srv__detail__load_object__rosidl_typesupport_introspection_c__LoadObject_service_type_support_handle.typesupport_identifier) {
    wzlscheduler_interfaces__srv__detail__load_object__rosidl_typesupport_introspection_c__LoadObject_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)wzlscheduler_interfaces__srv__detail__load_object__rosidl_typesupport_introspection_c__LoadObject_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, LoadObject_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, wzlscheduler_interfaces, srv, LoadObject_Response)()->data;
  }

  return &wzlscheduler_interfaces__srv__detail__load_object__rosidl_typesupport_introspection_c__LoadObject_service_type_support_handle;
}
