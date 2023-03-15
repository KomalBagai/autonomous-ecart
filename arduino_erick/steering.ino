/**
 * This file contains interrupts reading steering feedback from encoders and 
  lower level steering controller
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
**/

#define counter_inc 0.01
#define INTERRUPT_PIN1 18
#define INTERRUPT_PIN2 19


int int_steer()
{
  return (int)steer_enc_count;
}

void setup_steer_feedback()
{
  pinMode(INTERRUPT_PIN1, INPUT_PULLUP);  // internal pullup input pin 18
  pinMode(INTERRUPT_PIN2, INPUT_PULLUP);  // internal pullup input pin 19
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN1), ai0, RISING);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN2), ai1, RISING);
  int eep = EEPROM.read(0);
  if (eep != STEER_MIDDLE)
  {
    steer_enc_count = eep;
    serial_print("update from eeprom", eep); 
  }
}

// ISR (interrupt service routine) for steering feedback, must be as short as possible
void ai0()
{
  if (digitalRead(INTERRUPT_PIN2) == LOW)
    steer_enc_count += counter_inc;
  else
    steer_enc_count -= counter_inc;
}
void ai1()
{
  if (digitalRead(INTERRUPT_PIN1) == LOW)
    steer_enc_count -= counter_inc;
  else
    steer_enc_count += counter_inc;
  }


void set_steer(float desired)
{
  int des_map = (int)mapfloat(desired, -1, 1, STEER_RIGHT, STEER_LEFT);
  int current = int_steer();
  serial_print("desired_steer ", desired);
  serial_print("current ", current);
  serial_print("des_map ", des_map);
  if (current < des_map)
  {
    // serial_print("left ", des_map);
    no_stop_left(STEER_RPWM, STEER_LPWM, STEER_SPEED);
  }
  else if (current > des_map)
  {
    // serial_print("right ", des_map);
    no_stop_right(STEER_RPWM, STEER_LPWM, STEER_SPEED);
  }
  else 
  {
    serial_print("stop", 0);
    Stop(STEER_RPWM, STEER_LPWM);
    // delay(50);
  }
}

