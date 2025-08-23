void InitialSpeed() {
  MaxSpeed = 100;
  Ki = 0;
  KiB = 0;
  Error = 0;
  PreError = 0;
  if(BaseSpeed<=40)
  {
    LeftBaseSpeed = BaseSpeed-1;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 10;       //forward PID
    Kd = 25;
    Kt = 10;
    KpB = 10;       //backward PID
    KdB = 25;
    KtB = 10;
  }
  else if(BaseSpeed<=60)
  {
    LeftBaseSpeed = BaseSpeed- 0.7;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 13;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 13;       //backward PID
    KdB = 30;
    KtB = 10;
  }
  else if(BaseSpeed<=80)
  {
    LeftBaseSpeed = BaseSpeed- 0;
    RightBaseSpeed = BaseSpeed- 0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 19;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 19;       //backward PID
    KdB = 30;
    KtB = 8;
  }
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

void MotorStop() {
  AO();
  delay(MotorStop_Delay);
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
