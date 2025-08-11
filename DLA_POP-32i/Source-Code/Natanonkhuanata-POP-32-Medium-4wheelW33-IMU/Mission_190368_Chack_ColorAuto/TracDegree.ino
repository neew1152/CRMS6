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