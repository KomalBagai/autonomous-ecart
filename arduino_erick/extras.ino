//map() for float values
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//To see print messages open FTDI Port (Hint: /dev/ttyUSB1)
void serial_print(const char* message, double value)
{
  Serial2.print(message);
  Serial2.println(value);
}