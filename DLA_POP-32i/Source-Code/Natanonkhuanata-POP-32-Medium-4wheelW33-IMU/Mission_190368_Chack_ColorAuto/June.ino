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
        if((BL1==0) && (BR1==0)) break;       
      } 
  } else if ((BL1 == 1) && (BR1 == 0)) {

      while (1) {

        
        motor(1, -Speed);
        motor(2, -Speed);
        motor(3, Speed);
        motor(4, Speed);
        ConvertADCBack();
        if((BL1==0) && (BR1==0)) break;
      }
    }
  MotorStop();
  delay(50);
}
void FunctionJuneBack()
{
  TracJCStopBack();
  JuneBack();
}
void June() {
  //MotorStop();
  InitialSpeed();
  ConvertADC();
  if ((L1 == 0) && (R1 == 1)) {

      while (1) {
        motor(1, -Speed);
        motor(2, -Speed);
        motor(3, Speed);
        motor(4, Speed);
        ConvertADC();
        if((L1==0) && (R1==0)) break;       
      } 
  } else if ((L1 == 1) && (R1 == 0)) {

      while (1) {

        
        motor(1, Speed);
        motor(2, Speed);
        motor(3, -Speed);
        motor(4, -Speed);
        ConvertADC();
        if((L1==0) && (R1==0)) break;
      }
    }
  MotorStop();
  delay(50);
}
void FunctionJune()
{
  TracJCStop();
  June();
}