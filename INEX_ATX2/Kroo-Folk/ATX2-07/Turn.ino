void TurnLeft()
{
  MotorStop();
  sl(TurnSpeed);
  delay(250);
  Convert7ADC();
  while(L2 == 1)
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
  while(R2 == 1)
  {
    Convert7ADC();
  }
}
//T8R(250)
void T8R(int a)
{
  Convert7ADC();
  sr(TurnSpeed);
  delay(a);
  sr(60);
  while(analog(7) > RefR2){}
  while(analog(7) < RefR2){}
  ao();
}

//T8L(250)
void T8L(int a)
{
  Convert7ADC();
  sl(TurnSpeed);
  delay(a);
  sl(60);
  while(analog(3) > RefL2){}
  while(analog(3) < RefL2){}
  ao();
}

void UTurn()
{
  MotorStop();
  sl(TurnSpeed);
  delay(300);
  Convert7ADC();
  while(L2 == 1)
  {
    Convert7ADC();
  }
}