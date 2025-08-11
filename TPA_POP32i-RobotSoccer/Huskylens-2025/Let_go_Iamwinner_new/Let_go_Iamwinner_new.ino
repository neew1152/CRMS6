#include <POP32.h>
#include <POP32_Huskylens.h>
POP32_Huskylens huskylens;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
// ค่าที่ใช้ปรับหุ่นให้เข้าด้านหน้าตรงลูกบอล
#define rot_Kp 0.2
#define rot_Kp_slide 1.5
#define rot_Ki 0.0
#define rot_Kd 0.25
#define sp_rot 160     // ค่า setpoint ที่ลูกบอลอยู่ตรงกลางกล้องแกน x  320/2 = 160
#define rotErrorGap 15  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
#define idleSpd 35      // ค่าความเร็วการหมุนเมื่อไม่เจอลูกบอล
float rot_error, rot_pError, rot_i, rot_d, rot_w;
int ballPosX;
// ค่าที่ใช้ปรับหุ่นให้เข้าใกล้ลูกบอล
#define fli_Kp 3.0
#define fli_Ki 0.0
#define fli_Kd 1.0
#define flingErrorGap 15  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
float spFli = 165;        // ค่า setpoint ที่ยอมให้ลูกบอลอยู่ใกล้หุ่นมากที่สุด อาจเริ่มที่จุดกลางจอ แกน Y
float fli_error, fli_pError, fli_i, fli_d, fli_spd;
int ballPosY;
// ค่าที่ใช้ปรับหุ่นให้ตรงทิศอ้างอิง
#define alignErrorGap 4
float vecCurve, radCurve;
int discoveState = 1;
// ค่าที่ใช้รักษาทิศหุ่นยนต์
#define head_Kp 2.0f
#define head_Ki 0.0f
#define head_Kd 0.7f
float head_error, head_pError, head_w, head_d, head_i;
/* >> ball shooting <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */
#define limPin A0
#define reloadSpd 60


/*>>  ส่วนของ MPU6050 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */
float pvYaw, lastYaw;
uint8_t rxCnt = 0, rxBuf[8];

/*>>>>>>>>>>>>>  ส่วนของ PID  <<<<<<<<<<<<<<<<<<<<<<<< */
float thetaRad, vx, vy, spd1, spd2, spd3;
int L, C, R , B;
int Timer;


int oc = 14; // ปัญหาตรงนี้จะทำให้หุ่นวิ่งหาบอลช้า เเละสบัด

int side; //สำหรับ Goal keepper

int button; //Menu
int Count; // Menu

int shooting = 0; /* ตั้งค่าโหมดยิง */

int sensor = 0;  //เช็คsensor ฝั่งไหนเจอ discoverball
int Check = 0;


int Mode = 1; /* discoverball  */
int check = 1 , Status = 1; //discoverball
int Time = 500;//discoverball
int Count_dissball = 0; //discoverball 
int Round = 0; //
int A = 0;


int step = 1;//Offend function
int Check_outline = 1;//Out_line
int Check_shootnow = 1;//Shoot_now

int GoalPosX;

void setup() {
  sound(3000, 200);
  sound(3000, 200);
  oled.clear();
  oled.text(3, 3, "Setting shoot");
  oled.show();
  reload();
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
  //SetRobot();
  oled.clear();
  oled.text(2,2,"SW_OK == Menu");
  oled.text(4,2,"SW_A == test shoot");
  oled.show();
}
void loop() {
  //updateIMU();
  //heading(90,0,0);
  if(SW_OK())
  {
    Menu();
  }
  else if(SW_A())
  {
    shoot();
    reload();
  }
}