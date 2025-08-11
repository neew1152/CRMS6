  // 0:เคลียร์มุมเริ่มต้น, 1:ไม่เคลียร์มุมเริ่มต้น, 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการเหมือน 0
  // TurnLeftDegree(100, 90, 1);
  // TurnRightDegree(100, 90, 2);

  // 0:ไม่หมุนกลับทิศ, 1:หมุนกลับทิศ
  // TracDegreeSpeedTime(60, 0, 1000, 0);

void TracDegreeSpeedTime_Native(int MotorSpeed, int Degree, int Time, int PIDtemp) {
  MotorStop();
  int TempSpeed = BaseSpeed;
  int TempPidStatus = PidStatus;

  PidStatus = PIDtemp;
  StartTimer();
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyro(Degree);
  while (ReadTimer() < Time) {
    TracPID();
    StartTimer3();
    while ((ReadTimer3() < Kt)) {
      CalErrorGyro(Degree);
    }
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus = TempPidStatus;
}

void TracDegreeSpeedTimeBack_Native(int MotorSpeed, int Degree, int Time, int PIDtemp) {
  int TempSpeed = BaseSpeed;
  int TempPidStatus = PidStatus;

  PidStatus = PIDtemp;
  StartTimer();
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyroBack(Degree);
  while (ReadTimer() < Time) {
    TracPIDBack();
    StartTimer3();
    while ((ReadTimer3() < Kt)) {
      CalErrorGyroBack(Degree);
    }
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus = TempPidStatus;
}

void TurnLeftDegree_Native(int TurnSpeed, float Degree, int Origin) {
  int Status = 0;
  MotorStop();
  if (WheelDrive == 0) sl(TurnSpeed);
  else SL(TurnSpeed);
  for (int i = 0; i < 10; i++) {
    getIMU();
  }
  while (Status == 0) {
    if (getIMU()) {
      if ((pvYaw >= Degree - 30) && (pvYaw <= Degree - 0)) {
        Status = 1;
      } else if (Degree == 0) {
        if ((pvYaw >= 345) && (pvYaw <= 360)) {
          Status = 1;
        }
      }
    }
  }
  Status = 0;
  if (WheelDrive == 0) sl(20);
  else SL(20);
  while (Status == 0) {
    if (getIMU()) {
      if ((pvYaw >= Degree - 5) && (pvYaw <= Degree + 5)) {
        Status = 1;
      } else if (Degree == 0) {
        if ((pvYaw >= 355) || (pvYaw <= 5)) {
          Status = 1;
        }
      }
    }
  }
  if (WheelDrive == 0) sr(BrakeSpeedIMU);
  else SR(BrakeSpeedIMU);
  delay(BrakeTimeIMU);
  MotorStop();
  if (Origin != 1)
  {
    zeroYaw();
  }
}

void TurnRightDegree_Native(int TurnSpeed, float Degree, int Origin) { 
  int Status = 0;
  MotorStop();
  if (Origin != 1) zeroYaw();
  if (WheelDrive == 0) sr(TurnSpeed);
  else SR(TurnSpeed);
  for (int i = 0; i < 10; i++) {
    getIMU();
  }
  while (Status == 0) {
    if (getIMU()) {
      if (Origin == 2) {
        if (Degree == 0) break;
        if ((360 - pvYaw >= Degree - 30) && (360 - pvYaw <= Degree - 0)) {
          Status = 1;
        }
      } else if ((pvYaw <= Degree + 30) && (pvYaw >= Degree)) {
        Status = 1;
      } else if (Degree >= 330) {
        if ((pvYaw <= Degree - 330) || (pvYaw >= 330)) Status = 1;
      }
    }
  }
  Status = 0;
  if (WheelDrive == 0) sr(20);
  else SR(20);
  while (Status == 0) {
    if (getIMU()) {
      if (Origin == 2) {
        if (Degree == 0) break;
        if ((360 - pvYaw >= Degree - 5) && (360 - pvYaw <= Degree + 5)) {
          Status = 1;
        } else if (Degree >= 355) {
          if ((360 - pvYaw >= 355) || (360 - pvYaw <= 5)) {
            Status = 1;
          }
        }
      } else if ((pvYaw <= Degree + 5) && (pvYaw >= Degree - 5)) {
        Status = 1;
      } else if (Degree >= 355) {
        if ((pvYaw <= Degree - 355) || (pvYaw >= Degree - 5)) Status = 1;
      }
    }
  }
  if (WheelDrive == 0) sl(BrakeSpeedIMU);
  else SL(BrakeSpeedIMU);
  delay(BrakeTimeIMU);
  MotorStop();
}

void BackwardBalance_Native(int speed, int reverse_delay) {
  int Status = 0;
  delay(100);
  BackwardSpeedTime(SlowSpeed, 50);

  while (Status == 0) {
    ConvertADCBack();
    if ((BL1 == 0) && (BR1 == 1))  //เจอดำข้างซ้าย
    {
      delay(1);
      ConvertADCBack();
      if ((BL1 == 0) && (BR1 == 1))  //เจอดำข้างซ้าย
      {
        Status = 1;
        AO();
        motor(1, SlowSpeed);
        motor(2, SlowSpeed);
        motor(3, -SlowSpeed);
        motor(4, -SlowSpeed);
        while (BR1 == 1) { ConvertADCBack(); }
        //delay(30);
      }
    } else if ((BL1 == 1) && (BR1 == 0))  //เจอดำข้างขวา
    {
      delay(1);
      ConvertADCBack();
      if ((BL1 == 1) && (BR1 == 0))  //เจอดำข้างขวา
      {
        Status = 2;
        AO();
        motor(1, -SlowSpeed);
        motor(2, -SlowSpeed);
        motor(3, SlowSpeed);
        motor(4, SlowSpeed);
        while (BL1 == 1) { ConvertADCBack(); }
        //delay(30);
      }
    } else if ((BL1 == 0) && (BR1 == 0)) Status = 3;  //เจอดำทั้งสองข้าง
    else if (BL2 == 0) SL(40);                        //ซ้ายสุดเจอดำ
    else if (BR2 == 0) SR(40);                        //ขวาสุดเจอดำ
    else BackwardSpeedTime(SlowSpeed, 1);
  }
  MotorStop();
  delay(250);
  ForwardSpeedTime(speed, reverse_delay);
  MotorStop();
}

void ForwardBalance_Native(int speed, int reverse_delay) {
  int Status = 0;
  delay(100);
  ForwardSpeedTime(speed, 50);

  while (Status == 0) {
    ConvertADC();
    if ((L1 == 0) && (R1 == 1))  //เจอดำข้างซ้าย
    {
      delay(1);
      ConvertADC();
      if ((L1 == 0) && (R1 == 1)) {
        Status = 1;
        AO();
        SR(SlowSpeed);
        StartTimer();
        motor(1, -SlowSpeed);
        motor(2, -SlowSpeed);
        motor(3, SlowSpeed);
        motor(4, SlowSpeed);
        while (R1 == 1) { ConvertADC(); }
        //delay(30);
      }
    } else if ((L1 == 1) && (R1 == 0))  //เจอดำข้างขวา
    {
      delay(1);
      ConvertADC();
      if ((L1 == 1) && (R1 == 0)) {
        Status = 2;
        AO();
        motor(1, SlowSpeed);
        motor(2, SlowSpeed);
        motor(3, -SlowSpeed);
        motor(4, -SlowSpeed);
        while (L1 == 1) { ConvertADC(); }
        //delay(30);
      }
    } else if ((L1 == 0) && (R1 == 0)) Status = 3;  //เจอดำทั้งสองข้าง
    else if (L2 == 0) SR(40);                       //ซ้ายสุดเจอดำ
    else if (R2 == 0) SL(40);                       //ขวาสุดเจอดำ
    else ForwardSpeedTime(40, 1);
  }
  MotorStop();
  delay(250);
  BackwardSpeedTime(speed, reverse_delay);
  MotorStop();
}

void BackwardBalanceF()  //ถอยหลังปรับสมดุลใช้เซ็นเซอร์หน้า
{
  int Status = 0;
  BackwardSpeedTime(SlowSpeed, 1);

  while (Status == 0) {
    ConvertADC();
    if ((L1 == 0) && (R1 == 1))  //เจอดำข้างซ้าย
    {
      Status = 1;
      AO();
      SR(SlowSpeed);
      StartTimer();
      while (R1 == 1) {
        ConvertADC();
        if (ReadTimer() > 300) {
          AO();
          R1 = 0;
        }
      }
      //delay(30);
    } else if ((L1 == 1) && (R1 == 0))  //เจอดำข้างขวา
    {
      Status = 2;
      AO();
      SL(SlowSpeed);
      StartTimer();
      while (L1 == 1) {
        ConvertADC();
        if (ReadTimer() > 300) {
          AO();
          L1 = 0;
        }
      }
      //delay(30);
    } else if ((L1 == 0) && (R1 == 0)) Status = 3;  //เจอดำทั้งสองข้าง
  }
  //MotorStop();
  BackwardSpeedTime(SlowSpeed, 1);
  ConvertADC();
  while (C == 0) { ConvertADC(); }
}

void ForwardBalanceB()  //เดินหน้าปรับสมดุลใช้เซ็นเซอร์หลัง
{
  int Status = 0;
  ForwardSpeedTime(SlowSpeed, 1);

  while (Status == 0) {
    ConvertADCBack();
    if ((BL2 == 0) && (BR2 == 1))  //เจอดำข้างซ้าย
    {
      Status = 1;
      AO();
      SL(SlowSpeed);
      while (BR2 == 1) { ConvertADCBack(); }
      delay(20);
    } else if ((BL2 == 1) && (BR2 == 0))  //เจอดำข้างขวา
    {
      Status = 2;
      AO();
      SR(SlowSpeed);
      while (BL2 == 1) { ConvertADCBack(); }
      delay(20);
    } else if ((BL2 == 0) && (BR2 == 0)) Status = 3;  //เจอดำทั้งสองข้าง
  }
}