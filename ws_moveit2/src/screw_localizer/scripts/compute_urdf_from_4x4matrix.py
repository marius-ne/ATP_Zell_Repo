import numpy as np
from scipy.spatial.transform import Rotation as R

# T should be Cam2EE (so in EE coordinates)
# this is the matrix straight out of the hand-eye calibration
T = np.array(
    [[ 0.99900278, -0.03064319, -0.03247217, -0.16988879],
     [-0.03303235, -0.01795506, -0.99929299, -0.01649049],
     [ 0.03003849,  0.99936911, -0.01894937,  0.03362782],
     [ 0.          ,  0.          ,  0.          ,  1.        ]]
)

translation = T[:3, 3]
rotation = R.from_matrix(T[:3, :3])
roll, pitch, yaw = rotation.as_euler('xyz', degrees=False)

translation_strings = [f"{t:.6g}" for t in translation]
rotation_strings = [f"{r:.6g}" for r in [roll, pitch, yaw]]  # xyzw format
print(f"xyz: {' '.join(translation_strings)}")
print(f"rpy: {' '.join(rotation_strings)}")
