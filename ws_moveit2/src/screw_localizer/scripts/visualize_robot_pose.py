#!/usr/bin/env python3
"""Live visualization of robot end-effector pose from ROS 2 topic."""

import threading
from typing import Optional

import rclpy
from geometry_msgs.msg import PoseStamped
from rclpy.node import Node
from scipy.spatial.transform import Rotation as R


class PoseVisualizer(Node):
    def __init__(self):
        super().__init__("pose_visualizer")
        self.current_pose: Optional[PoseStamped] = None
        self.pose_lock = threading.Lock()

        self.subscription = self.create_subscription(
            PoseStamped,
            "pose_getter/current_ee_pose",
            self.pose_callback,
            10,
        )
        self.get_logger().info("Subscribed to pose_getter/current_ee_pose")

    def pose_callback(self, msg: PoseStamped) -> None:
        with self.pose_lock:
            self.current_pose = msg


def visualize_live():
    """Live visualization of robot pose."""
    try:
        import matplotlib.pyplot as plt
        from mpl_toolkits.mplot3d import Axes3D
    except ImportError as e:
        print(f"Error: matplotlib required: {e}")
        return

    rclpy.init()
    node = PoseVisualizer()

    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection="3d")

    frame_scale = 0.1
    last_pose = None

    def update_plot():
        nonlocal last_pose
        with node.pose_lock:
            current_pose = node.current_pose

        if current_pose is None or current_pose == last_pose:
            return

        last_pose = current_pose
        ax.clear()

        pose = current_pose.pose
        pos = [pose.position.x, pose.position.y, pose.position.z]
        quat = [
            pose.orientation.x,
            pose.orientation.y,
            pose.orientation.z,
            pose.orientation.w,
        ]

        # Plot EE position
        ax.scatter(*pos, c="tab:purple", s=100, marker="o", label="EE")

        # Get rotation matrix and draw coordinate frame
        rot = R.from_quat(quat).as_matrix()
        x_axis = rot[:, 0] * frame_scale
        y_axis = rot[:, 1] * frame_scale
        z_axis = rot[:, 2] * frame_scale

        ax.quiver(
            pos[0],
            pos[1],
            pos[2],
            x_axis[0],
            x_axis[1],
            x_axis[2],
            color="r",
            arrow_length_ratio=0.2,
            linewidth=2,
            label="X",
        )
        ax.quiver(
            pos[0],
            pos[1],
            pos[2],
            y_axis[0],
            y_axis[1],
            y_axis[2],
            color="g",
            arrow_length_ratio=0.2,
            linewidth=2,
            label="Y",
        )
        ax.quiver(
            pos[0],
            pos[1],
            pos[2],
            z_axis[0],
            z_axis[1],
            z_axis[2],
            color="b",
            arrow_length_ratio=0.2,
            linewidth=2,
            label="Z",
        )

        # Add text with pose info
        info_text = (
            f"Position: ({pos[0]:.3f}, {pos[1]:.3f}, {pos[2]:.3f})\n"
            f"Quat: ({quat[0]:.3f}, {quat[1]:.3f}, {quat[2]:.3f}, {quat[3]:.3f})"
        )
        ax.text2D(0.05, 0.95, info_text, transform=ax.transAxes, fontsize=9, verticalalignment="top")

        ax.set_xlabel("X")
        ax.set_ylabel("Y")
        ax.set_zlabel("Z")
        ax.set_title("End Effector Pose (Live)")
        ax.legend(loc="upper right")
        ax.set_xlim([-1, 1])
        ax.set_ylim([-1, 1])
        ax.set_zlim([-1, 1])

    # Animation loop
    def animation_thread():
        while rclpy.ok():
            rclpy.spin_once(node, timeout_sec=0.01)
            update_plot()
            try:
                fig.canvas.draw_idle()
            except Exception:
                pass

    thread = threading.Thread(target=animation_thread, daemon=True)
    thread.start()

    plt.tight_layout()
    plt.show()

    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    visualize_live()
