#include <POP32.h>
float previous_error_forward = 0;
float pvYaw;
uint8_t rxCnt = 0, rxBuf[8];
float BaseSpeed, LeftBaseSpeed, RightBaseSpeed, BackLeftBaseSpeed, BackRightBaseSpeed, TurnSpeed, MaxSpeed;
int Error, PreError, SumError, Kp, Kd, Ki, Kt, KpB, KdB, KiB, KtB;
int L2, R2, BL2, BR2, RefL2, RefR2, RefBL2, RefBR2;
long MotorStop_Delay, Timer, Timer2, Timer3;

#define SW_pin 18
#define No 0
#define Yes 1
#define BrakeSpeedIMU 100
#define BrakeTimeIMU 10
#define WheelDrive 1
int PidStatus = 0;
int CurrentHeading = 0; // Keep track of current heading, 0° initially

void setup() {
  BaseSpeed = 50;
  TurnSpeed = 80;
  MotorStop_Delay = 250;
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
    calibrate_IMU();
    ReadMPU();
  }
}

void InitialSpeed() {
  MaxSpeed = 100;
  Ki = 0;
  KiB = 0;
  Error = 0;
  PreError = 0;
  if(BaseSpeed<=40)
  {
    LeftBaseSpeed = BaseSpeed-1;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 10;       //forward PID
    Kd = 25;
    Kt = 10;
    KpB = 10;       //backward PID
    KdB = 25;
    KtB = 10;
  }
  else if(BaseSpeed<=60)
  {
    LeftBaseSpeed = BaseSpeed- 0.7;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 13;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 13;       //backward PID
    KdB = 30;
    KtB = 10;
  }
  else if(BaseSpeed<=80)
  {
    LeftBaseSpeed = BaseSpeed- 0;
    RightBaseSpeed = BaseSpeed- 0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 19;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 19;       //backward PID
    KdB = 30;
    KtB = 8;
  }
}
