# generated from rosidl_generator_py/resource/_idl.py.em
# with input from wzlscheduler_interfaces:msg/LabeledPoses.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_LabeledPoses(type):
    """Metaclass of message 'LabeledPoses'."""

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
                'wzlscheduler_interfaces.msg.LabeledPoses')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__labeled_poses
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__labeled_poses
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__labeled_poses
            cls._TYPE_SUPPORT = module.type_support_msg__msg__labeled_poses
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__labeled_poses

            from wzlscheduler_interfaces.msg import LabeledPose
            if LabeledPose.__class__._TYPE_SUPPORT is None:
                LabeledPose.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class LabeledPoses(metaclass=Metaclass_LabeledPoses):
    """Message class 'LabeledPoses'."""

    __slots__ = [
        '_elements',
    ]

    _fields_and_field_types = {
        'elements': 'wzlscheduler_interfaces/LabeledPose',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['wzlscheduler_interfaces', 'msg'], 'LabeledPose'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from wzlscheduler_interfaces.msg import LabeledPose
        self.elements = kwargs.get('elements', LabeledPose())

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
        if self.elements != other.elements:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def elements(self):
        """Message field 'elements'."""
        return self._elements

    @elements.setter
    def elements(self, value):
        if __debug__:
            from wzlscheduler_interfaces.msg import LabeledPose
            assert \
                isinstance(value, LabeledPose), \
                "The 'elements' field must be a sub message of type 'LabeledPose'"
        self._elements = value
