void Trac(int MotorSpeed)
{
  Convert7ADC();
  if(C==0) Forward(MotorSpeed, 1);

  else if(L2==0) tl(50);
  else if(L1==0) tl(30);

  else if(R2==0) tr(50);
  else if(R1==0) tr(30);
}

void TracNormalJC(int MotorSpeed, int Time)
{
  Forward(MotorSpeed, 1);
  Convert7ADC();
  while((L2==1)||(R2==1))
  {
    Trac(MotorSpeed);
  }
  Forward(MotorSpeed, Time);
}

void TracNormalSonar(int MotorSpeed, int Distance)
{
  Forward(MotorSpeed, 1);
  while(sonar() > Distance)
  {
    Trac(MotorSpeed);
  }
}

void TracNormalTime(int MotorSpeed, int Time)
{
  ResetTimer0();
  Forward(MotorSpeed, 1);
  while(Timer0 < Time)
  {
    Trac(MotorSpeed);
    ReadTimer0();
  }
}