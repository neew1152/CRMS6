// Initial.ino //
void InitialRef() {
  RefL2 = 1614;
  RefL1 = 2632;
  RefC = 1686;
  RefR1 = 1264;
  RefR2 = 1669;

  RefBL2 = 1592;
  RefBL1 = 978;
  RefBR1 = 1405;
  RefBR2 = 1462;
}

void InitialSpeed() {
  // MaxSpeed = BaseSpeed;
  MaxSpeed = 100;
  Ki = 0;
  KiB = 0;
  Error = 0;
  PreError = 0;

  if (BaseSpeed <= 40) {
    LeftBaseSpeed = BaseSpeed - 0;
    RightBaseSpeed = BaseSpeed - 0;
    BackLeftBaseSpeed = BaseSpeed - 0;
    BackRightBaseSpeed = BaseSpeed - 0;
    Kp = 10;  //forward PID
    Kd = 25;
    Kt = 10;
    KpB = 10;  //backward PID
    KdB = 25;
    KtB = 10;
  }

  else if (BaseSpeed <= 50) {
    LeftBaseSpeed = BaseSpeed - 0;
    RightBaseSpeed = BaseSpeed - 0;
    BackLeftBaseSpeed = BaseSpeed - 0;
    BackRightBaseSpeed = BaseSpeed - 0;
    Kp = 10;  //forward PID
    Kd = 25;
    Kt = 10;
    KpB = 10;  //backward PID
    KdB = 25;
    KtB = 10;
  }

  else if (BaseSpeed <= 60) {
    LeftBaseSpeed = BaseSpeed - 0;
    RightBaseSpeed = BaseSpeed - 0;
    BackLeftBaseSpeed = BaseSpeed - 0;
    BackRightBaseSpeed = BaseSpeed - 0;
    Kp = 13;  //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 13;  //backward PID
    KdB = 30;
    KtB = 10;
  }

  else if (BaseSpeed <= 70) {
    LeftBaseSpeed = BaseSpeed - 0;
    RightBaseSpeed = BaseSpeed - 0;
    BackLeftBaseSpeed = BaseSpeed - 0;
    BackRightBaseSpeed = BaseSpeed - 0;
    Kp = 16;  //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 16;  //backward PID
    KdB = 30;
    KtB = 10;
  }

  else if (BaseSpeed <= 80) {
    LeftBaseSpeed = BaseSpeed - 0;
    RightBaseSpeed = BaseSpeed - 0;
    BackLeftBaseSpeed = BaseSpeed - 0;
    BackRightBaseSpeed = BaseSpeed - 0;
    Kp = 19;  //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 19;  //backward PID
    KdB = 30;
    KtB = 8;
  }

  else if (BaseSpeed <= 90) {
    LeftBaseSpeed = BaseSpeed - 0;
    RightBaseSpeed = BaseSpeed - 0;
    BackLeftBaseSpeed = BaseSpeed - 0;
    BackRightBaseSpeed = BaseSpeed - 0;
    Kp = 22;  //forward PID
    Kd = 35;
    Kt = 10;
    KpB = 22;  //backward PID
    KdB = 35;
    KtB = 10;
  }

  else {
    LeftBaseSpeed = BaseSpeed - 0;
    RightBaseSpeed = BaseSpeed - 0;
    BackLeftBaseSpeed = BaseSpeed - 0;
    BackRightBaseSpeed = BaseSpeed - 0;
    Kp = 25;  //forward PID
    Kd = 50;
    Kt = 10;
    KpB = 25;  //backward PID
    KdB = 50;
    KtB = 5;
  }
}





// Analog.ino //

void Read5Analog() {
  L2 = analog(0);
  L1 = analog(1);
  C = analog(2);
  R1 = analog(3);
  R2 = analog(4);
}

void Read4BackAnalog() {
  BL2 = analog(5);
  BL1 = analog(6);
  BR1 = analog(7);
  BR2 = analog(8);
}

void Show7Analog() {
  RefL2 = L2;
  RefL1 = L1;
  RefC = C;
  RefR1 = R1;
  RefR2 = R2;
  oled.clear();
  oled.textSize(1);

  oled.text(0, 1, "Black");
  oled.show();
  waitSW_B();
  delay(100);
  Read5Analog();
  oled.text(2, 0, "L2=%d", L2);
  oled.text(3, 0, "L1=%d", L1);
  oled.text(4, 0, "C =%d", C);
  oled.text(5, 0, "R1=%d", R1);
  oled.text(6, 0, "R2=%d", R2);

  oled.text(0, 9, "White");
  oled.show();
  waitSW_B();
  delay(100);
  Read5Analog();
  oled.text(2, 8, "L2=%d", L2);
  oled.text(3, 8, "L1=%d", L1);
  oled.text(4, 8, "C =%d", C);
  oled.text(5, 8, "R1=%d", R1);
  oled.text(6, 8, "R2=%d", R2);

  oled.text(0, 17, "Avg");
  RefL2 = (RefL2 + L2) / 2;
  RefL1 = (RefL1 + L1) / 2;
  RefC = (RefC + C) / 2;
  RefR1 = (RefR1 + R1) / 2;
  RefR2 = (RefR2 + R2) / 2;
  oled.text(2, 17, "%d", RefL2);
  oled.text(3, 17, "%d", RefL1);
  oled.text(4, 17, "%d", RefC);
  oled.text(5, 17, "%d", RefR1);
  oled.text(6, 17, "%d", RefR2);
  oled.show();

  waitSW_B();
  delay(100);
  RefBL2 = BL2;
  RefBL1 = BL1;
  RefBR1 = BR1;
  RefBR2 = BR2;
  oled.clear();

  oled.text(0, 0, " Black");
  oled.show();
  waitSW_B();
  delay(100);
  Read4BackAnalog();
  oled.text(2, 0, "BL2=%d", BL2);
  oled.text(3, 0, "BL1=%d", BL1);
  oled.text(4, 0, "BR1=%d", BR1);
  oled.text(5, 0, "BR2=%d", BR2);

  oled.text(0, 9, "White");
  oled.show();
  waitSW_B();
  delay(100);
  Read4BackAnalog();
  oled.text(2, 8, "BL2=%d", BL2);
  oled.text(3, 8, "BL1=%d", BL1);
  oled.text(4, 8, "BR1=%d", BR1);
  oled.text(5, 8, "BR2=%d", BR2);

  oled.text(0, 17, "Avg");
  RefBL2 = (RefBL2 + BL2) / 2;
  RefBL1 = (RefBL1 + BL1) / 2;
  RefBR1 = (RefBR1 + BR1) / 2;
  RefBR2 = (RefBR2 + BR2) / 2;
  oled.text(2, 17, "%d", RefBL2);
  oled.text(3, 17, "%d", RefBL1);
  oled.text(4, 17, "%d", RefBR1);
  oled.text(5, 17, "%d", RefBR2);
  oled.show();

  waitSW_B();
}






// MPU6050.ino //
void InitSerial1() {
  Serial1.begin(115200);
  delay(100);
}

void zeroYaw() {
  delay(450);
  Serial1.write(0XA5);
  Serial1.write(0X54);
  delay(50);
  Serial1.write(0XA5);
  Serial1.write(0X55);
  delay(50);
  Serial1.write(0XA5);
  Serial1.write(0X52);
  delay(450);
  beep(0);
}

bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return false;
    rxCnt++;

    if (rxCnt == 8) {
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) {
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        if (pvYaw < 0) pvYaw = 360.000 + pvYaw;
        return true;
      }
    }
  }
  return false;
}

void ShowYaw() {
  while (1) {
    if (getIMU()) {
      oled.text(5, 4, "Yaw = %f  ", pvYaw);
      oled.show();
    }
  }
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





// PID.ino //
void ConvertADC() {
  Read5Analog();
  if (L2 < RefL2) L2 = 0;
  else L2 = 1;  //0:ดำ 1:ขาว
  if (L1 < RefL1) L1 = 0;
  else L1 = 1;
  if (C < RefC) C = 0;
  else C = 1;
  if (R1 < RefR1) R1 = 0;
  else R1 = 1;
  if (R2 < RefR2) R2 = 0;
  else R2 = 1;
}
void CalError() {
  ConvertADC();
  if (C == 0) Error = 100;
  else if ((L2 == 1) && (L1 == 1) && (C == 1) && (R1 == 1) && (R2 == 0)) Error = -1;
  else if ((L2 == 1) && (L1 == 1) && (C == 1) && (R1 == 0) && (R2 == 0)) Error = -2;
  else if ((L2 == 1) && (L1 == 1) && (C == 1) && (R1 == 0) && (R2 == 1)) Error = -3;
  else if ((L2 == 1) && (L1 == 1) && (C == 1) && (R1 == 1) && (R2 == 1)) Error = 0;
  else if ((L2 == 1) && (L1 == 0) && (C == 1) && (R1 == 1) && (R2 == 1)) Error = 3;
  else if ((L2 == 0) && (L1 == 0) && (C == 1) && (R1 == 1) && (R2 == 1)) Error = 2;
  else if ((L2 == 0) && (L1 == 1) && (C == 1) && (R1 == 1) && (R2 == 1)) Error = 1;
}
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

void ConvertADCBack() {
  Read4BackAnalog();
  if (BL2 < RefBL2) BL2 = 0;
  else BL2 = 1;  //0:ดำ 1:ขาว
  if (BL1 < RefBL1) BL1 = 0;
  else BL1 = 1;
  if (BR1 < RefBR1) BR1 = 0;
  else BR1 = 1;
  if (BR2 < RefBR2) BR2 = 0;
  else BR2 = 1;
}
void CalErrorBack() {
  ConvertADCBack();
  if ((BL1 == 0) && (BR1 == 0)) Error = 100;
  else if (BL1 == 0) Error = 101;
  else if (BR1 == 0) Error = 102;
  else if (BR2 == 0) Error = -1;
  else if (BL2 == 0) Error = 1;
  else Error = 0;
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





// Timer.ino //
int ReadZXSonar() {
  int Distance;
  Distance = (analog(7) / 10);
  return Distance;
}
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
