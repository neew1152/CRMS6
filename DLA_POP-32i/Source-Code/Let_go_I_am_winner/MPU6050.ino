void updateIMU() {
  for (int i = 0; i < 8; i++)  // วนอ่านหลายรอบเพื่อเพิ่มความแม่นยำในการรับข้อมูล
  {
    getIMU();  // อย่าลืมว่าใช้ pvYaw เมื่อไหร่ ต้องอัพเดทค่าก่อนทุกครั้ง
  }
}
void updateIMU_Special() {
  for (int i = 0; i < 16; i++)  // วนอ่านหลายรอบเพื่อเพิ่มความแม่นยำในการรับข้อมูล
  {
    getIMU();  // อย่าลืมว่าใช้ pvYaw เมื่อไหร่ ต้องอัพเดทค่าก่อนทุกครั้ง
  }
}
void zeroYaw() {
  Serial1.begin(115200);
  delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5);
  delay(100);
  Serial1.write(0X54);
  delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5);
  delay(100);
  Serial1.write(0X55);
  delay(100);
  // zero degree heading
  Serial1.write(0XA5);
  delay(100);
  Serial1.write(0X52);
  delay(100);
  // automatic mode
}
bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return;
    rxCnt++;
    if (rxCnt == 8) {  // package is complete
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) {  // data package is correct
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        return true;
      }
    }
  }
  return false;
}
void Auto_zero() {
  int bornpvYaw;
  zeroYaw();
  getIMU();
  int timer = millis();
  oled.clear();
  oled.text(1, 2, "Setting zero");
  while (abs(pvYaw) > 0.05) {  //วนทำซ้ำจนกว่าองศาจะน้อยกว่า 0.05
    if (getIMU()) {
      oled.text(3, 6, "Yaw: %f  ", pvYaw);
      oled.show();
      //beep();
      if (millis() - timer > 5000) {  //เวลาเกิน 5 วิให้ zeroYaw อีกครั้ง
        zeroYaw();
        timer = millis();
      }
    }
  }
  oled.clear();
  oled.text(3, 2, "bornpvYaw %l ", pvYaw);
  oled.show();
  delay(2000);
}
void ReadMPU() {
  oled.clear();
  while(1) {
    float Value = 0;
    for (int i = 0; i < 8; i++) {
      getIMU();
    }
    Value = pvYaw;
    //if (Value < 0) Value += 360;
    oled.text(2,2,"Value = %f",Value);
    oled.show();
  }
}