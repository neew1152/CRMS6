//  Analog //
void InitialRef() {
  RefL2 = 990;
  RefR2 = 880;

  RefBL2 = 1720;
  RefBR2 = 1920;
}

void ReadAnalog() {
  L2 = analog(0);
  R2 = analog(4);
  BL2 = analog(5);
  BR2 = analog(8);
}

void Show7Analog() {
  RefL2 = L2;
  RefR2 = R2;
  oled.clear();
  oled.textSize(1);

  oled.text(0, 1, "Black");
  oled.show();
  ReadAnalog();
  oled.text(2, 0, "L2=%d", L2);
  oled.text(3, 0, "R2=%d", R2);

  oled.text(0, 9, "White");
  oled.show();
  waitSW_B();
  delay(100);
  ReadAnalog();
  oled.text(2, 8, "L2=%d", L2);
  oled.text(3, 8, "R2=%d", R2);

  oled.text(0, 17, "Avg");
  RefL2 = (RefL2 + L2) / 2;
  RefR2 = (RefR2 + R2) / 2;
  oled.text(2, 17, "%d", RefL2);
  oled.text(3, 17, "%d", RefR2);
  oled.show();

  waitSW_B();
  delay(100);
  ReadAnalog();
  RefBL2 = BL2;
  RefBR2 = BR2;
  oled.text(5, 0, "BL2=%d", BL2);
  oled.text(6, 0, "BR2=%d", BR2);
  oled.show();

  waitSW_B();
  delay(100);
  ReadAnalog();
  oled.text(5, 8, "BL2=%d", BL2);
  oled.text(6, 8, "BR2=%d", BR2);

  RefBL2 = (RefBL2 + BL2) / 2;
  RefBR2 = (RefBR2 + BR2) / 2;
  oled.text(5, 17, "%d", RefBL2);
  oled.text(6, 17, "%d", RefBR2);
  oled.show();

  waitSW_B();
}

void ConvertADC() {
  // 0:ดำ 1:ขาว
  ReadAnalog();
  if (L2 < RefL2) L2 = 0;
  else L2 = 1;
  if (R2 < RefR2) R2 = 0;
  else R2 = 1;

  if (BL2 < RefBL2) BL2 = 0;
  else BL2 = 1;
  if (BR2 < RefBR2) BR2 = 0;
  else BR2 = 1;
}

int ReadZXSonar() {
  int Distance;
  Distance = (analog(7) / 10);
  return Distance;
}





// MPU6050 //
bool CalErrorGyro(int Degree) {
  if (getIMU()) {
    Error = pvYaw - Degree;
    if (Error > 180) Error = Error - 360;
    else if (Error < -180) Error = Error + 360;
    Error = Error / 5;
    return true;
  } else return false;
}

bool CalErrorGyroBack(int Degree) {
  if (getIMU()) {
    Error = Degree - pvYaw;
    if (Error > 180) Error = Error - 360;
    else if (Error < -180) Error = Error + 360;
    Error = Error / 5;
    return true;
  }
  return false;
}

void updateIMU() {
  for (int i = 0; i < 16; i++)  // วนอ่านหลายรอบเพื่อเพิ่มความแม่นยำในการรับข้อมูล
  {
    getIMU();  // อย่าลืมว่าใช้ pvYaw เมื่อไหร่ ต้องอัพเดทค่าก่อนทุกครั้ง
  }
}

void calibrate_IMU() {
  oled.clear();
  oled.text(2, 3, "Calibrating IMU");
  delay(500); zeroYaw();  // reset once at startup

  // Wait until IMU is outputting valid data
  unsigned long timer = millis();
  while (millis() - timer < 2000) {  // wait ~2s for stable data
    if (getIMU()) {      
      oled.text(4, 3, "pvYaw: %f", pvYaw);
      oled.show();
    }
  }
  
  oled.text(4, 3, "pvYaw: %l", pvYaw);
  oled.text(6, 4, "Successfully");
  oled.show(); beep(1);
}

void zeroYaw() {
  // Sets data rate to 115200 bps
  Serial1.write(0XA5); delay(50);
  Serial1.write(0X54); delay(50);
  // pitch correction roll angle
  Serial1.write(0XA5); delay(50);
  Serial1.write(0X55); delay(50);
  // zero degree heading
  Serial1.write(0XA5); delay(50);
  Serial1.write(0X52); delay(50);

  beep(1);
}

bool getIMU() {
  while (Serial1.available()) {
    uint8_t byteIn = Serial1.read();

    if (rxCnt == 0 && byteIn != 0xAA) {
      // waiting for start byte
      continue;
    }

    rxBuf[rxCnt++] = byteIn;

    if (rxCnt == 8) {  // full packet received
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) {
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        return true;
      }
    }
  }
  return false;
}

void Show_pvYaw() {
  oled.clear();
  while (1) {
    for (int i = 0; i < 8; i++) {
      getIMU();
    }

    float pvYaw_Value = normalizeYaw(pvYaw); // always in 0..360

    oled.text(4, 2, "pvYaw = %f", pvYaw_Value);
    oled.show();
  }
}

float angleError(float target, float current) {
  float error = target - current;
  if (error > 180) error -= 360;
  if (error < -180) error += 360;
  return error;  // always between -180 and +180
}


float normalizeYaw(float yaw) {
  if (yaw < 0) yaw += 360;
  else if (yaw >= 360) yaw -= 360;
  return yaw;
}





// Timer //
void StartTimer() {
  Timer = millis();
}
long int ReadTimer() {
  return (millis() - Timer);
}
void StartTimer2() {
  Timer2 = millis();
}
long int ReadTimer2() {
  return (millis() - Timer2);
}
void StartTimer3() {
  Timer3 = millis();
}
long int ReadTimer3() {
  return (millis() - Timer3);

}








