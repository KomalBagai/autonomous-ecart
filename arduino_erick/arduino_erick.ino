/**
 * This is the main file for e_rick drive-by-wire control node
 * auto_mode - publishes and subscribes to ros to interact with upper level Control and
  planning stack
**/

bool auto_mode = true;

//digital pins
#define R_BREAK_RPWM 4
#define R_BREAK_LPWM 5

#define STEER_RPWM 6  // handle right
#define STEER_LPWM 7  // handle left

#define F_BREAK_RPWM 8
#define F_BREAK_LPWM 9

#define RELAY 10
#define THROTTLE_TO_RICK 11  // output
//analog pins
#define THROTTLE_FEEDBACK A8  // velocity feedback

// predefined values
#define STEER_SPEED 255
#define STEER_RIGHT 0
#define STEER_LEFT 16 
#define STEER_MIDDLE 8
#define MAX_THROTTLE 255
#define MIN_THROTTLE 150  // minimum throttle value
// #define INC 4.0  // for joystick
#define INC 0.5  // for keyboard

float throttle = MIN_THROTTLE;
volatile float steer_enc_count = STEER_MIDDLE; //volatile to ensure it updates correctly in interrupt call
int pid_count, check = 0; 

#include <math.h>
#include <ros.h>
#include <EEPROM.h>
#include <alive_msgs/StampedInt64.h>
#include <alive_msgs/StampedFloat64.h>
#include <alive_msgs/Control.h>
#include <string.h>

ros::NodeHandle nh;

alive_msgs::StampedInt64 throttle_msg;
alive_msgs::StampedInt64 steer_msg;
ros::Publisher steer_pub("/steering", &steer_msg);
ros::Publisher throttle_pub("/velocity", &throttle_msg);

void pid_callback(const alive_msgs::Control& msg)
{
  pid_count++;
  // float desired_steer = msg.steer;
  // set_steer(desired_steer);
  float desired_throttle = msg.throttle;
  set_throttle(desired_throttle);
  int brake = (int)msg.brake;
  apply_brakes(brake);
  bool rev = msg.reverse;
  if (!rev){
    digitalWrite(RELAY, LOW);
    nh.loginfo("Forward mode");
  }
  else {
    digitalWrite(RELAY, HIGH);
    nh.logwarn("reverse mode");
  }
}

ros::Subscriber<alive_msgs::Control> pid_info("/pid_info_to_controller", &pid_callback);

void setup()
{
  Serial2.begin(9600);
  nh.initNode();

  pinMode(STEER_RPWM, OUTPUT);
  pinMode(STEER_LPWM, OUTPUT);
  pinMode(F_BREAK_LPWM, OUTPUT);
  pinMode(F_BREAK_RPWM, OUTPUT);
  pinMode(R_BREAK_RPWM, OUTPUT);
  pinMode(R_BREAK_LPWM, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(THROTTLE_TO_RICK, OUTPUT);
  pinMode(THROTTLE_FEEDBACK, INPUT);
  setup_steer_feedback();

  nh.advertise(steer_pub);
  nh.advertise(throttle_pub);
  nh.subscribe(pid_info);
  
  digitalWrite(RELAY, HIGH); //enables reverse in manual mode
}

void loop()
{
  // keyboard and joy_node should send commands to FTDI (serial1 of mega)
  if (Serial2.available())
  {
    // joy mode operation
    char received = (char)Serial2.read();
    steer_teleop(received);
    front_break(received);
    rear_break(received);
    throttle_teleop(received);
    reverse(received);
    exit_teleop(received);
    // homing(received);
    
  }
  if (auto_mode)
  {
    check = pid_count;
    // steering publish
    int angle = (int)steer_enc_count;
    steer_msg.header.stamp = nh.now();
    steer_msg.data = angle;
    steer_pub.publish(&steer_msg);

    // throttle publish
    int velocity = get_velocity();
    throttle_msg.header.stamp = nh.now();
    throttle_msg.data = velocity;
    throttle_pub.publish(&throttle_msg);

    nh.spinOnce();
    // exit_auto_mode();
  }
}

/**
 * Enables manual mode
 * Updates EEPROM at exit & turns relay on
**/
void exit_auto_mode()
{
  if (check != pid_count){
    digitalWrite(RELAY, HIGH); //enables reverse in manual mode
    serial_print("Entered Manual Mode \n Updated eeprom: ", (int)steer_enc_count);
    EEPROM.update(0, abs(steer_enc_count));
    nh.loginfo("Exited Auto Mode!");
  }
}
