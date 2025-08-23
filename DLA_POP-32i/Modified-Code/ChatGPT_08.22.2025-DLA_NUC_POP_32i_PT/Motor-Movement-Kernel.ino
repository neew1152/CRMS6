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
