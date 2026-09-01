void TurnLeft()
{
  MotorStop();
  sl(TurnSpeed);
  delay(100);
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
  delay(100);
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