// Global variables can be updated from local variables by writing "Global = Local" or "Local = Gobal" inside a function.
// Once global variables updated from local variables, the global variables will keeps the new value from local variables even after the function break.
// To keep global variables up-to-date, you must set local variables every time in every function that assigns "Global = Local" or "Local = Gobal".
// In other words, if every function assigns "Global = Local", you can focus on managing local variables, as global variables will automatically reflect local variables value.

// Global variables สามารถอัปเดตค่าได้ตาม Local variables โดยเขียน "Global = Local" หรือ "Local = Gobal" ในฟังก์ชัน
// เมื่อ Global variables อัปเดตตาม Local variables — Global variables จะเก็บค่าจาก Local variables ไว้ ถึงแม้ออกจากฟังก์ชันแล้ว
// เพื่อให้ Global variables อัปเดต คุณต้องใส่ค่า Local variables ในทุกฟังก์ชันที่ประกาศ "Global = Local" หรือ "Local = Gobal"
// หรืออีกความหมายหนึ่ง ทุกฟังก์ชันที่ประกาศ "Global = Local" หรือ "Local = Gobal" คุณแค่สนใจ Local variables เพราะ Global variables จะรับค่าจาก Local variables โดยอัตโนมัติ

void BackwardBalance()  //ถอยหลังปรับสมดุล
{
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
}

void ForwardBalance() {
  int Status = 0;
  delay(100);
  ForwardSpeedTime(40, 50);

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
  BackwardSpeedTime(40, 250);
}

void TracDegreeSpeedTime(int MotorSpeed, int Degree, int Time, int PIDtemp) {
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

void TracDegreeSpeedTimeBack(int MotorSpeed, int Degree, int Time, int PIDtemp) {
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

void TurnLeftDegree(int TurnSpeed, float Degree, int Origin) {  // 0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  int Status = 0;
  MotorStop();
  if (Origin != 1) zeroYaw();
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
}

void TurnRightDegree(int TurnSpeed, float Degree, int Origin) {  // 0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
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

void TracJCSonar(int Aaa)  //เดินถึงเส้นและออกจากฟังก์ชัน
{
  Sonar = analog(2) / 40;
  ForwardSpeed(20);
  while (1) {
    Sonar = analog(2) / 40;
    if (Sonar <= Aaa) break;
  }
  MotorStop();
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