import numpy as np
from scipy.spatial.transform import Rotation as R

# T should be Cam2EE (so in EE coordinates)
# this is the matrix straight out of the hand-eye calibration
T = np.array(
    [[ 0.9986449 , -0.04464343, -0.0267456,  -0.16993593],
 [-0.02712217, -0.00785062, -0.9996013,  -0.00991636],
 [ 0.04441567,  0.99897214, -0.00905081,  0.02835384],
 [ 0.          ,  0.          ,  0.          ,  1.        ]]
)

translation = T[:3, 3]
rotation = R.from_matrix(T[:3, :3])
roll, pitch, yaw = rotation.as_euler('xyz', degrees=False)

translation_strings = [f"{t:.6g}" for t in translation]
rotation_strings = [f"{r:.6g}" for r in [roll, pitch, yaw]]  # xyzw format
print(f"xyz: {' '.join(translation_strings)}")
print(f"rpy: {' '.join(rotation_strings)}")
