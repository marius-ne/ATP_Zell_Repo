from setuptools import find_packages, setup

package_name = 'screw_detector'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/weights', ['weights/best.pt']),
        ('share/' + package_name + '/weights', ['weights/best_huelse_aug.pt']),
        ('share/' + package_name + '/weights', ['weights/segmentation_model.pth']),
    ],
    install_requires=['setuptools', 'ultralytics', 'opencv-python', 'numpy', 'torch', 'torchvision'],
    zip_safe=True,
    maintainer='marius_neuhalfen',
    maintainer_email='marius.neuhalfen@rwth-aachen.de',
    description='detects screws for unscrewing them',
    license='TODO',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'screw_detector = screw_detector.screw_detector:main',
            'screw_segmentor = screw_detector.screw_segmentor:main'
        ],
    },
)
