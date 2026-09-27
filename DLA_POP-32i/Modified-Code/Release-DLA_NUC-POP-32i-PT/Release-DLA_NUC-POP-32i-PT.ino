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
  TurnSpeed = 70;
  MotorStop_Delay = 100;
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

void InitialSpeed() {
    MaxSpeed = 100;
    Ki = 0;
    KiB = 0;
    Error = 0;
    PreError = 0;

    // Reference tuning at BaseSpeed = 50
    float refSpeed = 50;
    float refKp = 10;
    float refKd = 25;
    float refKt = 10;

    // Scaling factor based on current BaseSpeed
    float scale = BaseSpeed / refSpeed;

    // Adjust base motor speeds
    LeftBaseSpeed = BaseSpeed - 0.1 * scale;
    RightBaseSpeed = BaseSpeed - 0 * scale;
    BackLeftBaseSpeed = BaseSpeed - 0 * scale;
    BackRightBaseSpeed = BaseSpeed - 0 * scale;

    // Forward PID
    Kp = refKp * scale;
    Kd = refKd * scale;
    Kt = refKt * scale;

    // Backward PID (same scaling)
    KpB = refKp * scale;
    KdB = refKd * scale;
    KtB = refKt * scale;
}
