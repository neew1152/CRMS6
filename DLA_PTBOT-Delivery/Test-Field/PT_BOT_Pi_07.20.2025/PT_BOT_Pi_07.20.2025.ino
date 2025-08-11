#include <PTBOTAtomVX.h>  // เรียกใช้งาน Library
#include <ESP32Encoder.h>

#define NO_SWITCH_LR 0
#define SWITCH_LR 1

//                    S0   S1   S2   S3   S4   S5
int sensor_min[] = { 175, 150, 150, 50, 50, 230 };    // ค่าสีดำ
int sensor_max[] = { 685, 520, 630, 250, 300, 900 };  // ค่าสีขาว
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
  initialize();          // เริ่มต้นการทำงานบอร์ด Atom VX  จะแสดง รูป PT
  Serial.begin(115200);  // เริ่มต้นใช้งาน Serial
  xTaskCreatePinnedToCore(liftLoop, "liftLoop", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(sonarLoop, "sonarLoop", 2048, NULL, 1, &sonarTaskHandle, 1);
  xTaskCreatePinnedToCore(switchGripperLoop, "switchGripperLoop", 2048, NULL, 1, &switchGripperTaskHandle, 1);
  vTaskSuspend(sonarTaskHandle);
  vTaskSuspend(switchGripperTaskHandle);
  setupDistanceSensor();
  setupServo();
  // lift(3);  // ยกแขน 3 จากจุดเดิม *ก่อนเปิดหุ่นต้องกดลงให้สุดก่อน ** สำคัญต้องปรับก่อน
  ///////////////////////เปิดอ่าค่า เซนเซอร์ ////////////////////////////////
  // ShowValue_Sensor(); // โชว์ค่าเซ็นเซอร์ตรวจจับเส้น
  // ShowDistanceSensor(); // โชว์ค่าเซ็นเซอร์วัดระยะทาง
  //////////////////////////////////////////////////////////
}

void loop() {

  STOP();  //สั่งหยุด กด SW1 or SW2 เพื่อทำงานต่อ
  setAngleOffset(); // เช็ตตั้งค่า servo 
  current_degree = 0;
  
  operation_community();
  // operation_311();
  // test();
}

void test()
{
  // 2 = 200, 2.5 = 275, 3 = 500, 4 = 850, Hight Way = 1300 1400
  //      IN             OUT
  // SetFront = 400, SetFront = 425
  // SetBack = 200, SetBack = 225
}