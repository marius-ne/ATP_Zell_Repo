import numpy as np
from scipy.spatial.transform import Rotation as R

T = np.array(
    [[0.99978236, 0.00863432, -0.0189917, -0.16867381],
     [-0.01919375, 0.0239542, -0.99952879, -0.01404551],
     [-0.00817532, 0.99967577, 0.02411471, -0.00494919],
     [0.0, 0.0, 0.0, 1.0]]
)

translation = T[:3, 3]
rotation = R.from_matrix(T[:3, :3])
roll, pitch, yaw = rotation.as_euler('xyz', degrees=False)

print("xyz:", *translation)
print("rpy:", roll, pitch, yaw)