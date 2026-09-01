void ResetTimer0()
{
  StartTimer0 = millis();
  Timer0 = 0;
}

void ReadTimer0()
{
  Timer0 = millis() - StartTimer0;
}

void ResetTimer1()
{
  StartTimer0 = millis();
  Timer1 = 0;
}

void ReadTimer1()
{
  Timer1 = millis() - StartTimer0;
}