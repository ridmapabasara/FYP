#!/bin/bash
sudo killall gzserver
sudo killall gzclient
sudo killall rviz
sudo killall roscore
sudo killall rosmaster
roslaunch mybot_navigation FX.launch
