void FW(int MotorSpeed,int T)
{
  while(1){
  InitialSpeed();
  BaseSpeed=MotorSpeed;
  ConvertADC();
  float k = 1;
  int SP_M1 = constrain(val_S1 * k, 0, LeftBaseSpeed);
  int SP_M2 = constrain(val_S2 * k, 0, RightBaseSpeed);
  if(val_S1>=70 && val_S2>=70) {FD2(SP_M1,SP_M2);}

  else if((val_S1>=60&&val_S1<70)) {FD2(SP_M1*0.8,SP_M2);}
  else if((val_S2>=60&&val_S2<70)) {FD2(SP_M1,SP_M2*0.8);}
  else if((val_S1>=50&&val_S1<60)) {FD2(SP_M1*0.7,SP_M2);}
  else if((val_S2>=50&&val_S2<60)) {FD2(SP_M1,SP_M2*0.7);}
  else if((val_S1>=40&&val_S1<50)) {FD2(SP_M1*0.6,SP_M2);}
  else if((val_S2>=40&&val_S2<50)) {FD2(SP_M1,SP_M2*0.6);}
  else if((val_S1>=30&&val_S1<40)) {FD2(SP_M1*0.5,SP_M2);}
  else if((val_S2>=30&&val_S2<40)) {FD2(SP_M1,SP_M2*0.5);}
  else if((val_S1<30&&val_S2<30)) {FD2(SP_M1*0.4,SP_M2*0.4);}

  if(L1==0||R1==0){break;}

  //(val_S1<30||val_S2<30)||
  else if((val_L1<=40||val_R1<=40)){break;}
  
  }
  // MotorStop();
  if(MotorSpeed==Speed)BackwardDelay(50,20);
  Balance();
  MotorStop();
  BackwardDelay(60,T);
  MotorStop();delay(30);
}

void FL(int MotorSpeed,int T)
{
  FW(MotorSpeed,T);TurnLeftDegree(100,80,2);
}
void FR(int MotorSpeed,int T)
{
  FW(MotorSpeed,T);TurnRightDegree(100,80,2);
}
void TT(int MotorSpeed,int Time)  //แทกตามเวลาที่กำหนด
{
  int Status=0;
  StartTimer0();
  while(Status==0)
  {
  InitialSpeed();
  BaseSpeed=MotorSpeed;
  ConvertADC();
  float k = 1;
  int SP_M1 = constrain(val_S1 * k, 0, LeftBaseSpeed);
  int SP_M2 = constrain(val_S2 * k, 0, RightBaseSpeed);
  if(val_S1>=70 && val_S2>=70) {FD2(SP_M1,SP_M2);}

  else if((val_S1>=60&&val_S1<70)) {FD2(SP_M1*0.8,SP_M2);}
  else if((val_S2>=60&&val_S2<70)) {FD2(SP_M1,SP_M2*0.8);}
  else if((val_S1>=50&&val_S1<60)) {FD2(SP_M1*0.7,SP_M2);}
  else if((val_S2>=50&&val_S2<60)) {FD2(SP_M1,SP_M2*0.7);}
  else if((val_S1>=40&&val_S1<50)) {FD2(SP_M1*0.6,SP_M2);}
  else if((val_S2>=40&&val_S2<50)) {FD2(SP_M1,SP_M2*0.6);}
  else if((val_S1>=30&&val_S1<40)) {FD2(SP_M1*0.5,SP_M2);}
  else if((val_S2>=30&&val_S2<40)) {FD2(SP_M1,SP_M2*0.5);}
  else if((val_S1<30&&val_S2<30)) {FD2(SP_M1*0.4,SP_M2*0.4);}

  // if(L1==0||R1==0){break;}

  //(val_S1<30||val_S2<30)||
  // if((val_L1<=40||val_R1<=40)){break;}
  
    ReadTimer0();
    if(Timer0>=Time) Status=1;
  }
}