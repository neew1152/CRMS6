void JuneBack() {
  //MotorStop();
  InitialSpeed();
  ConvertADCBack();
  if ((BL1 == 0) && (BR1 == 1)) {

    while (1) {
      motor(1, Speed);
      motor(2, Speed);
      motor(3, -Speed);
      motor(4, -Speed);
      ConvertADCBack();
      if ((BL1 == 0) && (BR1 == 0)) break;
    }
  } else if ((BL1 == 1) && (BR1 == 0)) {

    while (1) {


      motor(1, -Speed);
      motor(2, -Speed);
      motor(3, Speed);
      motor(4, Speed);
      ConvertADCBack();
      if ((BL1 == 0) && (BR1 == 0)) break;
    }
  }
}
void FunctionJuneBack() {
  TracJCStopBack();
  JuneBack();
}
void June() {
  //MotorStop();
  // delay(50);
  InitialSpeed();
  ConvertADC();
  if ((L1 == 0) && (R1 == 1)) {

    while (1) {
      motor(1, -60);
      motor(2, -60);
      motor(3, 60);
      motor(4, 60);
      ConvertADC();
      if ((L1 == 0) && (R1 == 0)) break;
    }
  } else if ((L1 == 1) && (R1 == 0)) {

    while (1) {


      motor(1, 60);
      motor(2, 60);
      motor(3, -60);
      motor(4, -60);
      ConvertADC();
      if ((L1 == 0) && (R1 == 0)) break;
    }
  }
  // delay(50);
}
void FunctionJune() {
  TracJCStop();
  June();
}