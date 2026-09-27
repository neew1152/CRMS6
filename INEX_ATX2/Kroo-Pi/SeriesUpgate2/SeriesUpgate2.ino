#include <Adafruit_TCS34725.h>
#include <POP32.h>


////////////////////////////////////////////////////////////
// our RGB -> eye-recognized gamma color
byte gammatable[256];

static uint16_t color16(uint16_t r, uint16_t g, uint16_t b) {
  uint16_t _color;
  _color = (uint16_t)(r & 0xF8) << 8;
  _color |= (uint16_t)(g & 0xFC) << 3;
  _color |= (uint16_t)(b & 0xF8) >> 3;
  return _color;
}
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
/////////////////////////////////////////////////////////////



//  Forward and Backward variable
int Speed, SlowSpeed, ACCSpeed, BaseSpeed, TurnSpeed, MaxSpeed, SonarSpeed, DistanceRef;
long LeftBaseSpeed, RightBaseSpeed;


//  Variable sensor
int RefL2, RefL1, RefR1, RefR2, SumError, RefBL2, RefBL1, RefBR1, RefBR2;
int L2, L1, R1, R2, BL2, BL1, BR1, BR2;
int minL2, minL1, minR1, minR2;
int maxL2, maxL1, maxR1, maxR2;

// Variable milis()
long Timer, Timer2, Timer3;

// Variable PID
int Error, PreError, Kp, Kd, Ki, Kt, KpB, KdB, KiB, KtB, BackLeftBaseSpeed, BackRightBaseSpeed, KpChange;

// Sensor IMU
float pvYaw;
uint8_t rxCnt = 0, rxBuf[8];

// Variable knob
int X, Y, grip;

//Variable RGB
int minRGB, maxRGB;


long Sonar;

// Constant
#define PA2 2
#define WheelDrive 1  //0:ขับเคลื่อน 2 ล้อ , 1:ขับเคลื่อน 4 ล้อ
#define breakTime 2
int PidStatus = 0;  //0:ใช้ล้อข้างเดียว 1:ใช้ล้อ 2 ข้าง




void setup() {

  // Perfomance Value Start Program
  Startprogrambeep();
  servo(4, 130);
  servo(5, 0);
  servo(6, 20);
  // Startprogramservo();
  // SetupTCS34725();
  Speed = 60;
  ACCSpeed = 100;
  SlowSpeed = 40;
  BaseSpeed = Speed;
  TurnSpeed = 90;

  zeroYaw();
  InitialSpeed();
  InitialRef();
  InitSerial1();
  oled.text(0, 1, "wellcome to robotics");
  oled.text(1, 2, "sw_ok = Test");
  oled.text(2, 2, "sw_a = no");
  oled.text(3, 2, "sw_b = no");
  oled.show();
  sw_ok_press();
  sound(3000, 100);
  zeroYaw();
  oled.clear();

  // FD2(70,70);
  // delay(1500);
  // ao();

  // distance();
  Can1();
  // Can2();
  // TracJCStop();
  // Trac2Speed(60, 1500);
  //CalibartionRGB();
  //Calibartion();
  /* 
   Grip();
   sound(500,500);
   sound(400,400);
   sound(300,100);
   LedyPut();
   */
  //FunctionJune();
  // Testservo();
  //PointsOne();
  //Trac2Speed(BaseSpeed,500);
  //Trac2SpeedBack(BaseSpeed,200);
  //JuneBack();
  //TracTeacher();
  //TracwhileBack();
  //BackwardSpeedTime(BaseSpeed,2000);
  //TracJCStopBack();
  //TestGyro();
  //ForwardMPU(2000);
  //ForwardSpeedTime(BaseSpeed,2000);
  //Show8Analog();
  //TracPID();
  //TracJCStop();
  //TracSpeedTime(Speed,515);
  //TurnLeftDegree(TurnSpeed,90,0);
  //TurnRightDegree(TurnSpeed,87,2);
  AO();
  while (1)
    ;
}

void loop() {
  /*
  zeroYaw();
  ShowYaw();
  delay(1000);
  */
  //ShowRGB();
  //CalibartionRGB();
  //distance();
}
