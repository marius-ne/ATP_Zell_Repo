# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robo_planner_msgs:msg/LabeledPointCloud.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_LabeledPointCloud(type):
    """Metaclass of message 'LabeledPointCloud'."""

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
            module = import_type_support('robo_planner_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'robo_planner_msgs.msg.LabeledPointCloud')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__labeled_point_cloud
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__labeled_point_cloud
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__labeled_point_cloud
            cls._TYPE_SUPPORT = module.type_support_msg__msg__labeled_point_cloud
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__labeled_point_cloud

            from geometry_msgs.msg import Pose
            if Pose.__class__._TYPE_SUPPORT is None:
                Pose.__class__.__import_type_support__()

            from sensor_msgs.msg import PointCloud2
            if PointCloud2.__class__._TYPE_SUPPORT is None:
                PointCloud2.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class LabeledPointCloud(metaclass=Metaclass_LabeledPointCloud):
    """Message class 'LabeledPointCloud'."""

    __slots__ = [
        '_label',
        '_poseorigin',
        '_posecad',
        '_pointcloud',
    ]

    _fields_and_field_types = {
        'label': 'string',
        'poseorigin': 'geometry_msgs/Pose',
        'posecad': 'geometry_msgs/Pose',
        'pointcloud': 'sensor_msgs/PointCloud2',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Pose'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Pose'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['sensor_msgs', 'msg'], 'PointCloud2'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.label = kwargs.get('label', str())
        from geometry_msgs.msg import Pose
        self.poseorigin = kwargs.get('poseorigin', Pose())
        from geometry_msgs.msg import Pose
        self.posecad = kwargs.get('posecad', Pose())
        from sensor_msgs.msg import PointCloud2
        self.pointcloud = kwargs.get('pointcloud', PointCloud2())

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
        if self.label != other.label:
            return False
        if self.poseorigin != other.poseorigin:
            return False
        if self.posecad != other.posecad:
            return False
        if self.pointcloud != other.pointcloud:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def label(self):
        """Message field 'label'."""
        return self._label

    @label.setter
    def label(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'label' field must be of type 'str'"
        self._label = value

    @builtins.property
    def poseorigin(self):
        """Message field 'poseorigin'."""
        return self._poseorigin

    @poseorigin.setter
    def poseorigin(self, value):
        if __debug__:
            from geometry_msgs.msg import Pose
            assert \
                isinstance(value, Pose), \
                "The 'poseorigin' field must be a sub message of type 'Pose'"
        self._poseorigin = value

    @builtins.property
    def posecad(self):
        """Message field 'posecad'."""
        return self._posecad

    @posecad.setter
    def posecad(self, value):
        if __debug__:
            from geometry_msgs.msg import Pose
            assert \
                isinstance(value, Pose), \
                "The 'posecad' field must be a sub message of type 'Pose'"
        self._posecad = value

    @builtins.property
    def pointcloud(self):
        """Message field 'pointcloud'."""
        return self._pointcloud

    @pointcloud.setter
    def pointcloud(self, value):
        if __debug__:
            from sensor_msgs.msg import PointCloud2
            assert \
                isinstance(value, PointCloud2), \
                "The 'pointcloud' field must be a sub message of type 'PointCloud2'"
        self._pointcloud = value
