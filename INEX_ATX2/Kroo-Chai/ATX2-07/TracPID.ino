void TracPID()
{
  int Output, LeftOutput, RightOutput, KpTemp;

  if(abs(Error) <= 3) KpTemp = 1;
  else KpTemp = Kp;
  
  Output = (KpTemp * Error) + (Ki * Integral) + Kd * (Error - PreError);
  LeftOutput = LeftSpeed + Output;
  RightOutput = RightSpeed - Output;

  if(LeftOutput > MaxSpeed) LeftOutput = MaxSpeed;
  if(RightOutput > MaxSpeed) RightOutput = MaxSpeed;
  if(LeftOutput < 0) LeftOutput = 0;
  if(RightOutput < 0) RightOutput < 0;

  fd2(LeftOutput, RightOutput);
  PreError = Error;
  Integral += Error;
}

void TracJC(int MotorSpeed, int Time)
{
  InitialSpeed(MotorSpeed);
  CalError();
  while(Error < 100)
  {
    TracPID();
    CalError();
  }
  Forward(MotorSpeed, Time);
}

void TracSonar(int MotorSpeed, int Distance)
{
  InitialSpeed(MotorSpeed);
  while(sonar() > Distance)
  {
    CalError();
    TracPID();
  }
}

void TracTime(int MotorSpeed, int Time)
{
  ResetTimer0();
  InitialSpeed(MotorSpeed);
  while(Timer0 < Time)
  {
    CalError();
    TracPID();
    ReadTimer0();
  }
}