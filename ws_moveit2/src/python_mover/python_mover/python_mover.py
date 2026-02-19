"""
python_mover – Minimal Python node for moving the KUKA iiwa robot.

This node talks to the *moveit_backend* (moveit_iiwa) node through the
wzlscheduler_interfaces services, the same way that the C++ robo_planner
(Main_Remancell.cpp) does – but stripped down to the essentials so you can
quickly send the robot to a pose from Python.

Services used
-------------
- /robot_move_to_position  (wzlscheduler_interfaces/srv/RobotMoveToPosition)
- /robot_set_velocity      (wzlscheduler_interfaces/srv/RobotSetVelocity)

Move types (matching the C++ backend)
--------------------------------------
1 = Absolute PTP   (OMPL / RRTConnect)
2 = Relative PTP   (OMPL / RRTConnect)
3 = Absolute Cartesian (Pilz LIN)
4 = Relative Cartesian (Pilz LIN)

Velocity types
--------------
0 = OMPL (PTP)
1 = Pilz (Cartesian)
"""

import math
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Pose, Point, Quaternion

from wzlscheduler_interfaces.srv import RobotMoveToPosition, RobotSetVelocity


# ── Move‑type constants (mirror the C++ backend) ─────────────────────────
MOVE_ABS_PTP = 1
MOVE_REL_PTP = 2
MOVE_ABS_CART = 3
MOVE_REL_CART = 4

# ── Velocity‑type constants ──────────────────────────────────────────────
VEL_OMPL = 0   # PTP motions
VEL_PILZ = 1   # Cartesian motions


def euler_to_quaternion(roll: float, pitch: float, yaw: float) -> Quaternion:
    """Convert roll/pitch/yaw (radians) to a geometry_msgs Quaternion."""
    cr, sr = math.cos(roll / 2), math.sin(roll / 2)
    cp, sp = math.cos(pitch / 2), math.sin(pitch / 2)
    cy, sy = math.cos(yaw / 2), math.sin(yaw / 2)

    q = Quaternion()
    q.w = cr * cp * cy + sr * sp * sy
    q.x = sr * cp * cy - cr * sp * sy
    q.y = cr * sp * cy + sr * cp * sy
    q.z = cr * cp * sy - sr * sp * cy
    return q


class PythonMover(Node):
    """Thin wrapper around the moveit_backend movement services."""

    def __init__(self):
        super().__init__('python_mover')

        # -- service clients ------------------------------------------------
        self.cli_move = self.create_client(
            RobotMoveToPosition, 'robot_move_to_position')
        self.cli_vel = self.create_client(
            RobotSetVelocity, 'robot_set_velocity')

        self.get_logger().info('Waiting for moveit_backend services …')
        self.cli_move.wait_for_service()
        self.cli_vel.wait_for_service()
        self.get_logger().info('Services available – ready to move.')

    # ── public helpers ────────────────────────────────────────────────────

    def set_velocity(self, vel: float, accel: float,
                     vel_type: int = VEL_OMPL) -> bool:
        """Set velocity/acceleration scaling (type 0=OMPL, 1=Pilz)."""
        req = RobotSetVelocity.Request()
        req.velocityscalingfactor = float(vel)
        req.accelerationscalingfactor = float(accel)
        req.type = vel_type

        future = self.cli_vel.call_async(req)
        rclpy.spin_until_future_complete(self, future)
        result = future.result()
        if result is None:
            self.get_logger().error('set_velocity service call failed')
            return False
        self.get_logger().info(
            f'set_velocity(vel={vel}, accel={accel}, type={vel_type}) → {result.result}')
        return bool(result.result)

    def move_to_pose(self, x: float, y: float, z: float,
                     roll: float = math.pi, pitch: float = 0.0,
                     yaw: float = 0.0,
                     move_type: int = MOVE_ABS_PTP) -> bool:
        """Send the robot to a pose (Euler angles in radians).

        Default orientation is pointing straight down (roll=π).
        """
        pose = Pose()
        pose.position = Point(x=float(x), y=float(y), z=float(z))
        pose.orientation = euler_to_quaternion(roll, pitch, yaw)
        return self._send_move(pose, move_type)

    def move_to_pose_quat(self, x: float, y: float, z: float,
                          qx: float, qy: float, qz: float, qw: float,
                          move_type: int = MOVE_ABS_PTP) -> bool:
        """Send the robot to a pose (quaternion orientation)."""
        pose = Pose()
        pose.position = Point(x=float(x), y=float(y), z=float(z))
        pose.orientation = Quaternion(x=float(qx), y=float(qy),
                                      z=float(qz), w=float(qw))
        return self._send_move(pose, move_type)

    def move_relative(self, dx: float = 0.0, dy: float = 0.0,
                      dz: float = 0.0, cartesian: bool = False) -> bool:
        """Move relative to current position.

        If *cartesian* is True the backend uses Pilz LIN, otherwise OMPL PTP.
        Orientation fields are ignored for relative moves (the backend keeps
        the current orientation).
        """
        mt = MOVE_REL_CART if cartesian else MOVE_REL_PTP
        pose = Pose()
        pose.position = Point(x=float(dx), y=float(dy), z=float(dz))
        pose.orientation = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)
        return self._send_move(pose, mt)

    # ── private ───────────────────────────────────────────────────────────

    def _send_move(self, pose: Pose, move_type: int) -> bool:
        req = RobotMoveToPosition.Request()
        req.pose = pose
        req.movetype = move_type

        self.get_logger().info(
            f'Moving  type={move_type}  '
            f'pos=({pose.position.x:.4f}, {pose.position.y:.4f}, {pose.position.z:.4f})')

        future = self.cli_move.call_async(req)
        rclpy.spin_until_future_complete(self, future)
        result = future.result()
        if result is None:
            self.get_logger().error('move service call failed')
            return False
        ok = bool(result.result)
        if ok:
            self.get_logger().info('Move succeeded ✓')
        else:
            self.get_logger().error('Move FAILED ✗')
        return ok


# ── Demo sequence (runs when launched directly) ──────────────────────────

def main(args=None):
    rclpy.init(args=args)
    mover = PythonMover()

    # -- Set PTP speed (like taskSetSpeedPtp in Main_Remancell) ------------
    mover.set_velocity(vel=0.3, accel=0.3, vel_type=VEL_OMPL)

    # -- Set Cartesian speed (like taskSetSpeedCartesianFast) --------------
    mover.set_velocity(vel=0.1, accel=0.1, vel_type=VEL_PILZ)

    # -- Example: move to an absolute pose (PTP) --------------------------
    #    Pointing straight down, similar to the pick approach poses in
    #    Main_Remancell.cpp (roll=π, pitch=0, yaw≈0.5 rad)
    mover.get_logger().info('=== Demo: Absolute PTP move ===')
    mover.move_to_pose(
        x=0.3, y=0.0, z=0.4,
        roll=math.pi, pitch=0.0, yaw=0.5,
        move_type=MOVE_ABS_PTP,
    )

    # -- Example: small cartesian move down --------------------------------
    mover.get_logger().info('=== Demo: Relative cartesian move (down 5 cm) ===')
    mover.set_velocity(vel=0.03, accel=0.02, vel_type=VEL_PILZ)
    mover.move_relative(dz=-0.05, cartesian=True)

    # -- Example: move back up with PTP ------------------------------------
    mover.get_logger().info('=== Demo: Relative PTP move (up 5 cm) ===')
    mover.move_relative(dz=0.05, cartesian=False)

    mover.get_logger().info('Demo finished.')
    mover.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
