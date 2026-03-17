#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>
#include <SoftI2C.h>

#define NO_SWITCH_LR 0
#define SWITCH_LR 1
/* ค่าเซ็นเซอร์ตรวจจับเส้น */
//                   S0   S1   S2   S3
int sensor_min[] = { 120, 90, 110, 120 };   // ค่าสีดำ
int sensor_max[] = { 500, 370, 500, 485 };  // ค่าสีขาว

/* ค่าเซ็นเซอร์อ่านค่าสี */
int clear_color_left = 4034;   // ค่าสีเหลืองมือจับด้านซ้าย
int clear_color_right = 3939;  // ค่าสีเหลืองมือจับด้านขวา

/* ค่าระยะจอดหน้าแท่นหยิบ */
float pick_can_distance = 7;     // ค่าระยะจอดหน้าแท่นหยิบ
float Place_can_distance = 7.5;  // ค่าระยะจอดหน้าแท่นหยิบ

/* ค่าระยะจอดหน้าแท่นวาง */
float place_left_side = 205;     // ค่าระยะจอดกรณีมือซ้ายวางกระป๋องซ้าย
float place_left_center = 150;   // ค่าระยะจอดกรณีมือซ้ายวางกระป๋องกลาง
float place_right_side = 235;    // ค่าระยะจอดกรณีมือขวาวางกระป๋องขวา
float place_right_center = 130;  // ค่าระยะจอดกรณีมือขวาวางกระป๋องกลาง

/* ค่าระยะจอดเมื่อ IR เจอกระป๋อง */
float can_distance = 38;

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
  // setupColorSensor();
  setupServo();
  lift(2);
  STOP();
  /////////////////////// เปิดอ่านค่า เซนเซอร์ ////////////////////////////////
  // assemblyMode();  // ประกอบ และปรับค่า Servo
  // ShowValue_Sensor();  // โชว์ค่าเซ็นเซอร์ตรวจจับเส้น
  // ShowDistanceSensor();  // โชว์ค่าเซ็นเซอร์วัดระยะทาง
  // calibrateCanColor();  // Calibrate เซ็นเซอร์อ่านค่าสี
  ////////////////////เทสค่า มือจับ Clos - Open ก่อน //////////////////////////////////////
  // STOP();servoCloseLeft();
  // STOP();servoCloseRight();
  // STOP();servoOpenLeft();
  // STOP();servoOpenRight();
  // set_clos_open(); //อยู่ Diy จะคีบแขน ซ้าย กดปุ่ม คีบขวา กดปุ่ม เปิดซ้าย กดุปุ่ม เปิดขวา
  ////////////////////// set Can1 ให้กางแค่เล็กน้อย//////////
  // get_b(5); //คีบ แล้ว(ยก) คู่
  // delay(2000);
  // setCan1(11); // มีระยะกางมือจับเล็กน้อย(open)
  // delay(2000);
  // drop_b(11); //ปล่อยกระป๋อง คู่ มีระยะกางมือจับเล็กน้อยก่อน(open)
  // lift(0);
  ///////////////////// เดินหน้าจับกระป๋องจากแท่น /////////////////
  // SetBack(25, 200, 'R');
  // PickCan(5); // หยิบกระป๋อง
  // BB(30, 500);
  // setCan1(11); // มีระยะกางมือจับเล็กน้อย(open)
  // SetBack(25, 200, 'L');  //เช็ตหลังตรง เมื่อเจอเส้นดำ จะถอยเดินจากเส้นดำ พร้อมเลี้ยว SetBack(ความเร็วมอเตอร์ทั้ง 4 ตัว, ระยะทางนับเวลาเดินออกจากเส้นดำ 1000=1วินาที, เลือกทิศทางเลี้ยว)
  // placeCan1(7,300,'a','a'); // สูง, ถอย วางขวา , l-l l-c r-r r-c else วางคู่
  // placeCan1(7,200,'r','c'); // สูง, ถอย วางขวา , l-l l-c r-r r-c else วางคู่
  // placeCan1(7,200,'l','l'); // สูง, ถอย วางกลาง , l-l l-c r-r r-c else วางคู่
  // placeCan1(7,200,'l','c'); // สูง, ถอย วางกลาง , l-l l-c r-r r-c else วางคู่
  // BB(30, 500);
  // placeCan1(7,300,'r','r'); // สูง, ถอย วางขวา , l-l l-c r-r r-c else วางคู่
  // placeCan1(7,300,'l','l'); // สูง, ถอย วางขวา , l-l l-c r-r r-c else วางคู่
  // BB(30, 400);
  //////////////////////////////////////////////
  // Can1();
  Operation();
  // Experiment();
  motorStop();
}

void loop() {
  // STOP();
  // setAngleOffset();
  // current_degree = 0;
  // servoCloseLeft();
  // servoCloseRight();


  // Can1();  // ออกจากจุดสตาร์ท ไปหยิบกระป๋อง และไปวางแท่นที่ 1
  // Can2();        // ไปหยิบกระป๋อง และไปวางแท่นที่ 2
  // Can3();        // ไปหยิบกระป๋อง และไปวางแท่นที่ 3
  // EndMission();  // เสร็จแล้ววิ่งไปจุดจบ
}