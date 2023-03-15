import rospy
from alive_msgs.msg import Control

def dummy_pid():
    pub_ = rospy.Publisher("/pid_info", Control, queue_size=1)
    rospy.init_node("dummy_pid")
    rate = rospy.Rate(10)
    msg = Control()
    while not rospy.is_shutdown():
        print(msg)
        msg.header.stamp = rospy.Time.now()
        msg.throttle = 0.0
        msg.steer = 0.0
        msg.brake = 0.0
        msg.reverse = 0
        pub_.publish(msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        dummy_pid()
    except rospy.ROSInterruptException:
        pass