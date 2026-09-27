#include <ATX2.h>
int L3, L2, L1, C, R1, R2, R3;
int RefL3, RefL2, RefL1, RefC, RefR1, RefR2, RefR3;
int Speed, ACCSpeed, SlowSpeed, TurnSpeed, LeftSpeed, RightSpeed;
long Timer0, StartTimer0, Timer1, StartTimer1; 
int Kp, Ki, Kd, Error, PreError, Integral, MaxSpeed;

void setup() {
  Speed = 60;
  ACCSpeed = 70;
  SlowSpeed = 50;
  TurnSpeed = 60;
  XIO();
  beep(1);
  ShowLCD();
//  sw_ok_press();
//  beep(2);
//  Show7ADC();
  Initial7ADC();
  sw_ok_press();
  beep(2);

  Forward(Speed, 250);
  TracJC(Speed, 100);
  TracJC(Speed, 150);
  TracJC(Speed, 100);
  TurnLeft();
  TracNormalTime(Speed, 900);

  Backward(Speed, 250);
  UTurn();
  TracJC(Speed, 100);
  TurnRight();
  TracJC(Speed, 150);
  HalfTurnLeft();
  Forward(Speed, 100);
  TracJC(Speed, 100);
  HalfTurnRight();
  Forward(Speed, 100);
  TracNormalTime(Speed, 500);

  UTurn();
  TracJC(Speed, 100);
  TurnLeft();
  TracJC(Speed, 100);
  TurnRight();

  Finish();
}

void loop() {

}