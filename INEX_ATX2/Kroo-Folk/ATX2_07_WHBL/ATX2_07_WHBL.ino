#include <ATX2.h>
int L3, L2, L1, C, R1, R2, R3;
int RefL3, RefL2, RefL1, RefC, RefR1, RefR2, RefR3;
int Speed, ACCSpeed, SlowSpeed, TurnSpeed, LeftSpeed, RightSpeed;
long Timer0, StartTimer0, Timer1, StartTimer1; 
int Kp, Ki, Kd, Error, PreError, Integral, MaxSpeed;
int SonarBlock;

void setup() {
  Speed = 60;
  ACCSpeed = 70;
  SlowSpeed = 50;
  TurnSpeed = 60;
  XIO();
  beep(1);
  Initial7ADC();
  OK();
  beep(2);

  B3();
  B2();
  Bcan1();
  B4();
  /*B5();
  B7();
  B6();
  B8();
  B9();
  Bcan10();
  B12();
  Bcan11();
  Bcan13();*/

  Finish();
}

void loop() {

}