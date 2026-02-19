from setuptools import setup

package_name = 'python_mover'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='remanpilot',
    maintainer_email='m.e.neuhalfen@t-online.de',
    description='Minimal Python node for moving the KUKA iiwa robot',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'python_mover = python_mover.python_mover:main'
        ],
    },
)
