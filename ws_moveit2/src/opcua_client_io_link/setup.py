from setuptools import find_packages, setup

package_name = 'opcua_client_io_link'

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
    maintainer='autopilot',
    maintainer_email='c.friedmann@wzl.rwth-aachen.de',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'client_node_io_link = opcua_client_io_link.client_node_io_link:main',
        ],
    },
)
