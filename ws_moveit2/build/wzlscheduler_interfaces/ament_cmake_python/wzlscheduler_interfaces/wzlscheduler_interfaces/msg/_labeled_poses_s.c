// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from wzlscheduler_interfaces:msg/LabeledPoses.idl
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
#include "wzlscheduler_interfaces/msg/detail/labeled_poses__struct.h"
#include "wzlscheduler_interfaces/msg/detail/labeled_poses__functions.h"

bool wzlscheduler_interfaces__msg__labeled_pose__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * wzlscheduler_interfaces__msg__labeled_pose__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool wzlscheduler_interfaces__msg__labeled_poses__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[56];
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
    assert(strncmp("wzlscheduler_interfaces.msg._labeled_poses.LabeledPoses", full_classname_dest, 55) == 0);
  }
  wzlscheduler_interfaces__msg__LabeledPoses * ros_message = _ros_message;
  {  // elements
    PyObject * field = PyObject_GetAttrString(_pymsg, "elements");
    if (!field) {
      return false;
    }
    if (!wzlscheduler_interfaces__msg__labeled_pose__convert_from_py(field, &ros_message->elements)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * wzlscheduler_interfaces__msg__labeled_poses__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of LabeledPoses */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("wzlscheduler_interfaces.msg._labeled_poses");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "LabeledPoses");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  wzlscheduler_interfaces__msg__LabeledPoses * ros_message = (wzlscheduler_interfaces__msg__LabeledPoses *)raw_ros_message;
  {  // elements
    PyObject * field = NULL;
    field = wzlscheduler_interfaces__msg__labeled_pose__convert_to_py(&ros_message->elements);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "elements", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
