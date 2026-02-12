from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'modbus_client'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
    ],
    install_requires=['setuptools', 'pymodbus'],
    zip_safe=True,
    maintainer='todo',
    maintainer_email='todo',
    description='Package provides a Modbus client node for ROS2 with read and write services',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'modbus_client_node = modbus_client.modbus_client_node:main'
        ],
    },
)
