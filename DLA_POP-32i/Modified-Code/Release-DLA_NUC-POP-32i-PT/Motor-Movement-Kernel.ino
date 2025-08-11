void TracDegreeSpeedTime(float MotorSpeed, int Time) {
  int TempPidStatus = PidStatus;
  int Degree = CurrentHeading;  // Track current heading dynamically
  BaseSpeed = MotorSpeed;
  MotorStop();
  StartTimer();
  InitialSpeed();
  CalErrorGyro(Degree);
  while (ReadTimer() < Time) {
    TracPID();
    StartTimer3();
    while ((ReadTimer3() < Kt)) {
      CalErrorGyro(Degree);
    }
  }
  InitialSpeed();
  PidStatus = TempPidStatus;
}

void TracDegreeSpeedTimeBack(float MotorSpeed, int Time) {
  int TempPidStatus = PidStatus;
  int Degree = CurrentHeading;  // Track current heading dynamically
  BaseSpeed = MotorSpeed;
  MotorStop();
  StartTimer();
  InitialSpeed();
  CalErrorGyroBack(Degree);
  while (ReadTimer() < Time) {
    TracPIDBack();
    StartTimer3();
    while ((ReadTimer3() < Kt)) {
      CalErrorGyroBack(Degree);
    }
  }
  InitialSpeed();
  PidStatus = TempPidStatus;
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
  MotorStop();
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
  MotorStop();
  zeroYaw();
}

void ForwardSpeed(float MotorSpeed) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  FD2(LeftBaseSpeed, RightBaseSpeed);
  InitialSpeed();
}

void ForwardSpeedTime(float MotorSpeed, int Time) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  FD2(LeftBaseSpeed, RightBaseSpeed);
  delay(Time);
  InitialSpeed();
}

void BackwardSpeed(float MotorSpeed) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  BK2(BackLeftBaseSpeed, BackRightBaseSpeed);
  InitialSpeed();
}

void BackwardSpeedTime(float MotorSpeed, int Time) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  BK2(BackLeftBaseSpeed, BackRightBaseSpeed);
  delay(Time);
  InitialSpeed();
}