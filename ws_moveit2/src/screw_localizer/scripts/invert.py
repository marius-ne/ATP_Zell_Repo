
import numpy as np

if __name__ == '__main__':
    m = np.array([
        [ 0.99995032, -0.00990013, -0.00116185, -0.17185801],
        [-0.00140932, -0.02502558, -0.99968582, -0.01585551],
        [ 0.00986794,  0.99963779, -0.02503829,  0.03695767],
        [ 0.0,         0.0,         0.0,         1.0        ]
    ])
    t = m[:3, 3]
    print(np.linalg.norm(t))

    print("Original matrix:")
    print(m)
    m_inv = np.linalg.inv(m)
    print("Inverted matrix:")
    print(m_inv)

