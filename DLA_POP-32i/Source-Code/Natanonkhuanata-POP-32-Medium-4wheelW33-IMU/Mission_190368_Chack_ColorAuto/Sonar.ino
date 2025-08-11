
void ShowSoar() {
  Sonar = analog(PA2);
  oled.text(3, 3, "distance= %l", Sonar / 40);
  delay(100);
  oled.show();
}
void ReadSonar() {
  Sonar = analog(PA2) / 40;
}
void BackwardSonar() {
  while (1) {
    ReadSonar();
    Backward();
    if (Sonar == 9) break;
  }
  sound(200, 500);
}
void TracSonar(int Speed,long distance) {
  BaseSpeed = Speed;
  InitialSpeed();
  ReadSonar();
  CalError();
  while (1) {
    TracPID();
    ReadSonar();
    if (Sonar <= distance) break;
  }
}

void ForwardSonar(long distance) {
  BaseSpeed = 40;
  while (1) {
    ReadSonar();
    fd2(BaseSpeed, BaseSpeed);
    if(Sonar <= distance) break;
  }
  MotorStop();
  beep();
}

void LeftSonar(){

}

void RightSonar(long distance){
  while(1){
    SR(40);
    ReadSonar();
    if(Sonar >= distance) break;
  }
  MotorStop();
  beep();
}
