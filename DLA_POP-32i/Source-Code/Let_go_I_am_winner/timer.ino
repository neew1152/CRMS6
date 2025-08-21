void StartTimer()
{
  Timer = millis();
}
long int ReadTimer()  {
  return(millis() - Timer);
}