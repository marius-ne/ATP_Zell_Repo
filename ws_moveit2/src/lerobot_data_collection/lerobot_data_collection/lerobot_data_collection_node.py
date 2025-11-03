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
import pandas as pd
from datetime import datetime

class LeRobotDataCollector(Node):
    def __init__(self):
        super().__init__('lerobot_data_collector')
        self.get_logger().info('LeRobot Data Collection Node started')

        # TODO: 
        # -Add subscription to camera topic
        # -Add method to record and save videos synchronized with data collection 
        # -Add subscription to joint angle goals (capture data from tele-operation)
        # -Synchronise data to image when making frames since those have lowest frequency
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

        # Dataset storage with proper LeRobot structure
        self.dataset = {
            'episodes': [],  # List of episode data (each episode contains frames)
            'meta': {
                'info': {
                    'codebase_version': 'v3.0',  # Must match installed LeRobot version
                    'fps': 30,
                    'robot_type': 'iiwa_arm',  # Update with your robot type
                    'total_episodes': 0,
                    'total_frames': 0,
                    'features': {},  # Will be populated when first episode is added
                    'data_path': 'data/chunk-{episode_chunk:03d}/episode_{episode_index:06d}.parquet',
                    'video_path': 'videos/chunk-{episode_chunk:03d}/episode_{episode_index:06d}.mp4'
                },
                'episodes': pd.DataFrame(columns=['episode_index', 'tasks', 'length', 'dataset_from_index', 'dataset_to_index']),
                'stats': {},  # Will be computed when saving
                'tasks': pd.DataFrame(columns=['task_index'])  # Tasks can be added later
            },
            'root': Path('/home/remanpilot/ws/lerobot_datasets')  # Datasets saved/loaded from here
        }
        
        self.dataset_name = None  # Name of currently loaded dataset
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
            # 'observation.images.cam_main': [], # TODO: Add when camera is implemented
            'observation.state': [], # Robot's state, like joint angles, velocity and effort.
            'action': [], # The action taken, like target joint angles.
            'episode_index': [], # ID for the episode.
            'frame_index': [], # ID for the frame within its episode (starts at 0 for each episode).
            'timestamp': [], # Time in seconds from the start of the episode.
            'next.done': [], # True if this is the last frame of an episode.
            'index': [], # A unique ID for the frame across the entire dataset.
            'task_index': [] # Task index for this frame (required by LeRobot)
        }

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

            # TODO: Add camera images when available
            # video_path = f'videos/chunk-{self.episode_index // 100:03d}/episode_{self.episode_index:06d}.mp4'
            # cam_main = {
            #     'path': video_path,
            #     'timestamp': target_time - start_time
            # }
            # frames['observation.images.cam_main'].append(cam_main)
            
            # Add frame data
            frames['observation.state'].append(observation_state)
            frames['action'].append(action)
            frames['episode_index'].append(self.episode_index)
            frames['frame_index'].append(frame_idx)
            frames['timestamp'].append(target_time - start_time) 
            frames['next.done'].append(frame_idx == num_frames - 1) 
            frames['index'].append(frame_idx)  # Can be updated later for multi-episode datasets
            
            
        
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
        
        # Add frames to dataset
        self.add_episode_to_dataset(frames, task_name='default_task')

        self.get_logger().info(
            f'✅ Episode {self.episode_index} SAVED: {len(frames["frame_index"])} frames'
        )
        
        # Increment episode counter for next recording
        self.episode_index += 1
        
        # Clear raw data buffers
        self.raw_joint_states = []
        self.raw_camera_images = []
        self.raw_controller_commands = []
    
    def add_episode_to_dataset(self, frames, task_name='default_task'):
        """Add a processed episode to the dataset with proper indexing"""
        
        if not frames or len(frames.get('frame_index', [])) == 0:
            self.get_logger().error('Cannot add empty episode to dataset')
            return
        
        num_frames = len(frames['frame_index'])
        current_total_frames = self.dataset['meta']['info']['total_frames']
        
        # Calculate dataset indices for this episode
        dataset_from_index = current_total_frames
        dataset_to_index = current_total_frames + num_frames
        
        # Update frame indices to be global across dataset
        frames_with_global_index = frames.copy()
        frames_with_global_index['index'] = list(range(dataset_from_index, dataset_to_index))
        
        # Update tasks DataFrame if new task and get task_index
        if task_name not in self.dataset['meta']['tasks'].index:
            task_index = len(self.dataset['meta']['tasks'])
            new_task = pd.DataFrame([{'task_index': task_index}], index=[task_name])
            self.dataset['meta']['tasks'] = pd.concat([self.dataset['meta']['tasks'], new_task])
        else:
            task_index = self.dataset['meta']['tasks'].loc[task_name, 'task_index']
        
        # Add task_index to all frames in this episode
        frames_with_global_index['task_index'] = [task_index] * num_frames
        
        # Store episode data
        episode_data = {
            'frames': frames_with_global_index,
            'episode_index': self.episode_index,
            'task': task_name,
            'num_frames': num_frames
        }
        self.dataset['episodes'].append(episode_data)
        
        # Update episode metadata DataFrame
        new_episode_row = pd.DataFrame([{
            'episode_index': self.episode_index,
            'tasks': [task_name],
            'length': num_frames,
            'dataset_from_index': dataset_from_index,
            'dataset_to_index': dataset_to_index
        }])
        
        self.dataset['meta']['episodes'] = pd.concat(
            [self.dataset['meta']['episodes'], new_episode_row],
            ignore_index=True
        )
        
        # Update metadata info
        self.dataset['meta']['info']['total_episodes'] += 1
        self.dataset['meta']['info']['total_frames'] += num_frames
        
        # Update features dict on first episode
        if self.dataset['meta']['info']['total_episodes'] == 1:
            self.dataset['meta']['info']['features'] = self._infer_features(frames_with_global_index)
        
        self.get_logger().info(
            f'Added episode {self.episode_index} to dataset: '
            f'{num_frames} frames, total dataset size: {self.dataset["meta"]["info"]["total_frames"]} frames'
        )
    
    def _infer_features(self, frames):
        """Infer feature types and shapes from first episode"""
        features = {}
        
        # observation.state
        if 'observation.state' in frames and len(frames['observation.state']) > 0:
            state_dim = len(frames['observation.state'][0])
            
            # Assuming 7-joint robot with positions, velocities, and efforts
            # state_dim should be 21 (7 joints × 3 measurements)
            num_joints = state_dim // 3
            
            # Create descriptive names for each dimension
            state_names = []
            # Positions
            for i in range(num_joints):
                state_names.append(f'joint_{i+1}_position')
            # Velocities
            for i in range(num_joints):
                state_names.append(f'joint_{i+1}_velocity')
            # Efforts
            for i in range(num_joints):
                state_names.append(f'joint_{i+1}_effort')
            
            features['observation.state'] = {
                'dtype': 'float32',
                'shape': [state_dim],
                'names': state_names
            }
        
        # action
        if 'action' in frames and len(frames['action']) > 0:
            action_dim = len(frames['action'][0])
            
            # Create descriptive names for action dimensions (target joint positions)
            action_names = []
            for i in range(action_dim):
                action_names.append(f'joint_{i+1}_target_position')
            
            features['action'] = {
                'dtype': 'float32',
                'shape': [action_dim],
                'names': action_names
            }
        
        # observation.images.cam_main (VideoFrame)
        # if 'observation.images.cam_main' in frames:
        #     features['observation.images.cam_main'] = {
        #         'dtype': 'video',
        #         'shape': [1],  # Scalar video frame reference
        #         'names': ['path', 'timestamp']
        #     }
        
        # Standard fields - use [1] for scalars instead of []
        features['episode_index'] = {'dtype': 'int64', 'shape': [1], 'names': []}
        features['frame_index'] = {'dtype': 'int64', 'shape': [1], 'names': []}
        features['timestamp'] = {'dtype': 'float32', 'shape': [1], 'names': []}
        features['next.done'] = {'dtype': 'bool', 'shape': [1], 'names': []}
        features['index'] = {'dtype': 'int64', 'shape': [1], 'names': []}
        features['task_index'] = {'dtype': 'int64', 'shape': [1], 'names': []}
        
        return features

    def load_dataset(self, dataset_name):
        """Load existing dataset from disk"""
        dataset_root = Path('/home/remanpilot/ws/lerobot_datasets') / dataset_name
        
        if not dataset_root.exists():
            self.get_logger().error(f'Dataset not found: {dataset_root}')
            print(f"❌ Dataset '{dataset_name}' not found at {dataset_root}")
            return
        
        try:
            # Load metadata
            meta_path = dataset_root / 'meta'
            
            # Load info.json
            import json
            info_path = meta_path / 'info.json'
            with open(info_path, 'r') as f:
                info = json.load(f)
            
            # Load episodes.parquet from nested directory (LeRobot v3.0 format)
            episodes_dir = meta_path / 'episodes'
            episodes_path = episodes_dir / 'episodes.parquet'
            episodes_df = pd.read_parquet(episodes_path)
            
            # Load tasks.parquet from nested directory
            tasks_path = meta_path / 'tasks.parquet'
            tasks_df = pd.read_parquet(tasks_path)
            
            # Load stats (if exists)
            stats = {}
            stats_path = meta_path / 'stats.json'
            if stats_path.exists():
                with open(stats_path, 'r') as f:
                    stats = json.load(f)
            
            # Initialize dataset structure
            self.dataset = {
                'episodes': [],
                'meta': {
                    'info': info,
                    'episodes': episodes_df,
                    'stats': stats,
                    'tasks': tasks_df
                },
                'root': dataset_root
            }
            
            # Load episode data from parquet files
            data_dir = dataset_root / 'data'
            for _, episode_row in episodes_df.iterrows():
                ep_idx = episode_row['episode_index']
                chunk_idx = ep_idx // 100  # Group episodes in chunks of 100
                
                # Load episode parquet file
                episode_file = data_dir / f'chunk-{chunk_idx:03d}' / f'episode_{ep_idx:06d}.parquet'
                
                if episode_file.exists():
                    episode_table = pq.read_table(episode_file)
                    frames = {col: episode_table[col].to_pylist() for col in episode_table.column_names}
                    
                    episode_data = {
                        'frames': frames,
                        'episode_index': ep_idx,
                        'task': episode_row['tasks'][0] if len(episode_row['tasks']) > 0 else 'default_task',
                        'num_frames': episode_row['length']
                    }
                    self.dataset['episodes'].append(episode_data)
                else:
                    self.get_logger().warn(f'Episode file not found: {episode_file}')
            
            # Update node state
            self.dataset_name = dataset_name
            self.episode_index = info['total_episodes']  # Continue from last episode
            
            self.get_logger().info(
                f'✅ Loaded dataset "{dataset_name}": '
                f'{info["total_episodes"]} episodes, {info["total_frames"]} frames'
            )
            print(f'✅ Loaded dataset "{dataset_name}" with {info["total_episodes"]} episodes')
            
        except Exception as e:
            self.get_logger().error(f'Failed to load dataset: {e}')
            print(f'❌ Failed to load dataset: {e}')

    def save_dataset(self, dataset_name):
        """Save current dataset to disk in Parquet format"""
        
        if not self.dataset['episodes']:
            self.get_logger().error('No episodes to save')
            print('❌ No episodes to save')
            return
        
        # Set dataset root path
        dataset_root = Path('/home/remanpilot/ws/lerobot_datasets') / dataset_name
        dataset_root.mkdir(parents=True, exist_ok=True)
        
        self.dataset['root'] = dataset_root
        self.dataset_name = dataset_name
        
        try:
            # Create directory structure
            data_dir = dataset_root / 'data'
            video_dir = dataset_root / 'videos'
            meta_dir = dataset_root / 'meta'
            
            data_dir.mkdir(exist_ok=True)
            video_dir.mkdir(exist_ok=True)
            meta_dir.mkdir(exist_ok=True)
            
            # Compute statistics before saving
            self._compute_stats()
            
            # Save each episode to parquet
            for episode_data in self.dataset['episodes']:
                ep_idx = episode_data['episode_index']
                chunk_idx = ep_idx // 100  # Group episodes in chunks of 100
                
                chunk_dir = data_dir / f'chunk-{chunk_idx:03d}'
                chunk_dir.mkdir(exist_ok=True)
                
                # Convert frames dict to PyArrow Table
                frames = episode_data['frames']
                
                # Build schema with proper types
                schema_fields = []
                arrays = {}
                
                for key, values in frames.items():
                    if key == 'observation.state' or key == 'action':
                        # Keep as list of lists, don't flatten
                        # PyArrow will handle the nested structure
                        arrays[key] = pa.array(values, type=pa.list_(pa.float32()))
                        schema_fields.append(pa.field(key, pa.list_(pa.float32())))
                    
                    # elif key == 'observation.images.cam_main':
                    #     # VideoFrame stored as struct with path and timestamp
                    #     paths = [v['path'] for v in values]
                    #     timestamps = [v['timestamp'] for v in values]
                    #     arrays[key] = pa.StructArray.from_arrays(
                    #         [pa.array(paths), pa.array(timestamps, type=pa.float32())],
                    #         names=['path', 'timestamp']
                    #     )
                    #     schema_fields.append(pa.field(key, pa.struct([
                    #         ('path', pa.string()),
                    #         ('timestamp', pa.float32())
                    #     ])))
                    
                    elif key in ['episode_index', 'frame_index', 'index', 'task_index']:
                        arrays[key] = pa.array(values, type=pa.int64())
                        schema_fields.append(pa.field(key, pa.int64()))
                    
                    elif key == 'timestamp':
                        arrays[key] = pa.array(values, type=pa.float32())
                        schema_fields.append(pa.field(key, pa.float32()))
                    
                    elif key == 'next.done':
                        arrays[key] = pa.array(values, type=pa.bool_())
                        schema_fields.append(pa.field(key, pa.bool_()))
                
                # Create table and write to parquet
                schema = pa.schema(schema_fields)
                table = pa.table(arrays, schema=schema)
                
                episode_file = chunk_dir / f'episode_{ep_idx:06d}.parquet'
                pq.write_table(table, episode_file)
                
                self.get_logger().info(f'Saved episode {ep_idx} to {episode_file}')
            
            # Save metadata
            import json
            
            # Save info.json
            info_path = meta_dir / 'info.json'
            with open(info_path, 'w') as f:
                json.dump(self.dataset['meta']['info'], f, indent=2)
            
            # Save episodes.parquet in nested chunk structure (LeRobot v3.0 format)
            # LeRobot expects episodes metadata in chunk subdirectories
            episodes_dir = meta_dir / 'episodes'
            episodes_dir.mkdir(exist_ok=True)
            episodes_chunk_dir = episodes_dir / 'chunk-000'
            episodes_chunk_dir.mkdir(exist_ok=True)
            episodes_path = episodes_chunk_dir / 'episodes_000000.parquet'
            self.dataset['meta']['episodes'].to_parquet(episodes_path)
            
            # Save tasks.parquet directly in meta/ (NOT in nested directory)
            tasks_path = meta_dir / 'tasks.parquet'
            self.dataset['meta']['tasks'].to_parquet(tasks_path)
            
            # Save stats.json
            if self.dataset['meta']['stats']:
                stats_path = meta_dir / 'stats.json'
                # Convert tensors to lists for JSON serialization
                stats_serializable = {}
                for key, stat_dict in self.dataset['meta']['stats'].items():
                    stats_serializable[key] = {
                        stat_type: values.tolist() if hasattr(values, 'tolist') else values
                        for stat_type, values in stat_dict.items()
                    }
                with open(stats_path, 'w') as f:
                    json.dump(stats_serializable, f, indent=2)
            
            self.get_logger().info(
                f'✅ Saved dataset "{dataset_name}" to {dataset_root}: '
                f'{self.dataset["meta"]["info"]["total_episodes"]} episodes, '
                f'{self.dataset["meta"]["info"]["total_frames"]} frames'
            )
            print(f'✅ Dataset saved to: {dataset_root}')
            
        except Exception as e:
            self.get_logger().error(f'Failed to save dataset: {e}')
            print(f'❌ Failed to save dataset: {e}')
            import traceback
            traceback.print_exc()
    
    def _compute_stats(self):
        """Compute statistics (min, max, mean, std) for normalization"""
        if not self.dataset['episodes']:
            return
        
        # Collect all observations and actions
        all_states = []
        all_actions = []
        
        for episode_data in self.dataset['episodes']:
            frames = episode_data['frames']
            if 'observation.state' in frames:
                all_states.extend(frames['observation.state'])
            if 'action' in frames:
                all_actions.extend(frames['action'])
        
        # Convert to numpy arrays
        if all_states:
            states_array = np.array(all_states, dtype=np.float32)
            self.dataset['meta']['stats']['observation.state'] = {
                'min': states_array.min(axis=0),
                'max': states_array.max(axis=0),
                'mean': states_array.mean(axis=0),
                'std': states_array.std(axis=0)
            }
        
        if all_actions:
            actions_array = np.array(all_actions, dtype=np.float32)
            self.dataset['meta']['stats']['action'] = {
                'min': actions_array.min(axis=0),
                'max': actions_array.max(axis=0),
                'mean': actions_array.mean(axis=0),
                'std': actions_array.std(axis=0)
            }
        
        self.get_logger().info('Computed dataset statistics for normalization')

    def print_status(self):
        """Print current status"""
        status = "🔴 RECORDING" if self.recording else "⚪ IDLE"
        dataset_info = f"Dataset: {self.dataset_name or 'Unnamed'}"
        total_episodes = self.dataset['meta']['info']['total_episodes']
        total_frames = self.dataset['meta']['info']['total_frames']
        
        print(f"\n{status} | Episode: {self.episode_index} | Samples: {len(self.raw_joint_states)}")
        print(f"{dataset_info} | Total Episodes: {total_episodes} | Total Frames: {total_frames}")

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
    print("  l     - Load existing dataset from disk")
    print("  p     - Save current dataset to disk")
    print("  SPACE - Start/Stop recording")
    print("  k     - Keep episode (save)")
    print("  d     - Discard episode")
    print("  s     - Show status")
    print("  q     - Quit")
    print("="*60 + "\n")
    
    while rclpy.ok():
        try:
            key = get_key()

            if key == 'l':  # Load dataset, prompt for name
                # Only load if not currently recording 
                # and if self.dataset is empty to avoid overriding recorded data
                if not node.recording:
                    if len(node.dataset['episodes']) > 0:
                        print(f"\n⚠️  Warning: Current dataset has {node.dataset['meta']['info']['total_episodes']} episodes.")
                        print("Options:")
                        print("  p - Save current dataset first, then load")
                        print("  c - Continue and discard current data")
                        print("  Any other key - Cancel")
                        confirm = get_key()
                        
                        if confirm == 'p':
                            # If user pressed 'p', save current dataset first
                            save_name = input("\nEnter name to save current dataset under: ")
                            node.save_dataset(save_name)
                        elif confirm == 'c':
                            # User chose to discard current data
                            print("⚠️  Discarding current dataset...")
                        else:
                            print("Load cancelled.")
                            continue
                    
                    dataset_name = input("\nEnter name of dataset to load: ")
                    node.load_dataset(dataset_name)
                else:
                    print("Cannot load dataset while recording. Stop recording first.")

            elif key == 'p':  # Save dataset if not recording AND dataset is not empty
                if not node.recording:
                    if len(node.dataset) == 0:
                        print("No dataset to save. Record some episodes first.")
                    else:
                        dataset_name = input("\nEnter name to save dataset under: ")
                        node.save_dataset(dataset_name)
                else:
                    print("Cannot save dataset while recording. Stop recording first.")

            elif key == ' ':  # Space to toggle recording
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