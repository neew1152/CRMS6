void TracDegreeSpeedTime(float MotorSpeed, int Time) {
  int TempPidStatus = PidStatus;
  int Degree = CurrentHeading;  // Track current heading dynamically
  BaseSpeed = MotorSpeed;
  Timer = millis();
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
  Timer = millis();
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

void Forward_Balance(float MotorSpeed, int reverse_delay) {
  BaseSpeed = MotorSpeed;
  while (1) {
    ConvertADC();
    if ((L2 == 0) && (R2 == 0)) {
      MotorStop();
      break;
    } else if (R2 == 0) {
      motor(12, LeftBaseSpeed);
      motor(34, -RightBaseSpeed);
    } else if (L2 == 0) {
      motor(12, -LeftBaseSpeed);
      motor(34, RightBaseSpeed);
    } else {
      ForwardSpeed(MotorSpeed);
    }
  }
  BackwardSpeedTime(MotorSpeed, reverse_delay);
}

void Backward_Balance(float MotorSpeed, int reverse_delay) {
  BaseSpeed = MotorSpeed;
  while (1) {
    ConvertADC();
    if ((BL2 == 0) && (BR2 == 0)) {
      MotorStop();
      break;
    } else if (BR2 == 0) {
      motor(12, -LeftBaseSpeed);
      motor(34, RightBaseSpeed);
    } else if (BL2 == 0) {
      motor(12, LeftBaseSpeed);
      motor(34, -RightBaseSpeed);
    } else {
      BackwardSpeed(MotorSpeed);
    }
  }
  ForwardSpeedTime(MotorSpeed, reverse_delay);
}

void TTL(int Degree) {
  // Update heading
  CurrentHeading += Degree;  // left turn decreases heading
  if (CurrentHeading < 0) CurrentHeading += 360;

  int TargetDegree = CurrentHeading;

  // Start turning
  MotorStop();
  if (WheelDrive == 0) sl(TurnSpeed);
  else SL(TurnSpeed);

  // Spin until close to target
  while (true) {
    if (getIMU()) {
      float error = angleError(TargetDegree, normalizeYaw(pvYaw));
      if (fabs(error) <= 30) break;  // within fast-turn window
    }
  }

  // Slow down for fine adjustment
  if (WheelDrive == 0) sl(20);
  else SL(20);

  while (true) {
    if (getIMU()) {
      float error = angleError(TargetDegree, normalizeYaw(pvYaw));
      if (fabs(error) <= 5) break;  // fine target window
    }
  }

  // Brake and stop
  if (WheelDrive == 0) sr(BrakeSpeedIMU);
  else SR(BrakeSpeedIMU);
  delay(BrakeTimeIMU);
  MotorStop();
}

void TTR(int Degree) {
  // Update heading
  CurrentHeading += Degree;  // right turn increases heading
  if (CurrentHeading >= 360) CurrentHeading -= 360;

  int TargetDegree = CurrentHeading;

  // Start turning
  MotorStop();
  if (WheelDrive == 0) sr(TurnSpeed);
  else SR(TurnSpeed);

  // Spin until close to target
  while (true) {
    if (getIMU()) {
      float error = angleError(TargetDegree, normalizeYaw(pvYaw));
      if (fabs(error) <= 30) break;
    }
  }

  // Slow down for fine adjustment
  if (WheelDrive == 0) sr(20);
  else SR(20);

  while (true) {
    if (getIMU()) {
      float error = angleError(TargetDegree, normalizeYaw(pvYaw));
      if (fabs(error) <= 5) break;
    }
  }

  // Brake and stop
  if (WheelDrive == 0) sl(BrakeSpeedIMU);
  else SL(BrakeSpeedIMU);
  delay(BrakeTimeIMU);
  MotorStop();
}

void U_TTL(int Degree) {
  // Update heading
  CurrentHeading -= Degree;
  if (CurrentHeading < 0) CurrentHeading += 360;
  int TargetDegree = CurrentHeading;

  MotorStop();
  if (WheelDrive == 0) sl(TurnSpeed);
  else SL(TurnSpeed);

  // Fast turn until within 30°
  while (true) {
    if (getIMU()) {
      float err = angleError(TargetDegree, normalizeYaw(pvYaw));
      if (fabs(err) <= 30) break;
    }
  }

  // Slow down for fine adjustment
  if (WheelDrive == 0) sl(20);
  else SL(20);

  while (true) {
    if (getIMU()) {
      float err = angleError(TargetDegree, normalizeYaw(pvYaw));
      if (fabs(err) <= 5) break;
    }
  }

  // Brake
  if (WheelDrive == 0) sr(BrakeSpeedIMU);
  else SR(BrakeSpeedIMU);
  delay(BrakeTimeIMU);
  MotorStop();
}

void U_TTR(int Degree) {
  // Update heading
  CurrentHeading += Degree;
  if (CurrentHeading >= 360) CurrentHeading -= 360;
  int TargetDegree = CurrentHeading;

  MotorStop();
  if (WheelDrive == 0) sr(TurnSpeed);
  else SR(TurnSpeed);

  // Fast turn until within 30°
  while (true) {
    if (getIMU()) {
      float err = angleError(TargetDegree, normalizeYaw(pvYaw));
      if (fabs(err) <= 30) break;
    }
  }

  // Slow down for fine adjustment
  if (WheelDrive == 0) sr(20);
  else SR(20);

  while (true) {
    if (getIMU()) {
      float err = angleError(TargetDegree, normalizeYaw(pvYaw));
      if (fabs(err) <= 5) break;
    }
  }

  // Brake
  if (WheelDrive == 0) sl(BrakeSpeedIMU);
  else SL(BrakeSpeedIMU);
  delay(BrakeTimeIMU);
  MotorStop();
}