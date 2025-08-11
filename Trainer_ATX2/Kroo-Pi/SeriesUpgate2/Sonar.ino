
void distance() {
  oled.clear();
  while (1) {
    Sonar = analog(PA2);
    oled.text(3, 3, "distance= %l", Sonar / 40);
    oled.show();
  }
}
void ReadSonar() {
  Sonar = analog(PA2);
}
void BackwardSonar() {
  while (1) {
    ReadSonar();
    Backward();
    if (Sonar >= 9) break;
  }
  sound(200, 500);
}
void TracJCSonar(int Aaa)  //เดินถึงเส้นและออกจากฟังก์ชัน
{
  Sonar = analog(2)/40;
  FD2(40, 40);
  while (1) {
    Sonar = analog(2)/40;
    if (Sonar <= Aaa)  break; 
  }
  MotorStop();
}