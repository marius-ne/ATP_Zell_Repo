# generated from rosidl_generator_py/resource/_idl.py.em
# with input from wzlscheduler_interfaces:srv/RobotFollowTrajectory.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RobotFollowTrajectory_Request(type):
    """Metaclass of message 'RobotFollowTrajectory_Request'."""

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
                'wzlscheduler_interfaces.srv.RobotFollowTrajectory_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__robot_follow_trajectory__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__robot_follow_trajectory__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__robot_follow_trajectory__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__robot_follow_trajectory__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__robot_follow_trajectory__request

            from geometry_msgs.msg import Pose
            if Pose.__class__._TYPE_SUPPORT is None:
                Pose.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RobotFollowTrajectory_Request(metaclass=Metaclass_RobotFollowTrajectory_Request):
    """Message class 'RobotFollowTrajectory_Request'."""

    __slots__ = [
        '_supportpoints',
    ]

    _fields_and_field_types = {
        'supportpoints': 'sequence<geometry_msgs/Pose>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Pose')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.supportpoints = kwargs.get('supportpoints', [])

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
        if self.supportpoints != other.supportpoints:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def supportpoints(self):
        """Message field 'supportpoints'."""
        return self._supportpoints

    @supportpoints.setter
    def supportpoints(self, value):
        if __debug__:
            from geometry_msgs.msg import Pose
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, Pose) for v in value) and
                 True), \
                "The 'supportpoints' field must be a set or sequence and each value of type 'Pose'"
        self._supportpoints = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RobotFollowTrajectory_Response(type):
    """Metaclass of message 'RobotFollowTrajectory_Response'."""

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
                'wzlscheduler_interfaces.srv.RobotFollowTrajectory_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__robot_follow_trajectory__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__robot_follow_trajectory__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__robot_follow_trajectory__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__robot_follow_trajectory__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__robot_follow_trajectory__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RobotFollowTrajectory_Response(metaclass=Metaclass_RobotFollowTrajectory_Response):
    """Message class 'RobotFollowTrajectory_Response'."""

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


class Metaclass_RobotFollowTrajectory(type):
    """Metaclass of service 'RobotFollowTrajectory'."""

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
                'wzlscheduler_interfaces.srv.RobotFollowTrajectory')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__robot_follow_trajectory

            from wzlscheduler_interfaces.srv import _robot_follow_trajectory
            if _robot_follow_trajectory.Metaclass_RobotFollowTrajectory_Request._TYPE_SUPPORT is None:
                _robot_follow_trajectory.Metaclass_RobotFollowTrajectory_Request.__import_type_support__()
            if _robot_follow_trajectory.Metaclass_RobotFollowTrajectory_Response._TYPE_SUPPORT is None:
                _robot_follow_trajectory.Metaclass_RobotFollowTrajectory_Response.__import_type_support__()


class RobotFollowTrajectory(metaclass=Metaclass_RobotFollowTrajectory):
    from wzlscheduler_interfaces.srv._robot_follow_trajectory import RobotFollowTrajectory_Request as Request
    from wzlscheduler_interfaces.srv._robot_follow_trajectory import RobotFollowTrajectory_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
