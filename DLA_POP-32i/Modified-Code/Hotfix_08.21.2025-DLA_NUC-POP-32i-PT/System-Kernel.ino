#define min 2000
#define max 0

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





// PID //
void TracPID() {
  int Output, LeftOutput, RightOutput;
  Output = (Kp * Error) + (Ki * SumError) + (Kd * (Error - PreError));
  LeftOutput = LeftBaseSpeed + Output;
  RightOutput = RightBaseSpeed - Output;
  if (PidStatus != 0) {
    LeftOutput = constrain(LeftOutput, -MaxSpeed, MaxSpeed);
    RightOutput = constrain(RightOutput, -MaxSpeed, MaxSpeed);
  } else {
    LeftOutput = constrain(LeftOutput, 0, MaxSpeed);
    RightOutput = constrain(RightOutput, 0, MaxSpeed);
  }
  motor(1, LeftOutput);
  motor(2, LeftOutput);
  motor(3, RightOutput);
  motor(4, RightOutput);
  PreError = Error;
  SumError += Error;
}

void TracPIDBack() {
  int Output, LeftOutput, RightOutput;
  Output = (KpB * Error) + (KiB * SumError) + (KdB * (Error - PreError));
  LeftOutput = BackLeftBaseSpeed + Output;
  RightOutput = BackRightBaseSpeed - Output;
  if (PidStatus != 0) {
    LeftOutput = constrain(LeftOutput, -MaxSpeed, MaxSpeed);
    RightOutput = constrain(RightOutput, -MaxSpeed, MaxSpeed);
  } else {
    LeftOutput = constrain(LeftOutput, 0, MaxSpeed);
    RightOutput = constrain(RightOutput, 0, MaxSpeed);
  }
  motor(1, -LeftOutput);
  motor(2, -LeftOutput);
  motor(3, -RightOutput);
  motor(4, -RightOutput);
  PreError = Error;
  SumError += Error;
}





// MPU6050 //
void InitSerial1() {
  Serial1.begin(115200);
  delay(100);
}

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
  for (int i = 0; i < 8; i++)  // วนอ่านหลายรอบเพื่อเพิ่มความแม่นยำในการรับข้อมูล
  {
    getIMU();  // อย่าลืมว่าใช้ pvYaw เมื่อไหร่ ต้องอัพเดทค่าก่อนทุกครั้ง
  }
}

void calibrate_IMU() {
  int bornpvYaw;
  zeroYaw();
  getIMU();
  int timer = millis();
  oled.clear();
  oled.text(1, 2, "Calibrating IMU");
  while (abs(pvYaw) > 0.05) {  // วนทำซ้ำจนกว่าองศาจะน้อยกว่า 0.05
    if (getIMU()) {
      oled.text(3, 6, "Yaw: %f  ", pvYaw);
      oled.show();
      if (millis() - timer > 5000) {  // เวลาเกิน 5 วิให้ zeroYaw อีกครั้ง
        zeroYaw();
        timer = millis();
      }
    }
  }
  oled.clear();
  oled.text(3, 2, "bornpvYaw %l", pvYaw);
  oled.text(6, 4, "Successfully");
  oled.show();
  beep(1);
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

void ReadMPU() {
  oled.clear();
  while (1) {
    float Value = 0;
    for (int i = 0; i < 8; i++) {
      getIMU();
    }
    Value = pvYaw;
    if (Value < 0) {
      oled.text(2, 2, "Value = %f", Value += 360);
    }
    oled.show();
  }
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