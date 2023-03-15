#!/usr/bin/env python
# license removed for brevity
import rospy
from sensor_msgs.msg import Joy
from std_msgs.msg import Float32
import serial
import time
com='/dev/ttyUSB0'
baud=9600
msg = Float32
class JoyControl:
    def __init__(self,port) :
        self.port=port
        # self.axis=0
        # self.forward=1
    def callback(self,data):
        axes=data.axes
        button=data.buttons
        # rospy.loginfo("gebbrish")
        # rospy.loginfo(str(axes[1]))
        if(axes[1]==1):
            print("UP")
            rospy.loginfo("UP")
            self.port.write(b'h')
            time.sleep(0.01)
        elif axes[1]==-1:
            print("DOWN")
            rospy.loginfo("DOWN")
            self.port.write(b'j')
            time.sleep(0.01)
        elif axes[1]==0:
            print("ZERO THROTTLE")
            rospy.loginfo("ZERO THROTTLE")
            self.port.write(b'q')
            self.axis=0 
        if(button[1]==1):
            print("RIGHT")
            rospy.loginfo("RIGHT")
            self.port.write(b'l')
        elif(button[3]==1):
            print("LEFT")
            rospy.loginfo("LEFT")
            self.port.write(b'r')
        if button[5]==1:
            print("FRONT BRAKES APPLIED")
            rospy.loginfo("FRONT BRAKES APPLIED")
            self.port.write(b'n')
        if button[4]==1:
            print("FRONT BRAKES REMOVED")
            rospy.loginfo("FRONT BRAKES REMOVED")
            self.port.write(b'b')
        if button[7]==1:
            print("REAR BRAKES APPLIED")
            rospy.loginfo("REAR BRAKES APPLIED")
            self.port.write(b'z')
        if button[6]==1:
            print("REAR BRAKES REMOVED")
            rospy.loginfo("REAR BRAKES REMOVED")
            self.port.write(b'Z')
        if button[9]==1:
            print("REVERSE MODE")
            self.port.write(b'c')
        if button[8]==1:
            print("FORWARD MODE")
            self.port.write(b'o')
    def vel_pub(self):
        rospy.init_node('talker', anonymous=True,log_level=rospy.DEBUG)
        rospy.Subscriber("/joy",Joy, self.callback)
        
        # if self.axis==0:
        #     self.port.write(b'q')
        
        rospy.spin()
if __name__ == '__main__':
    initialized = False
    com = rospy.get_param("/joy_com", com)
    baud = rospy.get_param("/baud", baud)
    while not initialized:
        try:
            mega = serial.Serial(com, baud)  # steer and break arduino port #changed to single arduino mega
                # uno = serial.Serial("COM5", 9600)  # throttle arduino port
            initialized = True
            print("serial up")
            rospy.loginfo("serial up")
        except:
            print("waiting for serial")
            rospy.loginfo("waiting for serial")
            time.sleep(1)
    
    joycontrol=JoyControl(mega)
    try:
        joycontrol.vel_pub()
    except rospy.ROSInterruptException:
        pass
