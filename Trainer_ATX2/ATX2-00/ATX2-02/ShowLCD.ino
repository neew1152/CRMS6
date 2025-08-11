void ShowLCD()
{
  glcdClear();
  glcdFillScreen(GLCD_BLUE);
  glcdMode(3);
  setTextColor(GLCD_RED);
  setTextSize(3);
  glcd(0,2,"ATX2+");
  setTextColor(GLCD_YELLOW);
  glcd(3,0,"Arduino");
}