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





void TurnLeft()
{
  MotorStop();
  sl(TurnSpeed);
  delay(225);
  Convert7ADC();
  while(L1 == 1)
  {
    Convert7ADC();
  }
}

void TurnRight()
{
  MotorStop();
  sr(TurnSpeed);
  delay(250);
  Convert7ADC();
  while(R1 == 1)
  {
    Convert7ADC();
  }
}

void T8R(int a)
{
  Convert7ADC();
  sr(TurnSpeed);
  delay(a);
  sr(60);
  while(analog(8) > RefR2){}
  while(analog(8) < RefR2){}
  ao();
}


void T8L(int a)
{
  Convert7ADC();
  sl(TurnSpeed);
  delay(a);
  sl(60);
  while(analog(2) > RefL2){}
  while(analog(2) < RefL2){}
  ao();
}

void UTurn()
{
  MotorStop();
  sl(TurnSpeed);
  delay(300);
  Convert7ADC();
  while(C == 1)
  {
    Convert7ADC();
  }
}





void InitialSpeed(int MotorSpeed)
{
  Error = 0;
  PreError = 0;
  Integral = 0;
  Ki = 0;
  MaxSpeed = MotorSpeed;
  if(MotorSpeed <= 50)
  {
    Kp = 10;
    Kd = 20;
    LeftSpeed = MotorSpeed - 0.02;
    RightSpeed = MotorSpeed;
  }

  else if (MotorSpeed <= 60){
    Kp = 13;
    Kd = 25;
    LeftSpeed = MotorSpeed - 0.005;
    RightSpeed = MotorSpeed - 0;
  }

  else if(MotorSpeed <= 70)
  {
    Kp = 15;
    Kd = 30;
    LeftSpeed = MotorSpeed;
    RightSpeed = MotorSpeed;
  }
  else if(MotorSpeed <= 100)
  {
    Kp = 20;
    Kd = 60;
    LeftSpeed = MotorSpeed;
    RightSpeed = MotorSpeed;
  }
}