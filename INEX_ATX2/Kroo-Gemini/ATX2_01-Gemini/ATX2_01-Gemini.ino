#include <ATX2.h>

// Define sensor pins for easy reference
const int L0 = 0;
const int L1 = 1;
const int R2 = 2;
const int R3 = 3;

const int NUM_SENSORS = 4;
const int SENSOR_PINS[NUM_SENSORS] = { L0, L1, R2, R3 };

// Array to hold Reference values (Thresholds)
// Indexes: 0=L0, 1=L1, 2=R2, 3=R3
int ref[NUM_SENSORS] = { 600, 600, 600, 600 };

void setup() {
  XIO();
  beep();
  servo(1, 90);
  OK();
  delay(500);
  glcdMode(0);
  glcdClear();
  setTextSize(1);

  // Slide_Calibration();
  // Experiment();
  // Operation();
}

void loop() {
}
