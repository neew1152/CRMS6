// ฟังก์ชันสแกนหาค่ากลางของเซ็นเซอร์โดยใช้เวลา 5 วินาที
void Slide_Calibration() {
  int min_L0 = 4095, max_L0 = 0;
  int min_L1 = 4095, max_L1 = 0;
  int min_R2 = 4095, max_R2 = 0;
  int min_R3 = 4095, max_R3 = 0;
  unsigned long timerStart;

  glcdClear();
  glcd(0, 0, "Slide Calibration");

  // วนลูปอ่านค่าเซ็นเซอร์ 5 วินาที เพื่อเก็บค่าต่ำสุด(Min) และสูงสุด(Max)
  timerStart = millis();
  while (millis() - timerStart < 5000) {
    int val_L0 = analog(0);
    int val_L1 = analog(1);
    int val_R2 = analog(2);
    int val_R3 = analog(3);

    if (val_L0 > max_L0) max_L0 = val_L0;
    if (val_L0 < min_L0) min_L0 = val_L0;

    if (val_L1 > max_L1) max_L1 = val_L1;
    if (val_L1 < min_L1) min_L1 = val_L1;

    if (val_R2 > max_R2) max_R2 = val_R2;
    if (val_R2 < min_R2) min_R2 = val_R2;

    if (val_R3 > max_R3) max_R3 = val_R3;
    if (val_R3 < min_R3) min_R3 = val_R3;

    glcd(1, 0, "SCANNING... %d Sec", 5 - (millis() - timerStart) / 1000);
    delay(5);
  }

  // นำค่า Min-Max มาเฉลี่ยเพื่อหาค่ากึ่งกลาง (Ref) ไว้ใช้ใน Main.ino
  Ref_L0 = (min_L0 + max_L0) / 2;
  Ref_L1 = (min_L1 + max_L1) / 2;
  Ref_R2 = (min_R2 + max_R2) / 2;
  Ref_R3 = (min_R3 + max_R3) / 2;

  // แสดงผลค่า Ref และ Min-Max บนหน้าจอ
  beep();
  glcdClear();
  glcd(0, 0, "Ref Values:");
  glcd(1, 0, "L0:%d L1:%d", Ref_L0, Ref_L1);
  glcd(2, 0, "R2:%d R3:%d", Ref_R2, Ref_R3);

  glcd(4, 0, "Min .. Max");
  glcd(5, 0, "L0: %d..%d", min_L0, max_L0);
  glcd(6, 0, "L1: %d..%d", min_L1, max_L1);
  glcd(7, 0, "R2: %d..%d", min_R2, max_R2);
  glcd(8, 0, "R3: %d..%d", min_R3, max_R3);
}

// ฟังก์ชันทดสอบเซอร์โวมอเตอร์ สั่งให้หมุนตามปุ่ม Knob ของบอร์ด
void test_servo() {
  while (1) {
    glcd(1, 0, "Knob= %d ", knob(0, 180));
    servo(1, knob(0, 180));
  }
}