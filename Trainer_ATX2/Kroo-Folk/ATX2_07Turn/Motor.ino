void MotorStop()
{
  ao();
  delay(10);
}

void Forward(int MotorSpeed, int Time)
{
  InitialSpeed(MotorSpeed);
  fd2(LeftSpeed, RightSpeed);
  delay(Time);
}

void Backward(int MotorSpeed, int Time)
{
  InitialSpeed(MotorSpeed);
  bk2(LeftSpeed, RightSpeed);
  delay(Time);
}