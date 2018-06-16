#!/bin/bash

export ROS_IP=192.168.8.102
export ROS_MASTER_URI=http://192.168.8.101:11311

source /home/ubuntu/catkin_ws/devel/setup.bash

exec "$@"
