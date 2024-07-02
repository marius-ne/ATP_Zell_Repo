from setuptools import find_packages
from setuptools import setup

setup(
    name='robo_planner_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('robo_planner_msgs', 'robo_planner_msgs.*')),
)
