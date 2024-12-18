# generated from rosidl_generator_py/resource/_idl.py.em
# with input from opcua_interfaces:msg/ActuatorRead.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ActuatorRead(type):
    """Metaclass of message 'ActuatorRead'."""

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
            module = import_type_support('opcua_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'opcua_interfaces.msg.ActuatorRead')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__actuator_read
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__actuator_read
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__actuator_read
            cls._TYPE_SUPPORT = module.type_support_msg__msg__actuator_read
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__actuator_read

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ActuatorRead(metaclass=Metaclass_ActuatorRead):
    """Message class 'ActuatorRead'."""

    __slots__ = [
        '_actuator_id',
        '_actuator_read_type',
        '_actuator_value_bool',
        '_actuator_value_int',
    ]

    _fields_and_field_types = {
        'actuator_id': 'string',
        'actuator_read_type': 'int8',
        'actuator_value_bool': 'boolean',
        'actuator_value_int': 'uint16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.actuator_id = kwargs.get('actuator_id', str())
        self.actuator_read_type = kwargs.get('actuator_read_type', int())
        self.actuator_value_bool = kwargs.get('actuator_value_bool', bool())
        self.actuator_value_int = kwargs.get('actuator_value_int', int())

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
        if self.actuator_id != other.actuator_id:
            return False
        if self.actuator_read_type != other.actuator_read_type:
            return False
        if self.actuator_value_bool != other.actuator_value_bool:
            return False
        if self.actuator_value_int != other.actuator_value_int:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def actuator_id(self):
        """Message field 'actuator_id'."""
        return self._actuator_id

    @actuator_id.setter
    def actuator_id(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'actuator_id' field must be of type 'str'"
        self._actuator_id = value

    @builtins.property
    def actuator_read_type(self):
        """Message field 'actuator_read_type'."""
        return self._actuator_read_type

    @actuator_read_type.setter
    def actuator_read_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'actuator_read_type' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'actuator_read_type' field must be an integer in [-128, 127]"
        self._actuator_read_type = value

    @builtins.property
    def actuator_value_bool(self):
        """Message field 'actuator_value_bool'."""
        return self._actuator_value_bool

    @actuator_value_bool.setter
    def actuator_value_bool(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'actuator_value_bool' field must be of type 'bool'"
        self._actuator_value_bool = value

    @builtins.property
    def actuator_value_int(self):
        """Message field 'actuator_value_int'."""
        return self._actuator_value_int

    @actuator_value_int.setter
    def actuator_value_int(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'actuator_value_int' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'actuator_value_int' field must be an unsigned integer in [0, 65535]"
        self._actuator_value_int = value
