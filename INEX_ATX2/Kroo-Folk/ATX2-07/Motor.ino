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

void Finish()
{
  ReadTimer1();
  ao();
  beep(0);
  glcdClear();
  setTextSize(2);
  glcd(0, 0, "Finish");
  glcd(1, 0, "Time = %l.%l s", Timer1/1000, Timer1%1000);
  while(1) {}
}