void TurnLeft()
{
  MotorStop();
  sl(TurnSpeed);
  delay(275);
  Convert7ADC();
  while(L2 == 1)
  {
    Convert7ADC();
  }
}

void HalfTurnLeft()
{
  MotorStop();
  sl(TurnSpeed);
  delay(125);
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
  delay(275);
  Convert7ADC();
  while(R2 == 1)
  {
    Convert7ADC();
  }
}

void HalfTurnRight()
{
  MotorStop();
  sr(TurnSpeed);
  delay(125);
  Convert7ADC();
  while(R2 == 1)
  {
    Convert7ADC();
  }
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