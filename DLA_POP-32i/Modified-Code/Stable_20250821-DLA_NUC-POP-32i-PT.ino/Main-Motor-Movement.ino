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

void ForwardBalance(float MotorSpeed, int reverse_delay) {
  BaseSpeed = MotorSpeed;
  while (1) {
      ConvertADC();
      if ((L2 == 0) && (R2 == 0)) {
          MotorStop();
          break;
      }
      else if (R2 == 0) {
          motor(12, LeftBaseSpeed);
          motor(34, -RightBaseSpeed);
      }
      else if (L2 == 0) {
          motor(12, -LeftBaseSpeed);
          motor(34, RightBaseSpeed);
      }
      else {
          ForwardSpeed(MotorSpeed);
      }
  }
  BackwardSpeedTime(MotorSpeed, reverse_delay);
  MotorStop();
}

void BackwardBalance(float MotorSpeed, int reverse_delay) {
  BaseSpeed = MotorSpeed;
  while (1) {
      ConvertADC();
      if ((BL2 == 0) && (BR2 == 0)) {
          MotorStop();
          break;
      }
      else if (BR2 == 0) {
          motor(12, -LeftBaseSpeed);
          motor(34, RightBaseSpeed);
      }
      else if (BL2 == 0) {
          motor(12, LeftBaseSpeed);
          motor(34, -RightBaseSpeed);
      }
      else {
          BackwardSpeed(MotorSpeed);
      }
  }
  ForwardSpeedTime(MotorSpeed, reverse_delay);
  MotorStop();
}

void TTL(int Degree) {
  CurrentHeading += Degree;
  if (CurrentHeading >= 360) CurrentHeading -= 360;
  if (CurrentHeading < 0) CurrentHeading += 360;

  int TargetDegree = CurrentHeading;
  
  int Status = 0;
  MotorStop();
  if (WheelDrive == 0) sl(TurnSpeed);
  else SL(TurnSpeed);
  for (int i = 0; i < 10; i++) {
    getIMU();
  }
  while (Status == 0) {
    if (getIMU()) {
      if ((pvYaw >= TargetDegree - 30) && (pvYaw <= TargetDegree)) {
        Status = 1;
      } else if (TargetDegree == 0) {
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
      if ((pvYaw >= TargetDegree - 5) && (pvYaw <= TargetDegree + 5)) {
        Status = 1;
      } else if (TargetDegree == 0) {
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

void TTR(int Degree) {
  // Step 1: Update current heading (right turn)
  CurrentHeading += Degree;
  if (CurrentHeading >= 360) CurrentHeading -= 360;
  if (CurrentHeading < 0) CurrentHeading += 360;

  int TargetDegree = CurrentHeading;

  // Step 2: Begin turning right
  int Status = 0;
  MotorStop();
  if (WheelDrive == 0) sr(TurnSpeed);
  else SR(TurnSpeed);

  // Read IMU a few times first
  for (int i = 0; i < 10; i++) {
    getIMU();
  }

  // Step 3: Fast turn until close to target
  while (Status == 0) {
    if (getIMU()) {
      if ((pvYaw <= TargetDegree + 30) && (pvYaw >= TargetDegree)) {
        Status = 1;
      } else if (TargetDegree >= 330) {
        if ((pvYaw <= TargetDegree - 330) || (pvYaw >= 330))
          Status = 1;
      }
    }
  }

  // Step 4: Slow down for fine adjustment
  Status = 0;
  if (WheelDrive == 0) sr(20);
  else SR(20);
  while (Status == 0) {
    if (getIMU()) {
      if ((pvYaw <= TargetDegree + 5) && (pvYaw >= TargetDegree - 5)) {
        Status = 1;
      } else if (TargetDegree >= 355) {
        if ((pvYaw <= TargetDegree - 355) || (pvYaw >= TargetDegree - 5))
          Status = 1;
      }
    }
  }

  // Step 5: Brake and stop
  if (WheelDrive == 0) sl(BrakeSpeedIMU);
  else SL(BrakeSpeedIMU);
  delay(BrakeTimeIMU);
  MotorStop();
}
