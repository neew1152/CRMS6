int ReadZXSonar() {
  int Distance;
  Distance = (analog(7)/10);
  return Distance;
}
void StartTimer()  {
  Timer = millis();
}
long int ReadTimer()  {
  return(millis() - Timer);
}
void StartTimer2()  {
  Timer2 = millis();
}
long int ReadTimer2()  {
  return(millis() - Timer2);
}
void StartTimer3()  {
  Timer3 = millis();
}
long int ReadTimer3()  {
  return(millis() - Timer3);
}
