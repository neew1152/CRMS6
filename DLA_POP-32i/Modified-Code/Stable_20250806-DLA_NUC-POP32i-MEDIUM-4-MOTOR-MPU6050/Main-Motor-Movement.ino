void BackwardBalance() {
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
  zeroYaw();
}

void BackwardBalance(int reverse_delay) {
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
  zeroYaw();
  ForwardSpeedTime(SlowSpeed, reverse_delay);
}

void BackwardBalance(int reverse_delay, char select) {
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
  zeroYaw();
  ForwardSpeedTime(SlowSpeed, reverse_delay);

  if (select == 'L') {
    TurnLeftDegree();
  }
  else if (select == 'R') {
    TurnRightDegree();
  }
}

void ForwardBalance() {
  int Status = 0;
  delay(100);
  ForwardSpeedTime(SlowSpeed, 50);

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
  zeroYaw();
}

void ForwardBalance(int reverse_delay) {
  int Status = 0;
  delay(100);
  ForwardSpeedTime(SlowSpeed, 50);

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
  zeroYaw();
  BackwardSpeedTime(SlowSpeed, reverse_delay);
}

void ForwardBalance(int reverse_delay, char select) {
  int Status = 0;
  delay(100);
  ForwardSpeedTime(SlowSpeed, 50);

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
  zeroYaw();
  BackwardSpeedTime(SlowSpeed, reverse_delay);
  if (select == 'L') {
    TurnLeftDegree();
  }

  else if (select == 'R') {
    TurnRightDegree();
  }
}

void TracDegreeSpeedTime(int MotorSpeed, int Time) {
  int TempSpeed = BaseSpeed;
  int TempPidStatus = PidStatus;
  int Degree = 0;
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

void TracDegreeSpeedTime(int MotorSpeed, int Time, char select) {
  int TempSpeed = BaseSpeed;
  int TempPidStatus = PidStatus;
  int Degree = 0;
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

  if (select == 'L') {
    TurnLeftDegree();
  }
  else if (select == 'R') {
    TurnRightDegree();
  }
}

void TracDegreeSpeedTimeBack(int MotorSpeed, int Time) {
  int TempSpeed = BaseSpeed;
  int TempPidStatus = PidStatus;
  int Degree = 0;
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

void TracDegreeSpeedTimeBack(int MotorSpeed, int Time, char select) {
  int TempSpeed = BaseSpeed;
  int TempPidStatus = PidStatus;
  int Degree = 0;
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

  if (select == 'L') {
    TurnLeftDegree();
  }
  else if (select == 'R') {
    TurnRightDegree();
  }
}

void TurnLeftDegree() {
  int Status = 0;
  int Degree = 90;
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
  zeroYaw();
}

void TurnRightDegree() {
  int Status = 0;
  int Degree = 270;
  MotorStop();
  if (WheelDrive == 0) sr(TurnSpeed);
  else SR(TurnSpeed);
  for (int i = 0; i < 10; i++) {
    getIMU();
  }
  while (Status == 0) {
    if (getIMU()) {
      if ((pvYaw <= Degree + 30) && (pvYaw >= Degree)) {
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
      if ((pvYaw <= Degree + 5) && (pvYaw >= Degree - 5)) {
        Status = 1;
      } else if (Degree >= 355) {
        if ((pvYaw <= Degree - 355) || (pvYaw >= Degree - 5)) Status = 1;
      }
    }
  }
  if (WheelDrive == 0) sl(BrakeSpeedIMU);
  else SL(BrakeSpeedIMU);
  delay(BrakeTimeIMU);
  zeroYaw();
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