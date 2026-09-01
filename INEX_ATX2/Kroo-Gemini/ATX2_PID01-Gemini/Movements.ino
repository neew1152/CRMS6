// ==========================================
// PID Constants (Tune these for your robot)
// ==========================================
float Kp = 0.02;  // Proportional: Adjusts turning sharpness
float Ki = 0.00;  // Integral: Helps with steady-state errors (usually 0 for line followers)
float Kd = 0.10;  // Derivative: Dampens wobbling/oscillation

int last_error = 0;
long integral = 0;

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

// ==========================================
// PID Error Calculation
// ==========================================
int getLineError() {
  // Your code indicates: Black Line = Low analog value, White Floor = High value.
  // We apply weights to the sensors. Outer sensors trigger a stronger turn.
  int WEIGHT_NEAR = 1;
  int WEIGHT_FAR = 3;

  int left_val = (analog(L1) * WEIGHT_NEAR) + (analog(L0) * WEIGHT_FAR);
  int right_val = (analog(R2) * WEIGHT_NEAR) + (analog(R3) * WEIGHT_FAR);

  // If robot drifts right, line moves to Left sensors -> Left value drops.
  // Left - Right becomes Negative -> Signals robot to steer Left.
  return left_val - right_val;
}

// ==========================================
// Smooth PID Line Tracking
// ==========================================
void TrackLine(int baseSpeedL, int baseSpeedR) {
  int error = getLineError();

  integral += error;
  integral = constrain(integral, -5000, 5000);  // Prevent integral windup

  int derivative = error - last_error;

  // Calculate PID adjustment
  int turn = (Kp * error) + (Ki * integral) + (Kd * derivative);
  last_error = error;

  // Apply adjustment to motor speeds
  int speedL = baseSpeedL + turn;
  int speedR = baseSpeedR - turn;

  // Constrain to maximum ATX2 motor limits (-100 to 100)
  speedL = constrain(speedL, -100, 100);
  speedR = constrain(speedR, -100, 100);

  // Drive motors (fd2 accepts negative numbers for reversing wheels during sharp turns)
  fd2(speedL, speedR);
}

// Track line for a specific amount of time (in milliseconds)
void ForwardTrackLineTime(int speed1, int speed2, unsigned long time_ms) {
  unsigned long startTime = millis();

  // Reset PID history before starting a fresh run
  last_error = 0;
  integral = 0;

  while (millis() - startTime <= time_ms) {
    TrackLine(speed1, speed2);
  }
  MotorStop();
}

// Track line until a specific sensor detects the line
void ForwardTrackLineStop(int speed1, int speed2, int stopSensorPin) {
  last_error = 0;
  integral = 0;

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