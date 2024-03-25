# generated from rosidl_generator_py/resource/_idl.py.em
# with input from wzlscheduler_interfaces:srv/RobotMoveToPosition.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RobotMoveToPosition_Request(type):
    """Metaclass of message 'RobotMoveToPosition_Request'."""

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
            module = import_type_support('wzlscheduler_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'wzlscheduler_interfaces.srv.RobotMoveToPosition_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__robot_move_to_position__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__robot_move_to_position__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__robot_move_to_position__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__robot_move_to_position__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__robot_move_to_position__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RobotMoveToPosition_Request(metaclass=Metaclass_RobotMoveToPosition_Request):
    """Message class 'RobotMoveToPosition_Request'."""

    __slots__ = [
        '_posx',
        '_posy',
        '_posz',
        '_rotx',
        '_roty',
        '_rotz',
        '_movetype',
    ]

    _fields_and_field_types = {
        'posx': 'double',
        'posy': 'double',
        'posz': 'double',
        'rotx': 'double',
        'roty': 'double',
        'rotz': 'double',
        'movetype': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.posx = kwargs.get('posx', float())
        self.posy = kwargs.get('posy', float())
        self.posz = kwargs.get('posz', float())
        self.rotx = kwargs.get('rotx', float())
        self.roty = kwargs.get('roty', float())
        self.rotz = kwargs.get('rotz', float())
        self.movetype = kwargs.get('movetype', int())

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
        if self.posx != other.posx:
            return False
        if self.posy != other.posy:
            return False
        if self.posz != other.posz:
            return False
        if self.rotx != other.rotx:
            return False
        if self.roty != other.roty:
            return False
        if self.rotz != other.rotz:
            return False
        if self.movetype != other.movetype:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def posx(self):
        """Message field 'posx'."""
        return self._posx

    @posx.setter
    def posx(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'posx' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'posx' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._posx = value

    @builtins.property
    def posy(self):
        """Message field 'posy'."""
        return self._posy

    @posy.setter
    def posy(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'posy' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'posy' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._posy = value

    @builtins.property
    def posz(self):
        """Message field 'posz'."""
        return self._posz

    @posz.setter
    def posz(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'posz' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'posz' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._posz = value

    @builtins.property
    def rotx(self):
        """Message field 'rotx'."""
        return self._rotx

    @rotx.setter
    def rotx(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'rotx' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'rotx' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._rotx = value

    @builtins.property
    def roty(self):
        """Message field 'roty'."""
        return self._roty

    @roty.setter
    def roty(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'roty' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'roty' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._roty = value

    @builtins.property
    def rotz(self):
        """Message field 'rotz'."""
        return self._rotz

    @rotz.setter
    def rotz(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'rotz' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'rotz' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._rotz = value

    @builtins.property
    def movetype(self):
        """Message field 'movetype'."""
        return self._movetype

    @movetype.setter
    def movetype(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'movetype' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'movetype' field must be an integer in [-2147483648, 2147483647]"
        self._movetype = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RobotMoveToPosition_Response(type):
    """Metaclass of message 'RobotMoveToPosition_Response'."""

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
            module = import_type_support('wzlscheduler_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'wzlscheduler_interfaces.srv.RobotMoveToPosition_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__robot_move_to_position__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__robot_move_to_position__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__robot_move_to_position__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__robot_move_to_position__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__robot_move_to_position__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RobotMoveToPosition_Response(metaclass=Metaclass_RobotMoveToPosition_Response):
    """Message class 'RobotMoveToPosition_Response'."""

    __slots__ = [
        '_result',
    ]

    _fields_and_field_types = {
        'result': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.result = kwargs.get('result', int())

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
        if self.result != other.result:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def result(self):
        """Message field 'result'."""
        return self._result

    @result.setter
    def result(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'result' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'result' field must be an integer in [-2147483648, 2147483647]"
        self._result = value


class Metaclass_RobotMoveToPosition(type):
    """Metaclass of service 'RobotMoveToPosition'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('wzlscheduler_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'wzlscheduler_interfaces.srv.RobotMoveToPosition')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__robot_move_to_position

            from wzlscheduler_interfaces.srv import _robot_move_to_position
            if _robot_move_to_position.Metaclass_RobotMoveToPosition_Request._TYPE_SUPPORT is None:
                _robot_move_to_position.Metaclass_RobotMoveToPosition_Request.__import_type_support__()
            if _robot_move_to_position.Metaclass_RobotMoveToPosition_Response._TYPE_SUPPORT is None:
                _robot_move_to_position.Metaclass_RobotMoveToPosition_Response.__import_type_support__()


class RobotMoveToPosition(metaclass=Metaclass_RobotMoveToPosition):
    from wzlscheduler_interfaces.srv._robot_move_to_position import RobotMoveToPosition_Request as Request
    from wzlscheduler_interfaces.srv._robot_move_to_position import RobotMoveToPosition_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
