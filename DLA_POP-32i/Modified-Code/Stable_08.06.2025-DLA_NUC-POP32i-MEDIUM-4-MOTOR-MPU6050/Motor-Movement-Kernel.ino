void MotorStop() {
  AO();
  delay(MotorStop_Delay);
}

void ForwardSpeed(int MotorSpeed) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  FD2(LeftBaseSpeed, RightBaseSpeed);
  BaseSpeed = Speed;
  InitialSpeed();
}

void ForwardSpeedTime(int MotorSpeed, int Time) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  FD2(LeftBaseSpeed, RightBaseSpeed);
  delay(Time);
  BaseSpeed = Speed;
  InitialSpeed();
  MotorStop();
}

void BackwardSpeed(int MotorSpeed) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  BK2(BackLeftBaseSpeed, BackRightBaseSpeed);
  BaseSpeed = Speed;
  InitialSpeed();
}

void BackwardSpeedTime(int MotorSpeed, int Time) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  BK2(BackLeftBaseSpeed, BackRightBaseSpeed);
  delay(Time);
  BaseSpeed = Speed;
  InitialSpeed();
  MotorStop();
}

void Move_Left(int Speed, int Time, char select) {
  MotorStop();
  if (select == 'S') {
    SL(Speed);
    delay(Time);
  }

  else if (select == 'T') {
    TL(Speed);
    delay(Time);
  }
  MotorStop();
}

void Move_Right(int Speed, int Time, char select) {
  MotorStop();
  if (select == 'S') {
    SR(Speed);
    delay(Time);
  }

  else if (select == 'T') {
    TR(Speed);
    delay(Time);
  }
  MotorStop();
}

void TracJCStop()  // เดินถึงเส้นและออกจากฟังก์ชัน
{
  ForwardSpeedTime(BaseSpeed, 100);
  InitialSpeed();
  CalError();
  while (Error < 99) {
    TracPID();
    StartTimer();
    while ((ReadTimer() < Kt) && (Error < 100)) {
      CalError();
    }
  }
}

void TracJC()  // เดินถึงเส้นที่ไม่ใช่ขอบและถอยแบบจูน
{
  TracJCBlack();
  MotorStop();
  //delay(100);
  BackwardBalanceF();
  BackwardSpeedTime(SlowSpeed, 120);
}

void TracJCBlack()  // วิ่งเข้าหลุมดำหรือพื้นที่วางสีเขียว
{
  TracJCStop();
  ForwardSpeedTime(SlowSpeed, 1);
  ConvertADC();
  while ((L2 == 1) && (R2 == 1)) { ConvertADC(); }
  MotorStop();
  if ((L2 == 0) && (R2 == 1))  //เจอดำข้างซ้าย
  {
    SL(SlowSpeed);
    while (R2 == 1) { ConvertADC(); }
    delay(10);
  } else if ((L2 == 1) && (R2 == 0))  //เจอดำข้างขวา
  {
    SR(SlowSpeed);
    while (L2 == 1) { ConvertADC(); }
    delay(10);
  }
  MotorStop();
}

void TracJCForward()  // เดินถึงขอบสะพานบนและถอยเดินตรง
{
  TracJCStop();
  ForwardSpeedTime(Speed, 300);
}

void TracJCSlowStop() {
  BaseSpeed = SlowSpeed;
  TracJCStop();
  BaseSpeed = Speed;
  InitialSpeed();
}

void TracJCSpeedTime(int MotorSpeed, int TimeDelay) {
  BaseSpeed = MotorSpeed;
  TracJCStop();
  FD2(LeftBaseSpeed, RightBaseSpeed);
  delay(TimeDelay);
  BaseSpeed = Speed;
  InitialSpeed();
}

void TracJCDegree(int MotorSpeed, int Degree, int Time, int PIDtemp) {
  int TempSpeed = BaseSpeed;
  int TempPidStatus = PidStatus;

  PidStatus = PIDtemp;
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyro(Degree);
  ConvertADC();
  while (C == 1) {
    TracPID();
    StartTimer3();
    while ((ReadTimer3() < Kt)) {
      CalErrorGyro(Degree);
    }
    ConvertADC();
  }
  MotorStop();
  TracDegreeSpeedTimeBack(MotorSpeed, Time);
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus = TempPidStatus;
}

void TracJCDegreeBack(int MotorSpeed, int Degree, int Time, int PIDtemp) {
  int TempSpeed = BaseSpeed;
  int TempPidStatus = PidStatus;

  PidStatus = PIDtemp;
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyroBack(Degree);
  ConvertADCBack();
  while ((BL1 == 1) && (BR1 == 1)) {
    TracPIDBack();
    StartTimer3();
    while ((ReadTimer3() < Kt)) {
      CalErrorGyroBack(Degree);
    }
    ConvertADCBack();
  }
  MotorStop();
  TracDegreeSpeedTime(MotorSpeed, Time);
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus = TempPidStatus;
}

void SpinDegree(int MotorSpeed, int Degree, int PIDtemp) {
  int TempSpeed = BaseSpeed;
  int TempPidStatus = PidStatus;
  int Status = 0;

  MotorStop();
  PidStatus = PIDtemp;
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyro(Degree);
  while (Status == 0) {
    TracPID();
    StartTimer3();
    while ((ReadTimer3() < Kt) && (Status == 0)) {
      if (CalErrorGyro(Degree)) {
        if (abs(Error) <= 3) Status = 1;
      }
    }
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus = TempPidStatus;
  MotorStop();
}

void SpinDegreeBack(int MotorSpeed, int Degree, int PIDtemp) {
  int TempSpeed = BaseSpeed;
  int TempPidStatus = PidStatus;
  int Status = 0;

  MotorStop();
  PidStatus = PIDtemp;
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyroBack(Degree);
  while (Status == 0) {
    TracPIDBack();
    StartTimer3();
    while ((ReadTimer3() < Kt) && (Status == 0)) {
      if (CalErrorGyroBack(Degree)) {
        if (abs(Error) <= 3) Status = 1;
      }
    }
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus = TempPidStatus;
  MotorStop();
}

void CurveDegree(int TurnSpeed, float Degree, char select, int Origin)  //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้น
{
  int Status = 0;
  if (Origin != 1) zeroYaw();

  if (select == 'L') {
    if (WheelDrive == 0) tl(TurnSpeed);
    else TL(TurnSpeed);
    for (int i = 0; i < 10; i++) {
      getIMU();
    }
    while (Status == 0) {
      if (getIMU()) {
        if ((pvYaw >= Degree - 25) && (pvYaw <= Degree - 0)) {
          Status = 1;
        } else if (Degree == 0) {
          if ((pvYaw >= 345) && (pvYaw <= 360)) {
            Status = 1;
          }
        }
      }
    }
  }

  else if (select == 'R') {
    if (WheelDrive == 0) tr(TurnSpeed);
    else TR(TurnSpeed);
    for (int i = 0; i < 10; i++) {
      getIMU();
    }
    while (Status == 0) {
      if (getIMU()) {
        if (Origin == 2) {
          if (Degree == 0) break;
          if ((360 - pvYaw >= Degree - 25) && (360 - pvYaw <= Degree - 0)) {
            Status = 1;
          }
        } else if ((pvYaw <= Degree + 25) && (pvYaw >= Degree)) {
          Status = 1;
        } else if (Degree >= 330) {
          if ((pvYaw <= Degree - 335) || (pvYaw >= 335)) Status = 1;
        }
      }
    }
  }
}

void CurveDegreeBack(int TurnSpeed, float Degree, char select, int Origin)  //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้น
{
  int Status = 0;
  if (Origin != 1) zeroYaw();

  if (select == 'L') {
    if (WheelDrive == 0) {
      motor(1, -TurnSpeed);
      motor(2, 0);
    } else {
      motor(1, -TurnSpeed);
      motor(2, -TurnSpeed);
      motor(3, 0);
      motor(4, 0);
    }
    for (int i = 0; i < 10; i++) {
      getIMU();
    }
    while (Status == 0) {
      if (getIMU()) {
        if ((pvYaw >= Degree - 25) && (pvYaw <= Degree - 0)) {
          Status = 1;
        } else if (Degree == 0) {
          if ((pvYaw >= 345) && (pvYaw <= 360)) {
            Status = 1;
          }
        }
      }
    }
  }

  else if (select == 'R') {
    if (WheelDrive == 0) {
      motor(1, 0);
      motor(2, -TurnSpeed);
    } else {
      motor(1, 0);
      motor(2, 0);
      motor(3, -TurnSpeed);
      motor(4, -TurnSpeed);
    }
    for (int i = 0; i < 10; i++) {
      getIMU();
    }
    while (Status == 0) {
      if (getIMU()) {
        if (Origin == 2) {
          if (Degree == 0) break;
          if ((360 - pvYaw >= Degree - 25) && (360 - pvYaw <= Degree - 0)) {
            Status = 1;
          }
        } else if ((pvYaw <= Degree + 25) && (pvYaw >= Degree)) {
          Status = 1;
        } else if (Degree >= 330) {
          if ((pvYaw <= Degree - 335) || (pvYaw >= 335)) Status = 1;
        }
      }
    }
  }
}