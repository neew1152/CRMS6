#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>
#include <SoftI2C.h>

//                   S0   S1   S2   S3
int sensor_min[] = { 100, 100, 100, 100 };
int sensor_max[] = { 500, 500, 500, 500 };

// SONAR
float pick_can_distance = 7;
float Place_can_distance = 7.5;

// IR
float can_distance = 38;

volatile bool sonar_enable = 0;
volatile float last_distance = 0.0;
volatile int lift_target = 0;
float power_factor = 1.0;
int line_value[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
float current_degree = 0;
float previous_error_forward = 0;
byte servo_pin[] = { 6, 5, 4, 0, 1, 2, 3 };

TaskHandle_t sonarTaskHandle = NULL;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  initialize();
  xTaskCreatePinnedToCore(liftLoop, "liftLoop", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(sonarLoop, "sonarLoop", 2048, NULL, 1, &sonarTaskHandle, 0);
  vTaskSuspend(sonarTaskHandle);
  BalanceArm('O');
  lift(2);
  STOP();
}

void loop() {
}
