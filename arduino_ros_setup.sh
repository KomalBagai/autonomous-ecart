#!/bin/bash
# cd (find alive-dev)
catkin clean -y
catkin build e_rick
source devel/setup.bash
rm -r ros_lib/
rosrun rosserial_arduino make_libraries.py .
rm -r ~/Arduino/libraries/ros_lib
mv ros_lib ~/Arduino/libraries/
# cp temp/ros_lib/e_rick/ArduinoDataMsg.h src/e_rick/arduino_erick/
# rm -r temp/