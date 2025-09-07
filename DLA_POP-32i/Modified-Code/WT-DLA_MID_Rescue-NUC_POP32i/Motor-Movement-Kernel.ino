void InitialSpeed() {
  MaxSpeed = 100;
  Ki = 0;
  KiB = 0;
  Error = 0;
  PreError = 0;

  // It's recommended to use ForwardSpeedTime() for motor tuning.

  if (BaseSpeed <= 40) {
    LeftBaseSpeed = BaseSpeed - 0;
    RightBaseSpeed = BaseSpeed - 1;
    BackLeftBaseSpeed = BaseSpeed - 0;
    BackRightBaseSpeed = BaseSpeed - 0;
    Kp = 10;  // Forward PID
    Kd = 25;
    Kt = 10;
    KpB = 10;  // Backward PID
    KdB = 25;
    KtB = 10;
  } else if (BaseSpeed <= 60) {
    LeftBaseSpeed = BaseSpeed - 1.25;
    RightBaseSpeed = BaseSpeed - 0;
    BackLeftBaseSpeed = BaseSpeed - 0;
    BackRightBaseSpeed = BaseSpeed - 0;
    Kp = 13;  // Forward PID
    Kd = 30;
    Kt = 10;
    KpB = 13;  // Backward PID
    KdB = 30;
    KtB = 10;
  } else if (BaseSpeed <= 80) {
    LeftBaseSpeed = BaseSpeed - 3;
    RightBaseSpeed = BaseSpeed - 0;
    BackLeftBaseSpeed = BaseSpeed - 0;
    BackRightBaseSpeed = BaseSpeed - 0;
    Kp = 19;  // Forward PID
    Kd = 30;
    Kt = 10;
    KpB = 19;  // Backward PID
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
