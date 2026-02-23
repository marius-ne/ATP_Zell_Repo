
import numpy as np

if __name__ == '__main__':
    t =  [-0.16993593, -0.00991636,  0.02835384]

    R = [[ 0.9986449,  -0.04464343, -0.0267456 ],
 [-0.02712217, -0.00785062, -0.9996013 ],
 [ 0.04441567 , 0.99897214, -0.00905081]]
    
    T = np.eye(4)
    T[:3,:3] = R
    T[:3,3] = t
    print(np.linalg.norm(t))

    print("Original matrix:")
    print(T)
    m_inv = np.linalg.inv(T)
    print("Inverted matrix:")
    print(m_inv)

