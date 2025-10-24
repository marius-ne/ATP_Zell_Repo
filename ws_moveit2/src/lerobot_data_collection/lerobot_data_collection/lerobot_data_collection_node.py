import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
import numpy as np
import pyarrow as pa
import pyarrow.parquet as pq
from pathlib import Path
import threading
import sys
import tty
import termios

class LeRobotDataCollector(Node):
    def __init__(self):
        super().__init__('lerobot_data_collector')
        self.get_logger().info('LeRobot Data Collection Node started')

        # TODO: 
        # -Add subscription to camera topic
        # -Add subscription to joint angle goals (capture data from tele-operation)
        # /iiwa_arm_controller/state or moveit_msgs/msg/DisplayTrajectory
        # -Add ability to load existing dataset
        # COMPLETE -Add ability to start/stop recording and keep/discard episodes, perhaps with some UI 
        # -Add ability to correct differences in timestamps between data sources
        # -Add ability to add recorded episode to current/loaded dataset when choosing to keep it
        # -Add ability to save dataset to disk, perhaps with some UI

        # Lists to which raw data will be stored while recording is true
        self.raw_joint_states = []
        self.raw_camera_images = []
        self.raw_controller_commands = []

        self.recording = False  # Flag to control if we are recording or not
        self.keep_episode = False  # Flag to control if we want to keep the recorded episode
        self.episode_index = 0  # Counter for episode numbering
        self.target_fps = 30.0  # Target frame rate for dataset (can be changed)
        
        self.joint_sub = self.create_subscription(JointState, '/joint_states', self.joint_callback, 10)
        
    # Recording raw data from joint states topic in a list
    def joint_callback(self, msg):
        if not self.recording:
            return
        
        self.raw_joint_states.append({
            'positions': list(msg.position),
            'velocities': list(msg.velocity),
            'efforts': list(msg.effort),
            'timestamp': msg.header.stamp.sec + msg.header.stamp.nanosec * 1e-9
        })

    def process_raw_data_to_frames(self):
        frames = {
            'observation.images.cam_high': [],
            'observation.state': [],
            'action': [],
            'episode_index': [],
            'frame_index': [],
            'timestamp': [],
            'next.done': [],
            'index': []
        }

        # We want to create frames from the raw data with a certain framerate, e.g., 30Hz
        # For that we need to, starting from the first frame, find what timestamps we want to keep
        # Then we need to group together image, joint and action data that are closest to one another in
        # time around each of these timestamps

        # Check if we have any data
        if not self.raw_joint_states:
            self.get_logger().warn('No joint state data to process')
            return frames
        
        # Get start and end timestamps from raw data
        start_time = self.raw_joint_states[0]['timestamp']
        end_time = self.raw_joint_states[-1]['timestamp']
        episode_duration = end_time - start_time
        
        self.get_logger().info(
            f'Processing episode: duration={episode_duration:.2f}s, '
            f'raw_joint_samples={len(self.raw_joint_states)}'
        )
        
        # Calculate time step for target FPS (e.g., 30Hz -> dt = 0.0333s)
        dt = 1.0 / self.target_fps
        
        # Generate target timestamps at regular intervals (30Hz)
        # Make sure we don't go beyond end_time
        target_timestamps = []
        current_time = start_time
        while current_time <= end_time:
            target_timestamps.append(current_time)
            current_time += dt
        
        num_frames = len(target_timestamps)
        
        self.get_logger().info(f'Will attempt to sample {num_frames} frames at {self.target_fps} Hz')
        
        # For each target timestamp, find the closest raw data
        joint_idx = 0
        
        for frame_idx, target_time in enumerate(target_timestamps):
            # Find closest joint state to target_time
            # Advance joint_idx to get close to target_time
            while (joint_idx < len(self.raw_joint_states) - 1 and 
                   self.raw_joint_states[joint_idx + 1]['timestamp'] <= target_time):
                joint_idx += 1
            
            # Check if the next sample is actually closer
            if joint_idx < len(self.raw_joint_states) - 1:
                current_diff = abs(self.raw_joint_states[joint_idx]['timestamp'] - target_time)
                next_diff = abs(self.raw_joint_states[joint_idx + 1]['timestamp'] - target_time)
                if next_diff < current_diff:
                    joint_idx += 1
            
            # Get the closest joint state data
            joint_state = self.raw_joint_states[joint_idx]
            
            # Log if timestamp mismatch is large (indicates sparse/inconsistent data)
            time_diff = abs(joint_state['timestamp'] - target_time)
            if time_diff > dt:  # If mismatch is larger than one frame period
                self.get_logger().warn(
                    f'Frame {frame_idx}: Large timestamp mismatch ({time_diff*1000:.1f}ms). '
                    f'Raw data may be sparse or inconsistent.'
                )
            
            # Create observation.state by concatenating positions + velocities + efforts
            observation_state = joint_state['positions'] + joint_state['velocities'] + joint_state['efforts']
            
            # TODO: Get corresponding action from raw_controller_commands
            # For now, use positions as placeholder action
            action = joint_state['positions']
            
            # Add frame data
            frames['observation.state'].append(observation_state)
            frames['action'].append(action)
            frames['episode_index'].append(self.episode_index)
            frames['frame_index'].append(frame_idx)
            frames['timestamp'].append(target_time - start_time) 
            frames['next.done'].append(frame_idx == num_frames - 1) 
            frames['index'].append(frame_idx)  # Can be updated later for multi-episode datasets
            
            # TODO: Add camera images when available
            # frames['observation.images.cam_high'].append(...)
        
        self.get_logger().info(
            f'Created {len(frames["frame_index"])} frames at {self.target_fps} Hz'
        )
        
        return frames
    
    def start_episode(self):
        """Start recording a new episode"""
        self.recording = True
        self.raw_joint_states = []
        self.raw_camera_images = []
        self.raw_controller_commands = []
        self.get_logger().info(f'🔴 RECORDING Episode {self.episode_index}')
    
    def stop_episode(self, keep=True):
        """Stop recording and optionally process the episode"""
        self.recording = False
        
        if not keep or len(self.raw_joint_states) == 0:
            self.get_logger().info(f'❌ Episode {self.episode_index} DISCARDED')
            self.raw_joint_states = []
            self.raw_camera_images = []
            self.raw_controller_commands = []
            return
        
        self.get_logger().info(f'✅ Processing Episode {self.episode_index}...')
        
        # Process raw data into frames
        frames = self.process_raw_data_to_frames()
        
        # TODO: Save frames to dataset (parquet, etc.)
        self.get_logger().info(
            f'✅ Episode {self.episode_index} SAVED: {len(frames["frame_index"])} frames'
        )
        
        # Increment episode counter for next recording
        self.episode_index += 1
        
        # Clear raw data buffers
        self.raw_joint_states = []
        self.raw_camera_images = []
        self.raw_controller_commands = []
    
    def print_status(self):
        """Print current status"""
        status = "🔴 RECORDING" if self.recording else "⚪ IDLE"
        print(f"\n{status} | Episode: {self.episode_index} | Samples: {len(self.raw_joint_states)}")

def get_key():
    """Get single keypress from terminal"""
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

def keyboard_ui_thread(node):
    """Run keyboard UI in separate thread"""
    print("\n" + "="*60)
    print("  LeRobot Data Collection - Keyboard Controls")
    print("="*60)
    print("  SPACE - Start/Stop recording")
    print("  k     - Keep episode (save)")
    print("  d     - Discard episode")
    print("  s     - Show status")
    print("  q     - Quit")
    print("="*60 + "\n")
    
    while rclpy.ok():
        try:
            key = get_key()
            
            if key == ' ':  # Space to toggle recording
                if not node.recording:
                    node.start_episode()
                else:
                    print("\nRecording stopped. Press 'k' to keep or 'd' to discard.")
            
            elif key == 'k':  # Keep episode
                if node.recording:
                    node.stop_episode(keep=True)
                else:
                    print("Not recording. Press SPACE to start.")
            
            elif key == 'd':  # Discard episode
                if node.recording:
                    node.stop_episode(keep=False)
                else:
                    print("Not recording. Press SPACE to start.")
            
            elif key == 's':  # Show status
                node.print_status()
            
            elif key == 'q':  # Quit
                print("\nQuitting...")
                break
                
        except Exception as e:
            print(f"Error in keyboard UI: {e}")
            break

def main(args=None):
    rclpy.init(args=args)
    node = LeRobotDataCollector()
    
    # Start keyboard UI thread
    ui_thread = threading.Thread(target=keyboard_ui_thread, args=(node,), daemon=True)
    ui_thread.start()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()