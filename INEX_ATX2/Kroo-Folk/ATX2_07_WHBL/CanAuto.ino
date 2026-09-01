void canauto1()
{
  ao();
  delay(1000);
  SonarBlock = analog(12);
  glcd(1,1, " %d     ", SonarBlock);
  if(SonarBlock < 550)
  {
    TracSonar(60, 200);
  }
  else
  {
    ao();
    delay(200);
  }
}