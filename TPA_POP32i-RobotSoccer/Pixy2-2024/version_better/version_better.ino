#include <POP32.h>
#include <POP32_Huskylens.h>
POP32_Huskylens huskylens;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
// ค่าที่ใช้ปรับหุ่นให้เข้าด้านหน้าตรงลูกบอล
#define rot_Kp 0.7
#define rot_Ki 0.0
#define rot_Kd 1.5
#define sp_rot 160      // ค่า setpoint ที่ลูกบอลอยู่ตรงกลางกล้องแกน x  320/2 = 160
#define rotErrorGap 15  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
#define idleSpd 35      // ค่าความเร็วการหมุนเมื่อไม่เจอลูกบอล
float rot_error, rot_pError, rot_i, rot_d, rot_w;
int ballPosX;
// ค่าที่ใช้ปรับหุ่นให้เข้าใกล้ลูกบอล
#define fli_Kp 3.0
#define fli_Ki 0.0
#define fli_Kd 1.5
#define flingErrorGap 15  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
float spFli = 190;        // ค่า setpoint ที่ยอมให้ลูกบอลอยู่ใกล้หุ่นมากที่สุด อาจเริ่มที่จุดกลางจอ แกน Y
float fli_error, fli_pError, fli_i, fli_d, fli_spd;
int ballPosY;
// ค่าที่ใช้ปรับหุ่นให้ตรงทิศอ้างอิง
#define alignErrorGap 4
float vecCurve, radCurve;
int discoveState = 1;
// ค่าที่ใช้รักษาทิศหุ่นยนต์
#define head_Kp 2.3f
#define head_Ki 0.0f
#define head_Kd 0.5f
float head_error, head_pError, head_w, head_d, head_i;
/* >> ball shooting <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */
#define limPin A0
#define reloadSpd 80

/*>>  ส่วนของ MPU6050 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */
float pvYaw, lastYaw;
uint8_t rxCnt = 0, rxBuf[8];
int helpcave;
float HelpYaw;

/*>>>>>>>>>>>>>  ส่วนของ PID  <<<<<<<<<<<<<<<<<<<<<<<< */
float thetaRad, vx, vy, spd1, spd2, spd3;
int L, C, R;
int Timer;
int Time = 1000;

//>>>>>>>> ค่าที่ใช้เช็คการค้นหาลูกบอล
int oc = 0;

int side; //สำหรับ Goal keepper
int button;
int Count = 1;

void setup() {
  sound(3000, 200);
  sound(3000, 200);
  oled.clear();
  oled.text(3, 3, "Setting shoot");
  oled.show();
  //reload();
  while (!huskylens.begin(Wire)) {
    oled.text(1, 0, "Begin failed!");
    oled.show();
    delay(100);
  }
  zeroYaw();
  oled.clear();
  oled.text(2, 1, "Wellcome to  Menu");
  oled.show();
  delay(100);
  delay(3000);
  Auto_zero();  //เรียกใช้ฟังก์ชันเซ็ตมุมอัตโนมัติ
  //ReadMPU();
}
void loop() {
  Menu();
}