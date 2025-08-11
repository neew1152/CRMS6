void PutCan() {
  CalibartionRGB();
  MotorStop();
  if (Color == 1) {
    TL(TurnSpeed);
    delay(120);
    MotorStop();
    TracSonar(40, 9);
    MotorStop();
    downhelp();
    MotorStop();
    Put();
    MotorStop();
    sound(1000, 500);
    MotorStop();
    BackwardSpeedTime(25, 200);
    MotorStop();
    ReadyPut();
    MotorStop();
  } else if (Color == 2) {  //Yellow
    Count++;
    if (Count == 1) {
      TracSonar(SlowSpeed, 6);
      MotorStop();
      TR(50);
      delay(9);
      MotorStop();
      ReadyPut_01();
      Put();
    } else {
      TracSonar(25, 5);
      MotorStop();
      TR(50);
      delay(69);
      MotorStop();
      ReadyPut_02();
      Put_02();
    }
  } else if (Color == 3) {
    MotorStop();
    TR(TurnSpeed);
    delay(120);
    MotorStop();
    TracSonar(40, 9);
    MotorStop();
    downhelp();
    MotorStop();
    Put();
    MotorStop();
    sound(1000, 500);
    MotorStop();
    BackwardSpeedTime(25, 200);
    MotorStop();
    ReadyPut();
    MotorStop();
  }
  /*
  Trac2SpeedBack(Speed,500);
  ForwardSpeedTime(30,400);
  MotorStop();
  TurnLeftDegree(TurnSpeed,90,0);
  MotorStop();
  FunctionJuneBack();
  MotorStop();
  */
}