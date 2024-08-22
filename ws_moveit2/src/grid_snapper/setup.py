from setuptools import find_packages, setup

package_name = 'grid_snapper'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='alexander',
    maintainer_email='a.wilczynski@wzl.rwth-aachen.de',
    description='Package which processes labeled image bounding boxes into 3d poses snapped into a grid.',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'image_to_world = grid_snapper.image_to_world:main',
            'pose_snapper = grid_snapper.pose_snapper:main'
        ],
    },
)
