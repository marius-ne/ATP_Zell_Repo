# generated from rosidl_generator_py/resource/_idl.py.em
# with input from opcua_interfaces_io_link:msg/SensorReadRequest.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SensorReadRequest(type):
    """Metaclass of message 'SensorReadRequest'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('opcua_interfaces_io_link')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'opcua_interfaces_io_link.msg.SensorReadRequest')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__sensor_read_request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__sensor_read_request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__sensor_read_request
            cls._TYPE_SUPPORT = module.type_support_msg__msg__sensor_read_request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__sensor_read_request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SensorReadRequest(metaclass=Metaclass_SensorReadRequest):
    """Message class 'SensorReadRequest'."""

    __slots__ = [
        '_sensor_id',
        '_sensor_read_type',
    ]

    _fields_and_field_types = {
        'sensor_id': 'string',
        'sensor_read_type': 'int8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.sensor_id = kwargs.get('sensor_id', str())
        self.sensor_read_type = kwargs.get('sensor_read_type', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.sensor_id != other.sensor_id:
            return False
        if self.sensor_read_type != other.sensor_read_type:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def sensor_id(self):
        """Message field 'sensor_id'."""
        return self._sensor_id

    @sensor_id.setter
    def sensor_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'sensor_id' field must be of type 'str'"
        self._sensor_id = value

    @builtins.property
    def sensor_read_type(self):
        """Message field 'sensor_read_type'."""
        return self._sensor_read_type

    @sensor_read_type.setter
    def sensor_read_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sensor_read_type' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'sensor_read_type' field must be an integer in [-128, 127]"
        self._sensor_read_type = value
