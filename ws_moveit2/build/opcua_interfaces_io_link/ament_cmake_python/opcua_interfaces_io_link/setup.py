from setuptools import find_packages
from setuptools import setup

setup(
    name='opcua_interfaces_io_link',
    version='0.0.0',
    packages=find_packages(
        include=('opcua_interfaces_io_link', 'opcua_interfaces_io_link.*')),
)
