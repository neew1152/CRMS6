void ConvertADC()
{
  Read4Analog();
  if(L2<RefL2) L2 = 0;else L2 = 1;    //0:ดำ 1:ขาว
  if(L1<RefL1) L1 = 0;else L1 = 1;
  if(R1<RefR1) R1 = 0;else R1 = 1;
  if(R2<RefR2) R2 = 0;else R2 = 1;
}
void CalError() {
  ConvertADC();
  if((L1==0)||(R1==0)) Error = 101;
  else if((L2==0)&&(L1==0)) Error = 102;  
  else if((R2==0)&&(R1==0)) Error = 103;
  else if((L2==1)&&(L1==1)&&(R1==1)&&(R2==0)) Error = -1;    
  else if((L2==1)&&(L1==1)&&(R1==1)&&(R2==1)) Error = 0; 
  else if((L2==0)&&(L1==1)&&(R1==1)&&(R2==1)) Error = 1; 
}
void TracPID()  {
  int Output, LeftOutput, RightOutput;
  Output = (Kp*Error) + (Ki*SumError) + (Kd*(Error-PreError));
  LeftOutput = LeftBaseSpeed + Output;
  RightOutput = RightBaseSpeed - Output;
  if(PidStatus!=0)
  {
    LeftOutput = constrain(LeftOutput,-MaxSpeed,MaxSpeed);
    RightOutput = constrain(RightOutput,-MaxSpeed,MaxSpeed);
  }
  else
  {
    LeftOutput = constrain(LeftOutput,0,MaxSpeed);
    RightOutput = constrain(RightOutput,0,MaxSpeed);
  }
  motor(1,LeftOutput);
  motor(2,LeftOutput);
  motor(3,RightOutput);
  motor(4,RightOutput);
  PreError = Error;
  SumError += Error;
}




///////////////////////////////////////////////////////////////////////////

void ConvertADCBack()
{
  Read4BackAnalog();
  if(BL2<RefBL2) BL2 = 0;else BL2 = 1;  //0:ดำ 1:ขาว
  if(BL1<RefBL1) BL1 = 0;else BL1 = 1;
  if(BR1<RefBR1) BR1 = 0;else BR1 = 1;
  if(BR2<RefBR2) BR2 = 0;else BR2 = 1;
}
void CalErrorBack() {
  ConvertADCBack();
  if((BL1==0)||(BR1==0)) Error = 100;
  else if(BR2==0) Error = -1; 
  else if(BL2==0) Error = 1;
  else Error = 0;   
}
void TracPIDBack()  {
  int Output, LeftOutput, RightOutput;
  Output = (KpB*Error) + (KiB*SumError) + (KdB*(Error-PreError));
  LeftOutput = BackLeftBaseSpeed + Output;
  RightOutput = BackRightBaseSpeed - Output;
  if(PidStatus!=0)
  {
    LeftOutput = constrain(LeftOutput,-MaxSpeed,MaxSpeed);
    RightOutput = constrain(RightOutput,-MaxSpeed,MaxSpeed);
  }
  else 
  {
    LeftOutput = constrain(LeftOutput,0,MaxSpeed);
    RightOutput = constrain(RightOutput,0,MaxSpeed);
  }
  motor(1,-LeftOutput);
  motor(2,-LeftOutput);
  motor(3,-RightOutput);
  motor(4,-RightOutput);
  PreError = Error;
  SumError += Error;
}