void Calibartion() {
  oled.clear();
  //Read4Analog();
  while (1) {
    Read4Analog();
    oled.text(2, 0, "L2=%d", L2);
    oled.text(3, 0, "L1=%d", L1);
    oled.text(4, 0, "R1=%d", R1);
    oled.text(5, 0, "R2=%d", R2);
    delay(10);
    oled.show();
    maxL2 = L2;
    maxL1 = L1;
    maxR1 = R1;
    maxR2 = R2;
    Read4Analog();
    oled.text(2, 0, "L2=%d", L2);
    oled.text(3, 0, "L1=%d", L1);
    oled.text(4, 0, "R1=%d", R1);
    oled.text(5, 0, "R2=%d", R2);
    delay(10);
    oled.show();
    if (L2 > maxL2) minL2 = maxL2;
    maxL2 = L2;
    if (L1 < maxL1) minL1 = L1;
    maxL1 = maxL1;
    if (R1 > maxR1) minR1 = maxR1;
    maxR1 = R1;
    if (R2 > maxR2) minR2 = maxR2;
    maxR1 = R2;
    //delay(50);
    //delay(50);
    if (SW_A()) break;
  }
  beep(500);
  oled.clear();
  oled.text(0, 2, "max");
  oled.text(2, 0, "maxL2=%d", maxL2);
  oled.text(3, 0, "maxL1=%d", maxL1);
  oled.text(4, 0, "maxR1=%d", maxR1);
  oled.text(5, 0, "maxR2=%d", maxR2);
  beep(500);
  oled.text(0, 13, "min");
  oled.text(2, 11, "minL2=%d", minL2);
  oled.text(3, 11, "minL1=%d", minL1);
  oled.text(4, 11, "minR1=%d", minR1);
  oled.text(5, 11, "minR2=%d", minR2);
  oled.show();
}
long result = 0;
void CalibartionRGB() {
  MotorStop();
  oled.clear();
  for (int i = 0; i <= 5; i++) {
    long RGBColor = ReadRGB();
    oled.text(i, 0, "RGB=%l", RGBColor);
    result = result + RGBColor;
  }
  oled.text(6,0," result = %l",result/6);
  oled.show();
  result =result/6;
  CheckRGB();
}