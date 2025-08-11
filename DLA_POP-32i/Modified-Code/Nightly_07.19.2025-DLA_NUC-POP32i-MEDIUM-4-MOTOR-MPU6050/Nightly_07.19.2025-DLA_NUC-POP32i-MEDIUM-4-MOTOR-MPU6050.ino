#include <POP32.h>

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

// Global variables can be updated from local variables by writing "Global = Local" or "Local = Gobal" inside a function.
// Once global variables updated from local variables, the global variables will keeps the new value from local variables even after the function break.
// To keep global variables up-to-date, you must set local variables every time in every function that assigns "Global = Local" or "Local = Gobal".
// In other words, if every function assigns "Global = Local", you can focus on managing local variables, as global variables will automatically reflect local variables value.

// Global variables สามารถอัปเดตค่าได้ตาม Local variables โดยเขียน "Global = Local" หรือ "Local = Gobal" ในฟังก์ชัน
// เมื่อ Global variables อัปเดตตาม Local variables — Global variables จะเก็บค่าจาก Local variables ไว้ ถึงแม้ออกจากฟังก์ชันแล้ว
// เพื่อให้ Global variables อัปเดต คุณต้องใส่ค่า Local variables ในทุกฟังก์ชันที่ประกาศ "Global = Local" หรือ "Local = Gobal"
// หรืออีกความหมายหนึ่ง ทุกฟังก์ชันที่ประกาศ "Global = Local" หรือ "Local = Gobal" คุณแค่สนใจ Local variables เพราะ Global variables จะรับค่าจาก Local variables โดยอัตโนมัติ

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
  oled.textSize(1);
  oled.text(0, 0, "SW_OK > Operation");
  oled.text(1, 0, "SW_A > Show7Analog && ShowYaw");
  oled.text(2, 0, "SW_B > Experiment");
  oled.show();
  SW_OK_Status = No;

  while (SW_OK_Status == No) {
    if (Read_sw_OK()) {
      InitSerial1();
      StartTimer();

      beep(1);
      oled.clear();
      oled.text(2, 0, "Operation");
      oled.show();

      SW_OK_Status = Yes;
    }

    if (SW_A()) {
      InitSerial1();
      StartTimer();
      Show7Analog();
      ShowYaw();
      SW_OK_Status = Yes;
    }

    if (SW_B()) {
      InitSerial1();
      StartTimer();

      beep(1);
      oled.clear();
      oled.text(2, 0, "Experiment");
      oled.show();
      Experiment();

      SW_OK_Status = Yes;
    }
  }
  StartTimer2();
}

void loop() {
  Operation();
}