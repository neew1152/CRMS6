void show7()
{
  glcdClear();
  while(1)
  {
    int A8;
    A8 = analog(12);
    glcd(1,1, " %d     ",A8);
  }
}