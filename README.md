# Autonomous e-Cart

This repository contains the e_rick ROS package for the electric rickshaw built in-house at IIIT Delhi as a part of the autonomous driving project - [ALiVe](https://sites.google.com/iiitd.ac.in/iiitd-alive/home)

## Demonstrations
1. [Static Obstacle Avoidance Demo](https://drive.google.com/file/d/17ly8vjDxwKD6AAUSbPGurJAICTVWojyS/view?usp=sharing)
2. [Keyboard Teleop Operation Demo](https://drive.google.com/file/d/1okGMuzUyRnWGpcceMH9ix6SWWPQ29vHw/view?usp=sharing)
3. [Brake Demo](https://drive.google.com/file/d/1x5sxo3HWZK250eq7wjvr5276ZveoLLC3/view?usp=sharing)


![rick](resources/rick.png)

## Structure
This package contains the Arduino-based ROS node which gets the vehicle (in this case, a modified electric-cart) status and publishes it to the Planning stack. Thereafter, subscribes to the Control information for the vechicle to run autonomously.

The Keyboard teleop script shows how we can run the rickshaw drive-by-wire using keyboard or joystick.

Note: This package can NOT be run as a stand-alone ROS node; it needs other information along with sensory feedback from the vehicle.
