void no_stop_right(int RPWM, int LPWM, int out) //motor right, steering left
{
  analogWrite(RPWM, out);
  analogWrite(LPWM, 0);
}

void no_stop_left(int RPWM, int LPWM, int out) //motor left steering right
{
  analogWrite(RPWM, 0);
  analogWrite(LPWM, out);
}

void Stop(int RPWM, int LPWM)
{
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  delay(10);
}

void Right(int RPWM, int LPWM, int out, int t) //motor right, steering left
{
  analogWrite(RPWM, out);
  analogWrite(LPWM, 0);
  delay(t);
  Stop(RPWM, LPWM);
}

void Left(int RPWM, int LPWM, int out, int t) //motor left steering right
{
  analogWrite(RPWM, 0);
  analogWrite(LPWM, out);
  delay(t);
  Stop(RPWM, LPWM);
}

