
import numpy as np

if __name__ == '__main__':
    m = np.array([[ 0.99978236,  0.00863432, -0.0189917,  -0.16867381],
                [-0.01919375,  0.0239542,  -0.99952879, -0.01404551],
                [-0.00817532,  0.99967577,  0.02411471, -0.00494919],
                [ 0.          ,  0.          ,  0.          ,  1.        ]])
    t = m[:3, 3]
    print(np.linalg.norm(t))

    print("Original matrix:")
    print(m)
    m_inv = np.linalg.inv(m)
    print("Inverted matrix:")
    print(m_inv)

