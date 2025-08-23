#include <POP32.h>
#define BrakeSpeedIMU 100
#define BrakeTimeIMU 10
#define max 0
#define min 2000
#define SW_pin 18
#define WheelDrive 1
#define No 0
#define Yes 1

int PidStatus = 0;
int CurrentHeading = 0; // Keep track of current heading, 0° initially

int L2, R2, BL2, BR2, RefL2, RefR2, RefBL2, RefBR2;
int Error, PreError, SumError, Kp, Kd, Ki, Kt, KpB, KdB, KiB, KtB;
long Timer, Timer2, Timer3;
float pvYaw;
float MotorStop_Delay, BaseSpeed, LeftBaseSpeed, RightBaseSpeed, BackLeftBaseSpeed, BackRightBaseSpeed, TurnSpeed, MaxSpeed;

uint8_t rxCnt = 0, rxBuf[8];

void setup() {
  BaseSpeed = 50;
  TurnSpeed = 50;
  MotorStop_Delay = 250;
  Serial1.begin(115200);
  InitialSpeed();
  InitialRef();

  oled.clear();
  oled.textSize(2);
  oled.text(0, 0, "DLA POP-32i");
  oled.show(); 
  oled.textSize(1);
  oled.text(2, 0, "---------------------");
  oled.text(3, 2, "SW_OK > Operation");
  oled.text(5, 2, "SW_A > Experiment");
  oled.text(7, 1, "SW_B > Analog - Yaw");
  oled.show(); beep(1);
}

void loop() {
  if (SW_OK()) {
    oled.clear();
    oled.text(3, 2, "SW_OK > Operation");
    oled.show();
    Operation();
    MotorStop();
  }

  if (SW_A()) {
    oled.clear();
    oled.text(5, 2, "SW_A > Experiment");
    oled.show();
    Experiment();
    MotorStop();
  }

  if (SW_B()) {
    Show7Analog();
    calibrate_IMU();
    Show_pvYaw();
  }
}
