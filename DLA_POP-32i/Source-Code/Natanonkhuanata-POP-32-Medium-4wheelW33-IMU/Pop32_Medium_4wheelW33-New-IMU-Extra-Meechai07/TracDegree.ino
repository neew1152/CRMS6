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
void TracDegreeSpeedTime(int MotorSpeed ,int Degree ,int Time ,int PIDtemp) 
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
void TracDegreeSpeedTimeBack(int MotorSpeed ,int Degree ,int Time ,int PIDtemp) 
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
  TracDegreeSpeedTimeBack(MotorSpeed,Degree,Time,PIDtemp);
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
  TracDegreeSpeedTime(MotorSpeed,Degree,Time,PIDtemp);
  BaseSpeed = TempSpeed;
  InitialSpeed();
  PidStatus=TempPidStatus;
}
