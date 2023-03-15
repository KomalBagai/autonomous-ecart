/**
 * Throttle Lower Level Controller
 * TODO: Test code and Tune on road
 **/

#define kp 0.55
#define ki 0.2
#define kd 1
#define kn 0.18
#define deltaT 0.1

float prev_error = 0;
float eint = 0;

void print_velocity_feedback()
{
  int throttle_read = analogRead(THROTTLE_FEEDBACK);
  // serial_print("Feedback: ", throttle_read);
}

int get_velocity()
{
  int throttle_read = analogRead(THROTTLE_FEEDBACK);
  int velocity = (int)map(throttle_read, 0, 250, 0, 50);  //speedometer voltage range = [9.6mV - 1.15V] ~ 1.5 to 250 bits
  return velocity;
}

float throttle_pid_control(int desVel)
{
  int currVel = get_velocity();
  float e = desVel - currVel;
  eint = eint + e * deltaT;
  
  // Compute the control signal u
  float u = kp * e + ki * eint + kd * (e - prev_error);
  prev_error = e;

  throttle += (kn * u); // kn:to increase u's impact
  if (throttle < MIN_THROTTLE)
  {
    throttle = MIN_THROTTLE;
  }
  if (throttle > MAX_THROTTLE)
  {
    throttle = MAX_THROTTLE;
  }
  return throttle;
}

void set_throttle(float desired)
{
  // float desired_pwm = throttle_pid_control(desired);
  int desired_pwm = (int)mapfloat(desired, 0, 1, MIN_THROTTLE, MAX_THROTTLE);
  // serial_print("desired", desired);
  // serial_print("desired_pwm", desired_pwm);
  analogWrite(THROTTLE_TO_RICK, desired_pwm);
}
