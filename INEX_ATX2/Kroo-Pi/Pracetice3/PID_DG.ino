void ConvertADC()
{
  Read5Analog();
  if(L2<RefL2) L2 = 0;else L2 = 1;    //0:ดำ 1:ขาว
  if(L1<RefL1) L1 = 0;else L1 = 1;
  if(R1<RefR1) R1 = 0;else R1 = 1;
  if(R2<RefR2) R2 = 0;else R2 = 1;
}
void CalError() {
  ConvertADC();
  if((L1==0||R1==0)) Error = 100;
  else if((L2==1)&&(L1==1)&&(R1==1)&&(R2==0)) Error = -1;
  else if((L2==1)&&(L1==1)&&(R1==0)&&(R2==0)) Error = -2;
  else if((L2==1)&&(L1==1)&&(R1==0)&&(R2==1)) Error = -3;
  else if((L2==1)&&(L1==0)&&(R1==0)&&(R2==1)) Error = 0;
  else if((L2==1)&&(L1==0)&&(R1==1)&&(R2==1)) Error = 3; 
  else if((L2==0)&&(L1==0)&&(R1==1)&&(R2==1)) Error = 2;
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
  if((BL1==0)&&(BR1==0)) Error = 100;
  else if(BL1==0) Error = 101;
  else if(BR1==0) Error = 102;
  else if(BR2==0) Error = -1; 
  else if(BL2==0) Error = 1;
  else Error = 0;   
}
void TracPIDBack()  {
  int Output, LeftOutput, RightOutput;
  Output = (KpB*Error) + (KiB*SumError) + (KdB*(Error-PreError));
  LeftOutput = BackLeftBaseSpeed + Output;
  RightOutput = BackRightBaseSpeed - Output;
  LeftOutput = constrain(LeftOutput,-MaxSpeed,MaxSpeed);
  RightOutput = constrain(RightOutput,-MaxSpeed,MaxSpeed);
  motor(1,-LeftOutput);
  motor(2,-LeftOutput);
  motor(3,-RightOutput);
  motor(4,-RightOutput);
  PreError = Error;
  SumError += Error;
}


bool CalErrorGyro(int Degree)
{
  if(getIMU()) 
  {
    Error = pvYaw-Degree;
    if(Error>180) Error = Error-360;
    else if(Error<-180) Error = Error+360;
    Error = Error/5;
    return true;
  }
  else return false; 
}
bool CalErrorGyroBack(int Degree)
{
  if(getIMU()) 
  {
    Error = Degree-pvYaw;
    if(Error>180) Error = Error-360;
    else if(Error<-180) Error = Error+360;
    Error = Error/5;
    return true;
  }
  return false;
}
void TDT(int MotorSpeed ,int Degree ,int Time ,int PIDtemp) 
{  
  int TempSpeed=BaseSpeed;
  int TempPidStatus=PidStatus;
  
  PidStatus=PIDtemp;
  StartTimer();
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyro(Degree);
  while(ReadTimer()<Time)
  {
    TracPID();
    StartTimer3();
    while((ReadTimer3()<Kt))
    {
      CalErrorGyro(Degree);
    }
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus=TempPidStatus;
}
void TDTB(int MotorSpeed ,int Degree ,int Time ,int PIDtemp) 
{  
  int TempSpeed=BaseSpeed;
  int TempPidStatus=PidStatus;

  PidStatus=PIDtemp;
  StartTimer();
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyroBack(Degree);
  while(ReadTimer()<Time)
  {
    TracPIDBack();
    StartTimer3();
    while((ReadTimer3()<Kt))
    {
      CalErrorGyroBack(Degree);
    }
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus=TempPidStatus;
}
void SpinDegree(int MotorSpeed ,int Degree ,int PIDtemp) 
{  
  int TempSpeed=BaseSpeed;
  int TempPidStatus=PidStatus;
  int Status=0;

  MotorStop();
  PidStatus=PIDtemp;
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyro(Degree);
  while(Status==0)
  {
    TracPID();
    StartTimer3();
    while((ReadTimer3()<Kt)&&(Status==0))
    {
      if(CalErrorGyro(Degree)) {if(abs(Error)<=3) Status = 1;}
    }  
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus=TempPidStatus;
  MotorStop();
}
void SpinDegreeBack(int MotorSpeed ,int Degree ,int PIDtemp)  
{  
  int TempSpeed=BaseSpeed;
  int TempPidStatus=PidStatus;
  int Status=0;

  MotorStop();
  PidStatus=PIDtemp;
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyroBack(Degree);
  while(Status==0)
  {
    TracPIDBack();
    StartTimer3();
    while((ReadTimer3()<Kt)&&(Status==0))
    {
      if(CalErrorGyroBack(Degree)) {if(abs(Error)<=3) Status = 1;}
    }  
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus=TempPidStatus;
  MotorStop();
}
void TracJCDegree(int MotorSpeed ,int Degree ,int Time ,int PIDtemp) 
{  
  int TempSpeed=BaseSpeed;
  int TempPidStatus=PidStatus;
  
  PidStatus=PIDtemp;
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyro(Degree);
  ConvertADC();
  while(C==1)
  {
    TracPID();
    StartTimer3();
    while((ReadTimer3()<Kt))
    {
      CalErrorGyro(Degree);
    }
    ConvertADC();
  }
  MotorStop();
  TDTB(MotorSpeed,Degree,Time,PIDtemp);
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus=TempPidStatus;
}
void TracJCDegreeBack(int MotorSpeed ,int Degree ,int Time ,int PIDtemp) 
{  
  int TempSpeed=BaseSpeed;
  int TempPidStatus=PidStatus;

  PidStatus=PIDtemp;
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  CalErrorGyroBack(Degree);
  ConvertADCBack();
  while((BL1==1)&&(BR1==1))
  {
    TracPIDBack();
    StartTimer3();
    while((ReadTimer3()<Kt))
    {
      CalErrorGyroBack(Degree);
    }
    ConvertADCBack();
  }
  MotorStop();
  TDT(MotorSpeed,Degree,Time,PIDtemp);
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus=TempPidStatus;
}
