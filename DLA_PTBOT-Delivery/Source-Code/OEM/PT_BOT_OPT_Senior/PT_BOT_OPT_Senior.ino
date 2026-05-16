#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>

#define NO_SWITCH_LR 0
#define SWITCH_LR 1

//                    S0   S1   S2   S3   S4   S5
int sensor_min[] = { 300, 300, 300, 300, 300, 300 };  // ค่าสีดำ
int sensor_max[] = { 770, 750, 950, 950, 900, 950 };  // ค่าสีขาว
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
  lift(3);
  ///////////////////////เปิดอ่าค่า เซนเซอร์ ////////////////////////////////
  // ShowValue_Sensor(); // โชว์ค่าเซ็นเซอร์ตรวจจับเส้น
  // ShowDistanceSensor(); // โชว์ค่าเซ็นเซอร์วัดระยะทาง
  //////////////////////////////////////////////////////////
}

void loop() {
  STOP();
  setAngleOffset();
  current_degree = 0;

  Can1();        // ออกจากจุดสตาร์ท ไปหยิบกระป๋อง และไปวางกระป๋องที่ 1
  Can2();        // ไปวางกระป๋องที่ 2
  Can3();        // ไปหยิบกระป๋อง และไปวางกระป๋องที่ 3
                 //  Can4(); // ไปวางกระป๋องที่ 4
                 //  Can5(); // ไปหยิบกระป๋อง และไปวางกระป๋องที่ 5
                 //  Can6(); // ไปวางกระป๋องที่ 6
  EndMission();  // เสร็จแล้ววิ่งไปจุดจบ
}
