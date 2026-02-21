#!/usr/bin/env python3
"""
TCP Calibrator Node
===================
Reads recorded tool0 poses (from pose_getter in manual mode) where the robot
approached a fixed spike/point from various orientations, and computes the
TCP offset in the tool0 frame via least-squares optimization.

Theory
------
For each recorded pose i the base→tool0 transform is:
    T_i = [ R_i | t_i ]          (4×4 homogeneous)

The (unknown) TCP point expressed in tool0 is  p_tcp  (3×1).
In world coordinates the TCP tip is:
    P_world = R_i · p_tcp + t_i

Since the spike is fixed, every pose yields the same world point:
    R_i · p_tcp + t_i  =  R_j · p_tcp + t_j    ∀ i,j

Re-arranging for each pair (i, j):
    (R_i − R_j) · p_tcp  =  t_j − t_i

Stacking all pairs gives an over-determined system  A·p = b  which is
solved in the least-squares sense.

Usage
-----
  ros2 run tcp_calibrator tcp_calibrator --ros-args \
      -p yaml_path:=<path/to/recorded_poses.yaml>

Or without ROS, simply:
  python3 tcp_calibrator.py --yaml <path/to/recorded_poses.yaml>
"""

import sys
import argparse
import numpy as np
import yaml
from scipy.spatial.transform import Rotation as R

import rclpy
from rclpy.node import Node

# ---------------------------------------------------------------------------
# Core calibration algorithm
# ---------------------------------------------------------------------------

def calibrate_tcp(matrices: list[np.ndarray]):
    """
    Compute the TCP offset in the tool0 frame from N ≥ 3 recorded
    base→tool0 poses that all touch the same fixed point.

    Parameters
    ----------
    matrices : list of (4,4) ndarray
        Homogeneous base→tool0 transforms.

    Returns
    -------
    p_tcp : (3,) ndarray
        TCP position in tool0 frame  [x, y, z].
    spike_world : (3,) ndarray
        Estimated spike position in world/base frame.
    residuals : (N,) ndarray
        Per-pose Euclidean distance from the mean spike point (mm-scale
        quality indicator).
    """
    N = len(matrices)
    if N < 3:
        raise ValueError(f'Need at least 3 poses for TCP calibration, got {N}.')

    rotations = [T[:3, :3] for T in matrices]
    translations = [T[:3, 3] for T in matrices]

    # Build the over-determined system  A·p_tcp = b  from all unique pairs
    A_rows = []
    b_rows = []
    for i in range(N):
        for j in range(i + 1, N):
            A_rows.append(rotations[i] - rotations[j])
            b_rows.append(translations[j] - translations[i])

    A = np.vstack(A_rows)   # (M, 3)  where M = N*(N-1)/2 * 3
    b = np.concatenate(b_rows)  # (M,)

    # Least-squares solve
    result, residuals_ls, rank, sv = np.linalg.lstsq(A, b, rcond=None)
    p_tcp = result  # (3,)

    # Compute the spike point in world from each pose and gather residuals
    spike_points = np.array([R_i @ p_tcp + t_i
                             for R_i, t_i in zip(rotations, translations)])
    spike_world = spike_points.mean(axis=0)
    residuals = np.linalg.norm(spike_points - spike_world, axis=1)

    return p_tcp, spike_world, residuals


def format_results(p_tcp, spike_world, residuals, matrices):
    """Return a human-readable results string."""
    lines = []
    lines.append('=' * 60)
    lines.append('         TCP CALIBRATION RESULTS')
    lines.append('=' * 60)
    lines.append('')
    lines.append(f'  Poses used:          {len(matrices)}')
    lines.append('')
    lines.append('  TCP offset in tool0 frame (meters):')
    lines.append(f'    x = {p_tcp[0]: .6f}')
    lines.append(f'    y = {p_tcp[1]: .6f}')
    lines.append(f'    z = {p_tcp[2]: .6f}')
    lines.append(f'    ‖p‖= {np.linalg.norm(p_tcp):.6f}')
    lines.append('')
    lines.append('  Spike point in world/base frame (meters):')
    lines.append(f'    x = {spike_world[0]: .6f}')
    lines.append(f'    y = {spike_world[1]: .6f}')
    lines.append(f'    z = {spike_world[2]: .6f}')
    lines.append('')
    lines.append('  Per-pose residuals (mm):')
    for i, r in enumerate(residuals):
        lines.append(f'    Pose {i+1:>3d}:  {r * 1000:.3f} mm')
    lines.append('')
    lines.append(f'  Mean error:  {residuals.mean() * 1000:.3f} mm')
    lines.append(f'  Max  error:  {residuals.max() * 1000:.3f} mm')
    lines.append(f'  Std  error:  {residuals.std() * 1000:.3f} mm')
    lines.append('')

    # Build the 4×4 tool0→tcp transform (rotation = identity, translation = p_tcp)
    T_tool0_tcp = np.eye(4)
    T_tool0_tcp[:3, 3] = p_tcp
    np.set_printoptions(precision=6, suppress=True)
    lines.append('  tool0 → TCP  transform (4×4):')
    for row in T_tool0_tcp:
        lines.append(f'    {row}')
    lines.append('')

    # URDF snippet for easy copy-paste
    lines.append('  URDF joint snippet (copy into your xacro):')
    lines.append('  ──────────────────────────────────────────')
    lines.append(f'    <joint name="tool0_to_tcp" type="fixed">')
    lines.append(f'      <parent link="tool0"/>')
    lines.append(f'      <child link="tcp"/>')
    lines.append(f'      <origin xyz="{p_tcp[0]:.6f} {p_tcp[1]:.6f} {p_tcp[2]:.6f}" rpy="0 0 0"/>')
    lines.append(f'    </joint>')
    lines.append(f'    <link name="tcp"/>')
    lines.append('')
    lines.append('=' * 60)

    return '\n'.join(lines)


def save_results_yaml(path, p_tcp, spike_world, residuals):
    """Persist calibration results to a YAML file."""
    data = {
        'tcp_offset_tool0': {
            'x': float(p_tcp[0]),
            'y': float(p_tcp[1]),
            'z': float(p_tcp[2]),
            'norm': float(np.linalg.norm(p_tcp)),
        },
        'spike_world': {
            'x': float(spike_world[0]),
            'y': float(spike_world[1]),
            'z': float(spike_world[2]),
        },
        'quality': {
            'num_poses': int(len(residuals)),
            'mean_error_mm': float(residuals.mean() * 1000),
            'max_error_mm': float(residuals.max() * 1000),
            'std_error_mm': float(residuals.std() * 1000),
        },
        'transform_4x4': np.eye(4).tolist(),  # placeholder, filled below
    }
    T = np.eye(4)
    T[:3, 3] = p_tcp
    data['transform_4x4'] = [[float(v) for v in row] for row in T]

    with open(path, 'w') as f:
        yaml.dump(data, f, default_flow_style=False)
    return path


# ---------------------------------------------------------------------------
# YAML loader
# ---------------------------------------------------------------------------

def load_poses_from_yaml(yaml_path: str) -> list[np.ndarray]:
    """
    Load recorded poses from the pose_getter YAML file.

    Returns a list of 4×4 numpy arrays (base→tool0 transforms).
    """
    with open(yaml_path, 'r') as f:
        data = yaml.safe_load(f)

    if data is None or 'poses' not in data:
        raise ValueError(f'No "poses" key found in {yaml_path}')

    poses = data['poses']
    if len(poses) == 0:
        raise ValueError(f'No poses recorded in {yaml_path}')

    matrices = []
    for entry in poses:
        if 'matrix_4x4' in entry:
            T = np.array(entry['matrix_4x4'])
            if T.shape != (4, 4):
                raise ValueError(f"Pose id={entry.get('id','?')}: matrix_4x4 shape {T.shape} != (4,4)")
            matrices.append(T)
        else:
            # Fallback: reconstruct from position + quaternion
            pos = entry['position']
            quat = entry['orientation_quat']
            T = np.eye(4)
            T[:3, :3] = R.from_quat([quat['x'], quat['y'], quat['z'], quat['w']]).as_matrix()
            T[:3, 3] = [pos['x'], pos['y'], pos['z']]
            matrices.append(T)

    return matrices


# ---------------------------------------------------------------------------
# ROS 2 node wrapper
# ---------------------------------------------------------------------------

class TcpCalibratorNode(Node):
    def __init__(self):
        super().__init__('tcp_calibrator_node')

        # Declare parameters
        self.declare_parameter('yaml_path', '')
        self.declare_parameter('output_path', '')

        yaml_path = self.get_parameter('yaml_path').value
        output_path = self.get_parameter('output_path').value

        # If yaml_path not provided, use the default pose_getter location
        if not yaml_path:
            import os
            # Try the installed pose_getter location
            default = os.path.join(
                os.path.dirname(os.path.abspath(__file__)),
                '..', 'pose_getter', 'recorded_poses.yaml')
            default = os.path.normpath(default)
            if os.path.isfile(default):
                yaml_path = default
            else:
                # Try the source workspace location
                src_default = os.path.join(
                    os.path.dirname(os.path.abspath(__file__)),
                    '..', '..', '..', 'pose_getter', 'pose_getter', 'recorded_poses.yaml')
                src_default = os.path.normpath(src_default)
                if os.path.isfile(src_default):
                    yaml_path = src_default
                else:
                    self.get_logger().error(
                        'No yaml_path provided and could not find recorded_poses.yaml.\n'
                        '  Provide it via: -p yaml_path:=/path/to/recorded_poses.yaml')
                    return

        self.get_logger().info(f'Loading poses from: {yaml_path}')

        try:
            matrices = load_poses_from_yaml(yaml_path)
            self.get_logger().info(f'Loaded {len(matrices)} poses.')
        except Exception as e:
            self.get_logger().error(f'Failed to load poses: {e}')
            return

        try:
            p_tcp, spike_world, residuals = calibrate_tcp(matrices)
        except Exception as e:
            self.get_logger().error(f'Calibration failed: {e}')
            return

        # Print results
        report = format_results(p_tcp, spike_world, residuals, matrices)
        self.get_logger().info('\n' + report)

        # Save results YAML
        if not output_path:
            import os
            output_path = os.path.join(
                os.path.dirname(yaml_path), 'tcp_calibration_result.yaml')

        saved = save_results_yaml(output_path, p_tcp, spike_world, residuals)
        self.get_logger().info(f'Results saved to: {saved}')


# ---------------------------------------------------------------------------
# Entry points
# ---------------------------------------------------------------------------

def main(args=None):
    """ROS 2 entry point."""
    rclpy.init(args=args)
    node = TcpCalibratorNode()
    # One-shot node — no spinning needed, but keep alive briefly for logging
    node.destroy_node()
    if rclpy.ok():
        rclpy.shutdown()


def main_standalone():
    """Standalone CLI entry point (no ROS required)."""
    parser = argparse.ArgumentParser(description='TCP Calibrator — compute tool0→TCP offset')
    parser.add_argument('--yaml', required=True, help='Path to recorded_poses.yaml from pose_getter')
    parser.add_argument('--output', default=None, help='Path to save calibration result YAML')
    parsed = parser.parse_args()

    print(f'Loading poses from: {parsed.yaml}')
    matrices = load_poses_from_yaml(parsed.yaml)
    print(f'Loaded {len(matrices)} poses.\n')

    p_tcp, spike_world, residuals = calibrate_tcp(matrices)
    print(format_results(p_tcp, spike_world, residuals, matrices))

    import os
    out_path = parsed.output or os.path.join(
        os.path.dirname(parsed.yaml), 'tcp_calibration_result.yaml')
    save_results_yaml(out_path, p_tcp, spike_world, residuals)
    print(f'\nResults saved to: {out_path}')


if __name__ == '__main__':
    # Allow running directly as a script (without ROS)
    if '--yaml' in sys.argv:
        # run as: python3 tcp_calibrator.py --yaml /path/to/recorded_poses.yaml
        main_standalone()
    else:
        # run as: ros2 run tcp_calibrator tcp_calibrator --ros-args -p yaml_path:=/path/to/recorded_poses.yaml
        main()
