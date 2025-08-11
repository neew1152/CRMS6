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