#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>
#include <SoftI2C.h>

#define NO_SWITCH_LR 0
#define SWITCH_LR 1

/* ค่าเซ็นเซอร์ตรวจจับเส้น */
//                   S0   S1   S2   S3
int sensor_min[] = { 300, 300, 200, 200 };  // ค่าสีดำ
int sensor_max[] = { 500, 500, 500, 500 };  // ค่าสีขาว

/* ค่าเซ็นเซอร์อ่านค่าสี */
int clear_color_left = 4034;   // ค่าสีเหลืองมือจับด้านซ้าย
int clear_color_right = 3939;  // ค่าสีเหลืองมือจับด้านขวา

/* ค่าระยะจอดหน้าแท่นหยิบ */
float pick_can_distance = 5;  // ค่าระยะจอดหน้าแท่นหยิบ

/* ค่าระยะจอดหน้าแท่นวาง */
float place_left_side = 205;     // ค่าระยะจอดกรณีมือซ้ายวางกระป๋องซ้าย
float place_left_center = 150;   // ค่าระยะจอดกรณีมือซ้ายวางกระป๋องกลาง
float place_right_side = 235;    // ค่าระยะจอดกรณีมือขวาวางกระป๋องขวา
float place_right_center = 130;  // ค่าระยะจอดกรณีมือขวาวางกระป๋องกลาง

/* ค่าระยะจอดเมื่อ IR เจอกระป๋อง */
float can_distance = 30;

float power_factor = 1.0;
int line_value[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
float current_degree = 0;
float previous_error_forward = 0;
byte servo_pin[] = { 6, 5, 4, 0, 1, 2, 3 };
bool sonar_enable = 0;

long delayALL = 125;

TaskHandle_t sonarTaskHandle = NULL;
TaskHandle_t switchGripperTaskHandle = NULL;

void setup() {
  Serial.begin(115200);
  initialize();
  xTaskCreatePinnedToCore(liftLoop, "liftLoop", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(sonarLoop, "sonarLoop", 2048, NULL, 1, &sonarTaskHandle, 0);
  xTaskCreatePinnedToCore(switchGripperLoop, "switchGripperLoop", 2048, NULL, 1, &switchGripperTaskHandle, 1);
  xTaskCreatePinnedToCore(stockLoop, "stockLoop", 2048, NULL, 1, NULL, 0);
  vTaskSuspend(sonarTaskHandle);
  vTaskSuspend(switchGripperTaskHandle);
  setupColorSensor();
  setupServo();
  lift(0);
  /////////////////////// เปิดอ่านค่า เซนเซอร์ ////////////////////////////////
  // assemblyMode();  // ประกอบ และปรับค่า Servo
  // ShowValue_Sensor();  // โชว์ค่าเซ็นเซอร์ตรวจจับเส้น
  // ShowDistanceSensor();  // โชว์ค่าเซ็นเซอร์วัดระยะทาง
  // calibrateCanColor();  // Calibrate เซ็นเซอร์อ่านค่าสี
  // ShowValue_Distance();
  // ShowValue_encoder();
  //////////////////////////////////////////////////////////
  STOP();
  operation();
  motorStop();
}

void loop() {
}