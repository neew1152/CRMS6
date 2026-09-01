void Slide_Calibration() {
  int minVal[NUM_SENSORS] = { 4095, 4095, 4095, 4095 };
  int maxVal[NUM_SENSORS] = { 0, 0, 0, 0 };

  glcdClear();
  glcd(0, 0, "Slide Calibration");

  unsigned long timerStart = millis();

  // Scan for 5 seconds
  while (millis() - timerStart < 5000) {
    for (int i = 0; i < NUM_SENSORS; i++) {
      int val = analog(SENSOR_PINS[i]);

      if (val > maxVal[i]) maxVal[i] = val;
      if (val < minVal[i]) minVal[i] = val;
    }

    glcd(1, 0, "SCANNING... %d Sec", 5 - (millis() - timerStart) / 1000);
    delay(5);  // Small delay to prevent display flickering
  }

  // Calculate midpoints and apply to references
  for (int i = 0; i < NUM_SENSORS; i++) {
    ref[i] = (minVal[i] + maxVal[i]) / 2;
  }

  // Display Results
  glcdClear();
  glcd(0, 0, "Ref Values:");
  glcd(1, 0, "L0:%d L1:%d", ref[L0], ref[L1]);
  glcd(2, 0, "R2:%d R3:%d", ref[R2], ref[R3]);

  glcd(4, 4, "Min .. Max");
  glcd(5, 0, "L0: %d..%d", minVal[L0], maxVal[L0]);
  glcd(6, 0, "L1: %d..%d", minVal[L1], maxVal[L1]);
  glcd(7, 0, "R2: %d..%d", minVal[R2], maxVal[R2]);
  glcd(8, 0, "R3: %d..%d", minVal[R3], maxVal[R3]);
}