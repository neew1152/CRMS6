#include <POP32.h>

// Global variables can be updated from local variables by writing "Global = Local" or "Local = Gobal" inside a function.
// Once global variables updated from local variables, the global variables will keeps the new value from local variables even after the function break.
// In other words, if every function assigns "Global = Local", you can focus on managing local variables, as global variables will automatically reflect local variables value.

// Global variables สามารถอัปเดตค่าได้ตาม Local variables โดยเขียน "Global = Local" หรือ "Local = Gobal" ในฟังก์ชัน
// เมื่อ Global variables อัปเดตตาม Local variables | Global variables จะเก็บค่าจาก Local variables ไว้ ถึงแม้ออกจากฟังก์ชันแล้ว
// หรืออีกความหมายหนึ่ง ทุกฟังก์ชันที่ประกาศ "Global = Local" หรือ "Local = Gobal" คุณแค่สนใจ Local variables เพราะ Global variables จะรับค่าจาก Local variables โดยอัตโนมัติ

int Speed, BaseSpeed, SlowSpeed, LeftBaseSpeed, RightBaseSpeed, TurnSpeed, MaxSpeed, MotorStop_Delay, DistanceRef;
int Error, PreError, Kp, Kd, Ki, Kt, KpB, KdB, KiB, KtB, BackLeftBaseSpeed, BackRightBaseSpeed, KpChange;
int RefL2, RefL1, RefC, RefR1, RefR2, SumError, RefBL2, RefBL1, RefBR1, RefBR2;
int L2, L1, C, R1, R2, BL2, BL1, BR1, BR2;
long Timer, Timer2, Timer3, Sonar;
int SW_OK_Status, digital_sw = 0;

#define SW_pin 18
#define No 0
#define Yes 1
#define BrakeSpeedIMU 100
#define BrakeTimeIMU 10

#define WheelDrive 1  // 0:ขับเคลื่อน 2 ล้อ - 1:ขับเคลื่อน 4 ล้อ
int PidStatus = 0;    // 0:ใช้ล้อข้างเดียว   - 1:ใช้ล้อ 2 ข้าง

float pvYaw;
uint8_t rxCnt = 0, rxBuf[8];

void setup() {
  Speed = 40;
  Speed = BaseSpeed;
  SlowSpeed = 50;
  TurnSpeed = 100;
  MotorStop_Delay = 50;
  InitialSpeed();
  InitialRef();
  beep(0);
  oled.clear();
  oled.mode(0);
  oled.dim(true);

  oled.textSize(2);
  oled.text(0, 0, "DLA POP-32i");
  oled.show();
  oled.textSize(1);
  oled.text(2, 0, "---------------------");
  oled.text(3, 2, "SW_OK > Operation");
  oled.text(5, 2, "SW_A > Experiment");
  oled.text(7, 1, "SW_B > Analog - Yaw");
  oled.show();
}

void loop() {
  if (SW_OK()) {
    InitSerial1();
    StartTimer();
    StartTimer2();

    oled.clear();
    oled.text(3, 2, "SW_OK > Operation");
    oled.show();
    Operation();
    beep(1);
    oled.clear();
    oled.text(3, 6, "Operation");
    oled.text(5, 4, "Successfully!");
    oled.show();
    MotorStop();
  }

  if (SW_A()) {
    InitSerial1();
    StartTimer();

    oled.clear();
    oled.text(5, 2, "SW_A > Experiment");
    oled.show();
    Experiment();
    beep(1);
    oled.clear();
    oled.text(3, 5, "Experiment");
    oled.text(5, 4, "Successfully!");
    oled.show();
    MotorStop();
  }

  if (SW_B()) {
    InitSerial1();
    StartTimer();
    oled.clear();
    Show7Analog();
    oled.clear();
    oled.text(3, 4, "Setting zeroYaw");
    oled.show();
    zeroYaw();
    ShowYaw();
  }
}