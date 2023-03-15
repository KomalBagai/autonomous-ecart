

// Steering Params
int out_steer = 200;
int t_steer = 100;

// Rear Break Params
int out_rBreak = 200;
int out_rBreak_l = 70; //disengage value
int t_rBreak = 600;

// Front Break Params
int out_fBreak = 250;
int t_fBreak = 100;

// steering handle reset to middle
// void homing(char rec){
// if (rec == 'H'){
//     if(steer_enc_count < STEER_MIDDLE)
//       left(STEER_RPWM, STEER_LPWM, STEER_SPEED, 10);
//     else if(steer_enc_count > STEER_MIDDLE)
//       right(STEER_RPWM, STEER_LPWM, STEER_SPEED, 10);
//     else
//       Stop(STEER_RPWM, STEER_LPWM);
//   }
// }


/**
 * Updates EEPROM at exit teleoperation
**/
void exit_teleop(char i)
{
  if (i == 'x')
  {
    digitalWrite(RELAY, HIGH); //enables reverse in manual mode
    serial_print("Entered Manual Mode \n Updated eeprom: ", (int)steer_enc_count);
    EEPROM.update(0, abs(steer_enc_count)); 
  }
}

void front_break(char i)
{
  if (i == 'b')  // press space or keypad5
  {
    Right(F_BREAK_RPWM, F_BREAK_LPWM, out_fBreak, t_fBreak);
    analogWrite(THROTTLE_TO_RICK, 0); // send throttle zero when braking
  }
  else if (i == 'n')
  {
    Left(F_BREAK_RPWM, F_BREAK_LPWM, out_fBreak, t_fBreak);  // brake
    analogWrite(THROTTLE_TO_RICK, 0); // send throttle zero when braking
  }
}

void rear_break(char i)
{
  if (i == 'z')  // press keypad period
  {
    Right(R_BREAK_RPWM, R_BREAK_LPWM, out_rBreak, t_rBreak);  // brake
    analogWrite(THROTTLE_TO_RICK, 0); // send throttle zero when braking
  }

  else if (i == 'Z')  // press keypad0 for hard brake
  {
    Left(R_BREAK_RPWM, R_BREAK_LPWM, out_rBreak_l, t_rBreak);
    analogWrite(THROTTLE_TO_RICK, 0); // send throttle zero when braking
  }
}

void steer_teleop(char i)
{
  if (i == 'r')
  {
    // if (steer_enc_count <= STEER_RIGHT)
      // Stop(STEER_RPWM, STEER_LPWM);
    // else
      Right(STEER_RPWM, STEER_LPWM, out_steer, t_steer);
  }
  else if (i == 'l')
  {
    // if (steer_enc_count >= STEER_LEFT)
      // Stop(STEER_RPWM, STEER_LPWM);
    // else
      Left(STEER_RPWM, STEER_LPWM, out_steer, t_steer);
  }
  else if (i == 's')
  {
    Stop(STEER_RPWM, STEER_LPWM);
  }

}

void throttle_teleop(char i)
{
  if (i == 'h')
  {
    throttle = throttle + INC;
  }
  else if (i == 'j')
  {
    throttle = throttle - INC;
    if (throttle <= MIN_THROTTLE - 2)
    {
      throttle = MIN_THROTTLE;
    }
  }
  else if (i == 'q')
  {
    throttle = MIN_THROTTLE;
  }
  if (throttle >= MAX_THROTTLE)
  {
    throttle = MAX_THROTTLE;
  }
  analogWrite(THROTTLE_TO_RICK, throttle);
  // serial_print("throttle: ", throttle);
  // char str[80];
  // itoa(throttle, str, 10);
  // nh.loginfo(str);
}

void reverse(char i)
{
  if (i == 'o')
  {
    digitalWrite(RELAY, HIGH);
    nh.logwarn("reverse mode");
  }

  else if (i == 'c')
  {
    digitalWrite(RELAY, LOW);
    nh.logwarn("forward mode");
  }
  // else
  //   digitalWrite(RELAY, HIGH);
}
