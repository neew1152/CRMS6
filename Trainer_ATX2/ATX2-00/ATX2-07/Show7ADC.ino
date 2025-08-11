void Show7ADC()
{
  Read7ADC();
  glcdClear();
  glcdFillScreen(GLCD_BLUE);
  glcdMode(3);
  setTextColor(GLCD_RED);
  setTextSize(1);
  glcd(0, 0, "L3 = %d", L3);
  glcd(1, 0, "L2 = %d", L2);
  glcd(2, 0, "L1 = %d", L1);
  glcd(3, 0, "C = %d", C);
  glcd(4, 0, "R1 = %d", R1);
  glcd(5, 0, "R2 = %d", R2);
  glcd(6, 0, "R3 = %d", R3);
}