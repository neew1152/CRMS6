#include <ATX2.h>
int L3, L2, L1, C, R1, R2, R3;
int RefL3, RefL2, RefL1, RefC, RefR1, RefR2, RefR3;

void setup() {
  XIO();
  beep(1);
  ShowLCD();
  sw_ok_press();
  beep(2);
  Show7ADC();
}

void loop() {
  // put your main code here, to run repeatedly:

}