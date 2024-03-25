// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from wzlscheduler_interfaces:srv/RobotMoveToPosition.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "wzlscheduler_interfaces/srv/detail/robot_move_to_position__struct.h"
#include "wzlscheduler_interfaces/srv/detail/robot_move_to_position__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool wzlscheduler_interfaces__srv__robot_move_to_position__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[80];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("wzlscheduler_interfaces.srv._robot_move_to_position.RobotMoveToPosition_Request", full_classname_dest, 79) == 0);
  }
  wzlscheduler_interfaces__srv__RobotMoveToPosition_Request * ros_message = _ros_message;
  {  // posx
    PyObject * field = PyObject_GetAttrString(_pymsg, "posx");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->posx = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // posy
    PyObject * field = PyObject_GetAttrString(_pymsg, "posy");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->posy = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // posz
    PyObject * field = PyObject_GetAttrString(_pymsg, "posz");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->posz = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // rotx
    PyObject * field = PyObject_GetAttrString(_pymsg, "rotx");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->rotx = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // roty
    PyObject * field = PyObject_GetAttrString(_pymsg, "roty");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->roty = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // rotz
    PyObject * field = PyObject_GetAttrString(_pymsg, "rotz");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->rotz = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // movetype
    PyObject * field = PyObject_GetAttrString(_pymsg, "movetype");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->movetype = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * wzlscheduler_interfaces__srv__robot_move_to_position__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of RobotMoveToPosition_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("wzlscheduler_interfaces.srv._robot_move_to_position");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "RobotMoveToPosition_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  wzlscheduler_interfaces__srv__RobotMoveToPosition_Request * ros_message = (wzlscheduler_interfaces__srv__RobotMoveToPosition_Request *)raw_ros_message;
  {  // posx
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->posx);
    {
      int rc = PyObject_SetAttrString(_pymessage, "posx", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // posy
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->posy);
    {
      int rc = PyObject_SetAttrString(_pymessage, "posy", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // posz
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->posz);
    {
      int rc = PyObject_SetAttrString(_pymessage, "posz", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rotx
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->rotx);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rotx", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // roty
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->roty);
    {
      int rc = PyObject_SetAttrString(_pymessage, "roty", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rotz
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->rotz);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rotz", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // movetype
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->movetype);
    {
      int rc = PyObject_SetAttrString(_pymessage, "movetype", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "wzlscheduler_interfaces/srv/detail/robot_move_to_position__struct.h"
// already included above
// #include "wzlscheduler_interfaces/srv/detail/robot_move_to_position__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool wzlscheduler_interfaces__srv__robot_move_to_position__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[81];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("wzlscheduler_interfaces.srv._robot_move_to_position.RobotMoveToPosition_Response", full_classname_dest, 80) == 0);
  }
  wzlscheduler_interfaces__srv__RobotMoveToPosition_Response * ros_message = _ros_message;
  {  // result
    PyObject * field = PyObject_GetAttrString(_pymsg, "result");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->result = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * wzlscheduler_interfaces__srv__robot_move_to_position__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of RobotMoveToPosition_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("wzlscheduler_interfaces.srv._robot_move_to_position");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "RobotMoveToPosition_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  wzlscheduler_interfaces__srv__RobotMoveToPosition_Response * ros_message = (wzlscheduler_interfaces__srv__RobotMoveToPosition_Response *)raw_ros_message;
  {  // result
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->result);
    {
      int rc = PyObject_SetAttrString(_pymessage, "result", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
