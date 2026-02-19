import numpy as np
from scipy.spatial.transform import Rotation as R

# T should be Cam2EE (so in EE coordinates)
# this is the matrix straight out of the hand-eye calibration
T = np.array(
    [[ 0.99995032, -0.00990013, -0.00116185, -0.17185801],
     [-0.00140932, -0.02502558, -0.99968582, -0.01585551],
     [ 0.00986794,  0.99963779, -0.02503829,  0.03695767],
     [ 0.          ,  0.          ,  0.          ,  1.        ]]
)

translation = T[:3, 3]
rotation = R.from_matrix(T[:3, :3])
roll, pitch, yaw = rotation.as_euler('xyz', degrees=False)

translation_strings = [f"{t:.6g}" for t in translation]
rotation_strings = [f"{r:.6g}" for r in [roll, pitch, yaw]]  # xyzw format
print(f"xyz: {' '.join(translation_strings)}")
print(f"rpy: {' '.join(rotation_strings)}")
