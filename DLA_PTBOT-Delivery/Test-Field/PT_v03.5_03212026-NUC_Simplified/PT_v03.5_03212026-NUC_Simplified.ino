#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>
#include <SoftI2C.h>

#define NO_SWITCH_LR 0
#define SWITCH_LR 1

//                   S0   S1   S2   S3
int sensor_min[] = { 120, 90, 110, 120 };   // ค่าสีดำ
int sensor_max[] = { 500, 370, 500, 485 };  // ค่าสีขาว

// SONAR
float pick_can_distance = 7;
float Place_can_distance = 7.5;

// IR
float can_distance = 38;

float power_factor = 1.0;
int line_value[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
float current_degree = 0;
float previous_error_forward = 0;
byte servo_pin[] = { 6, 5, 4, 0, 1, 2, 3 };
bool sonar_enable = 0;

TaskHandle_t sonarTaskHandle = NULL;
TaskHandle_t switchGripperTaskHandle = NULL;

void setup() {
  Serial.begin(115200);
  initialize();
  xTaskCreatePinnedToCore(liftLoop, "liftLoop", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(sonarLoop, "sonarLoop", 2048, NULL, 1, &sonarTaskHandle, 0);
  xTaskCreatePinnedToCore(switchGripperLoop, "switchGripperLoop", 2048, NULL, 1, &switchGripperTaskHandle, 1);
  vTaskSuspend(sonarTaskHandle);
  vTaskSuspend(switchGripperTaskHandle);
  Balance_Arm('O');
  lift(2);
  STOP();
  // ShowValue_Sensor();
  // ShowDistanceSensor();
  // TS();
  // TAL();
  Operation();
  // Experiment();
  STOP();
}

void loop() {
}