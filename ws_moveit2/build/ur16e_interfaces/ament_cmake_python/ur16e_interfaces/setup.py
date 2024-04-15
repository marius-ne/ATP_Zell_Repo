from setuptools import find_packages
from setuptools import setup

setup(
    name='ur16e_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('ur16e_interfaces', 'ur16e_interfaces.*')),
)
