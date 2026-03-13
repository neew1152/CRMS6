#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>

#define NO_SWITCH_LR 0
#define SWITCH_LR 1

// มอเตอร์ : 1-ซ้าย 2-ขวา
// เซ็นเซอร์ : ซ้ายหน้า-0 ขวาหน้า-1 ขวาหลัง-2 ซ้ายหลัง-3

//                    S0   S1   S2   S3   S4   S5
int sensor_min[] = { 240, 270, 290, 200, 240, 410 };
int sensor_max[] = { 670, 700, 950, 500, 820, 970 };
float power_factor = 1.0;

int line_value[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int current_degree = 0;
float previous_error_forward = 0;
byte servo_pin[] = { 6, 5, 4, 0, 1, 2, 3 };

long delayALL = 150;

TaskHandle_t sonarTaskHandle = NULL;
TaskHandle_t switchGripperTaskHandle = NULL;

void setup() {
  initialize();
  Serial.begin(115200);
  xTaskCreatePinnedToCore(liftLoop, "liftLoop", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(sonarLoop, "sonarLoop", 2048, NULL, 1, &sonarTaskHandle, 1);
  xTaskCreatePinnedToCore(switchGripperLoop, "switchGripperLoop", 2048, NULL, 1, &switchGripperTaskHandle, 1);
  vTaskSuspend(sonarTaskHandle);
  vTaskSuspend(switchGripperTaskHandle);
  setupDistanceSensor();
  setupServo();
  // ShoUwValue_Sensor();
  // ShowDistanceSensor();

  STOP();
  setAngleOffset();
  current_degree = 0;
  // Experiment();
  // Operation();
}

void loop() {
}
