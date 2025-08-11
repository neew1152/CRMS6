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
int Color,Count;

long Sonar;

// Constant
#define PA2 2
#define WheelDrive 1  //0:ขับเคลื่อน 2 ล้อ , 1:ขับเคลื่อน 4 ล้อ
#define breakTime 50
int PidStatus = 0;  //0:ใช้ล้อข้างเดียว 1:ใช้ล้อ 2 ข้าง




void setup() {

  // Perfomance Value Start Program
  Startprogrambeep();
  Startprogramservo();
  SetupTCS34725();
  Speed = 60;
  ACCSpeed = 60;
  SlowSpeed = 30;
  BaseSpeed = Speed;
  TurnSpeed = 90;

  InitialSpeed();
  InitialRef();
  oled.text(0, 1, "wellcome to robotics");
  oled.text(1, 2, "sw_ok=servo1");
  oled.text(2, 2, "sw_a=servo2");
  oled.text(3, 2, "sw_b=servo3");
  oled.show();
  sound(3000, 100);
  oled.clear();
    
    
  //Auto_zero();
  //dGS_Left(TurnSpeed,90,1);
    //dGS(270);
  //ReadyPut_02();
  //dGS_Right_Main(TurnSpeed,270,0);
  //TracSpeedTime(ACCSpeed,500);
  //dGS_box(50, 338 , 1 , 2);
  //TurnRightDegree(TurnSpeed,270,1);
  //dGS_Left(90,0,1.5);
  /*
  SR(TurnSpeed);
  Trac2SpeedBack(Speed, 500);
  ForwardSpeedTime(30, 400);
  MotorStop();
  TurnLeftDegree(TurnSpeed, 90 - pvYaw, 0);
  MotorStop();
  FunctionJuneBack();
  MotorStop();
  */
  //ReadyPut_01();
  //TestSpeed();
  //TracSonar(10.0);
  //GoCan1();
  //GoCan2();
  //Put();
  //GoPoints1();
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
  //Testservo();
  //PointsOne();
  //Trac2Speed(BaseSpeed,500);
  //Backward2Speed(200);
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
  //AO();while(1);
}

void loop() {
  /*
  zeroYaw();
  ShowYaw();
  delay(1000);
  */
  //ShowRGB();
  //CalibartionRGB();
  //ShowSoar();
  Auto_zero();
  sw_ok_press();
  beep();
  GoCan1();
  Checkpont_01();
  GoCan2();
  Checkpoint_02();
  AO();while (1);
}
