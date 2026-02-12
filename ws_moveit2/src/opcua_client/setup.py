from setuptools import find_packages, setup

package_name = 'opcua_client'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools', 'opcua'],
    zip_safe=True,
    maintainer='christian',
    maintainer_email='christian@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'client_node = opcua_client.client_node:main',
            'publisher_to_client = opcua_client.publisher_to_client:main',
        ],
    },
)
