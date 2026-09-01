// Helper: Checks if a specific sensor is seeing the Line (Black)
bool isLine(int sensorPin) {
  return analog(sensorPin) < ref[sensorPin];
}

// Helper: Checks if a specific sensor is seeing the Floor (White)
bool isFloor(int sensorPin) {
  return analog(sensorPin) >= ref[sensorPin];
}

// Safely stops all motors
void MotorStop() {
  ao();
  delay(100);
}

// Basic 2-sensor Line Tracking
void TrackLine(int speed1, int speed2) {
  bool leftOnFloor = isFloor(L1);
  bool rightOnFloor = isFloor(R2);

  if (leftOnFloor && rightOnFloor) {
    fd2(speed1, speed2);  // Both see floor -> Go straight with custom L/R speeds
  } else if (!leftOnFloor && rightOnFloor) {
    sl(speed1);  // Left sees line -> Adjust left
  } else if (leftOnFloor && !rightOnFloor) {
    sr(speed2);  // Right sees line -> Adjust right
  }
}

// Track line for a specific amount of time (in milliseconds)
void ForwardTrackLineTime(int speed1, int speed2, unsigned long time_ms) {
  unsigned long startTime = millis();
  while (millis() - startTime <= time_ms) {
    TrackLine(speed1, speed2);
  }
  MotorStop();
}

// Track line until a specific sensor detects the line
void ForwardTrackLineStop(int speed1, int speed2, int stopSensorPin) {
  while (isFloor(stopSensorPin)) {
    TrackLine(speed1, speed2);
  }
  MotorStop();
}

// Move straight (no tracking) until a specific sensor detects the line
void ForwardLineStop(int speed1, int speed2, int stopSensorPin) {
  while (isFloor(stopSensorPin)) {
    fd2(speed1, speed2);
  }
  MotorStop();
}

// Move straight blindly for a set duration
void ForwardDelay(int speed1, int speed2, int time_ms) {
  fd2(speed1, speed2);
  delay(time_ms);
  MotorStop();
}

// Move backward blindly for a set duration
void BackwardDelay(int speed1, int speed2, int time_ms) {
  bk2(speed1, speed2);
  delay(time_ms);
  MotorStop();
}

// Spin Left to clear current line, then stop when it finds the next line
void SLsensor(int speed, int blindDelayMs, int stopSensorPin) {
  sl(speed);
  delay(blindDelayMs);  // Blind turn to escape current line

  while (isFloor(stopSensorPin)) {
    sl(speed);  // Keep spinning until line is found
  }
  MotorStop();
}

// Spin Right to clear current line, then stop when it finds the next line
void SRsensor(int speed, int blindDelayMs, int stopSensorPin) {
  sr(speed);
  delay(blindDelayMs);  // Blind turn to escape current line

  while (isFloor(stopSensorPin)) {
    sr(speed);  // Keep spinning until line is found
  }
  MotorStop();
}