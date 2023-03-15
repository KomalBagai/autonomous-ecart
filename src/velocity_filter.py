#! /usr/bin/env python

import rospy
from scipy.stats import mode
from alive_msgs.msg import StampedFloat64
from alive_msgs.msg import StampedInt64

n = 9 # mode of n values, also rate of output msgs would be 80/n  
count = 0
vel = []
velocity = StampedFloat64()
filter_vel_pub = rospy.Publisher("/velocity", StampedFloat64, queue_size=1)

def vel_filter(msg):
    global count
    count = count+1
    vel.append(msg.data)
    if (count % n == 0):
        velocity.header.stamp = rospy.Time.now()
        velocity.data = mode(vel).mode[0]
        filter_vel_pub.publish(velocity)
        # print(vel, velocity.data)
        del vel[:]
        print(msg.data, velocity.data)
    # print(msg)


if __name__=="__main__":
    rospy.init_node("velocity_filter")
    rospy.Subscriber("/vel_pub", StampedInt64, vel_filter)
    rospy.spin()
    