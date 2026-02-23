import os
from glob import glob

from setuptools import find_packages, setup

package_name = 'screw_localizer'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'),
            glob(os.path.join('launch', '*launch.[pxy][yma]*'))),
    ],
    scripts=['scripts/run_localization.py'],
    install_requires=['setuptools', 'ultralytics', 'opencv-python', 'numpy', 'scipy', "screw_interfaces"],
    zip_safe=True,
    maintainer='remanpilot',
    maintainer_email='m.e.neuhalfen@t-online.de',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'screw_localizer = screw_localizer.screw_depth_localizer:main',
            'screw_depth_localizer = screw_localizer.screw_depth_localizer:main',
            'screw_triangulator = screw_localizer.screw_triangulator:main',
            'client_localize_screws = screw_localizer.client_localize_screws:main'
        ],
    },
)
