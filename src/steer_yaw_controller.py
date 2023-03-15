#! /usr/bin/env python

PORT='/dev/ttyUSB1' # update after checking arduino port
baud=9600

import rospy
import serial
import time
from alive_msgs.msg import Control
from geometry_msgs.msg import PoseStamped
import tf

current = 0

def isclose(a, b, rel_tol=1e-09, abs_tol=0.0):
    return abs(a-b) <= max(rel_tol * max(abs(a), abs(b)), abs_tol)

def serial_initialize():
    global port
    global initialized
    while not initialized:
        try:
            port = serial.Serial(PORT, baud)
            initialized = True
            print("serial up")
        except:
            print("waiting for serial")
            time.sleep(1)
            return

def pid_callback(msg):
    global current
    desired_steer = msg.steer + current
    print("steer: ", desired_steer)
    print("current ", current)
    if(not(isclose(desired_steer, current, rel_tol=0.1))):
        print("in isclose")
        if (desired_steer < current):
            # port.write(b'r')
            print("right")
        elif(desired_steer > current):
            # port.write(b'l')
            print("left")
        else:
            port.write(b's')
        time.sleep(0.1)

def floam_callback(msg):
    global current
    q = (msg.pose.orientation.x, msg.pose.orientation.y, msg.pose.orientation.z, msg.pose.orientation.w)
    r, p, y = tf.transformations.euler_from_quaternion(q)
    current = y
    

if __name__ == '__main__':
    
    initialized = False
    serial_initialize()
    rospy.init_node("steer_yaw_controller")
    rospy.Subscriber("/pid_info", Control, pid_callback)
    rospy.Subscriber("/pose", PoseStamped, floam_callback)
    rospy.spin()