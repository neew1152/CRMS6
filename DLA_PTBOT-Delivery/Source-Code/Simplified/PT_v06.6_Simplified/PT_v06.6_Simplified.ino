#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>
#include <SoftI2C.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

volatile bool sonar_enable = 0;
volatile float last_distance = 0.0;
volatile int lift_target = 0;
float power_factor = 1.0;
int line_value[] = { 0, 0, 0, 0};
float current_degree = 0;
float previous_error_forward = 0;
TaskHandle_t sonarTaskHandle = NULL;

// IR                S0   S1   S2   S3
int sensor_min[] = { 100, 100, 100, 100 };
int sensor_max[] = { 500, 500, 500, 500 };

// LASER
float can_distance = 38;

// SERVO
int Swing_Left = 45;
int Swing_Right = 45;
int Open_Left = 100;
int Open_Right = 100;
int Close_Left = 145;
int Close_Right = 145;

// ULTRASONIC
float pick_can_distance = 7;
float Place_can_distance = 7.5;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  i2cMutex = xSemaphoreCreateRecursiveMutex();
  initialize();
  xTaskCreatePinnedToCore(liftLoop, "liftLoop", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(sonarLoop, "sonarLoop", 2048, NULL, 1, &sonarTaskHandle, 0);
  BalanceArm('O');
  lift(2);
  STOP();
  Operation();
  // ShowValue_Sensor();
  // ShowDistanceSensor();
  STOP();
}

void loop() {
}
