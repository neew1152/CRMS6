#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>
#include <SoftI2C.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#define chanal_Swing_Left 0
#define chanal_Swing_Right 1
#define chanal_Gripper_Left 2
#define chanal_Gripper_Right 3

ESP32Encoder encoder;

volatile bool sonar_enable = 0;
volatile float last_distance = 0.0;
volatile int lift_target = 0;
int line_value[] = { 0, 0, 0, 0};
int swing_current_degree[] = { 0, 0 };
float current_degree = 0;
float power_factor = 1.0;
float previous_error_forward = 0;
TaskHandle_t sonarTaskHandle = NULL;

// IR                S0   S1   S2   S3
int sensor_min[] = { 75, 95, 125, 120 };
int sensor_max[] = { 580, 700, 780, 730 };

// LASER
float can_distance = 38;

// SERVO
int Swing_Left = 58;   // S0 เพิ่ม ง้างออก
int Swing_Right = 58;  // S1 ลด หุบเข้า
int Open_Left = 110;  // S2 เพิ่ม หุบเข้า
int Open_Right = 90;  // S3 ลด หุบออก
int Close_Left = 147;   // S2 เพิ่ม หุบเข้า
int Close_Right = 127;  // S3 ลด หุบออก

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
