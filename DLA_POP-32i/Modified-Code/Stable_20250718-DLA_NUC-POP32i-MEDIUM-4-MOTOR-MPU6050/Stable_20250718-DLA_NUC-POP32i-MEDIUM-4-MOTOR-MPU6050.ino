#include <POP32.h>

int Speed, SlowSpeed, ACCSpeed, BaseSpeed, LeftBaseSpeed, RightBaseSpeed, TurnSpeed, MaxSpeed, SonarSpeed, MotorStop_Delay, DistanceRef;
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

#define WheelDrive 1  // 0:ขับเคลื่อน 2 ล้อ  1:ขับเคลื่อน 4 ล้อ
int PidStatus = 0;    // 0:ใช้ล้อข้างเดียว    1:ใช้ล้อ 2 ข้าง

float pvYaw;
uint8_t rxCnt = 0, rxBuf[8];

void setup() {
  Speed = 60;
  ACCSpeed = 100;
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
  oled.text(0, 0, "SW_OK > loop");
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
      oled.text(2, 0, "loop");
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
  Wait_sw_ok_press();
  beep(0);
  zeroYaw();
}

void Experiment() {
  // TestGyro();
}