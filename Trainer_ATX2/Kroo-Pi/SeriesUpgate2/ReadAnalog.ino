/* 
     Show Value Sensor   

     Analog 2 is Altarsonic

*/

void Read4Analog() {
  L2 = analog(0);
  L1 = analog(1);
  R1 = analog(3);
  R2 = analog(4);
}
void Read4BackAnalog() { 
  BL1 = analog(5);
  BL2 = analog(6);
  BR1 = analog(7);
  BR2 = analog(8);
}