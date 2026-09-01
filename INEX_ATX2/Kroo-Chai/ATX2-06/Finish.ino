void Finish()
{
  ReadTimer1();
  ao();
  beep(0);
  glcdClear();
  setTextSize(2);
  glcd(0, 0, "Fonish");
  glcd(1, 0, "Time = %l.%l s", Timer1/1000, Timer1%1000);
  while(1) {}
}