#!/usr/bin/env python

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

# for your packages to be recognized by python
d = generate_distutils_setup(
 packages=['python_counter_algorithms', 'python_counter_ros'],
 package_dir={'python_counter_algorithms': 'src/python_counter_algorithms', 'python_counter_ros': 'src/python_counter_ros'}
)

setup(**d)
