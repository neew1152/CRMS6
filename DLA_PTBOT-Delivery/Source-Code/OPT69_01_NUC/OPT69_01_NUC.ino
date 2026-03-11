#include <PTBOTAtomVX.h>  // เรียกใช้งาน Library
#include <ESP32Encoder.h>

#define NO_SWITCH_LR 0
#define SWITCH_LR 1

//                    S0   S1   S2   S3   S4   S5
int sensor_min[] = { 240, 270, 290, 200, 240, 410 };  // ค่าสีดำ
int sensor_max[] = { 670, 700, 950, 500, 820, 970 };  // ค่าสีขาว
float power_factor = 1.0;

int line_value[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int current_degree = 0;
float previous_error_forward = 0;
byte servo_pin[] = { 6, 5, 4, 0, 1, 2, 3 };

long delayALL = 150;

TaskHandle_t sonarTaskHandle = NULL;
TaskHandle_t switchGripperTaskHandle = NULL;
// มอเตอร์ ต่อ 1 ซ้าย 2 ขวา
//เซ็นเซอร์ ซ้ายหน้า = 0 ขวา หน้า 1
//เซ้็นเซอร์ หลัง ขวา 2-ซ้ายสุด 5
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
  // ShoUwValue_Sensor(); // โชว์ค่าเซ็นเซอร์ตรวจจับเส้น
  // ShowDistanceSensor(); // โชว์ค่าเซ็นเซอร์วัดระยะทาง
}

void loop() {

  STOP();
  setAngleOffset();
  current_degree = 0;
  // Experiment();
  placeCan1_NoShake_Enhanced('G', 'L', 'L', 60, 300);
  // community();
  // operation_311();
  // End();
}
