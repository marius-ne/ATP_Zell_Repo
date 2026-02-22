
import numpy as np

if __name__ == '__main__':
    t =  [-0.19035098,
 -0.01819389,
  0.02748924]
    R = [[ 0.99949278, -0.02734792,  0.01631804],
 [ 0.01642375,  0.00364518, -0.99985848],
 [ 0.02728457,  0.99961933,  0.00409248]]
    T = np.eye(4)
    T[:3,:3] = R
    T[:3,3] = t
    print(np.linalg.norm(t))

    print("Original matrix:")
    print(T)
    m_inv = np.linalg.inv(T)
    print("Inverted matrix:")
    print(m_inv)

