#! /usr/bin/env python

import rospy
from alive_msgs.msg import StampedFloat64

n = 8.0
steer_pub = rospy.Publisher("/erick_steering", StampedFloat64, queue_size=1)


count = 0.0
steer_list = []

def filter(msg):
    global count
    count = count +1.0
    steer_list.append(msg.data)

    if (count%n == 0):
        steer = StampedFloat64()
        steer.header.stamp = rospy.Time.now()
        steer.data = sum(steer_list)/n
        steer_pub.publish(steer)
        print(int(steer.data))
        del steer_list[:]

if __name__ == '__main__':
    rospy.init_node("steer_feedback")
    rospy.Subscriber("/steer", StampedFloat64, filter)
    rospy.spin()