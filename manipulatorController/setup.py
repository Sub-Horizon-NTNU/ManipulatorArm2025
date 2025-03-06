from setuptools import setup, find_packages
import os
from glob import glob

setup(
    name='manipulatorController',
    version='0.0.1',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/manipulatorController']),
        ('share/manipulatorController', ['package.xml']),
    ],
    zip_safe=True,
    maintainer='your_name',
    maintainer_email='your@email.com',
    description='Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'manual_control_subscriber = manipulatorController.manual_control_subscriber:main'
        ],
    },
)