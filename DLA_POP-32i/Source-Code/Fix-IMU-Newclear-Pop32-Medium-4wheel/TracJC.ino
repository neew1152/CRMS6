void TracJCSonar(int Aaa)  //เดินถึงเส้นและออกจากฟังก์ชัน
{
  Sonar = analog(2)/40;
  ForwardSpeed(20);
  while (1) {
    Sonar = analog(2)/40;
    if (Sonar <= Aaa)  break; 
  }
  MotorStop();
}

void TracJCStop() //เดินถึงเส้นและออกจากฟังก์ชัน
{  
  ForwardSpeedTime(BaseSpeed,100);
  InitialSpeed();
  CalError();
  while(Error<99)
  {
    TracPID();
    StartTimer();
    while((ReadTimer()<Kt)&&(Error<100))
    {
      CalError();
    }
  }
}
void TracJC() //เดินถึงเส้นที่ไม่ใช่ขอบและถอยแบบจูน
{
  TracJCBlack();
  MotorStop();
  //delay(100);
  BackwardBalanceF();
  BackwardSpeedTime(SlowSpeed,120);
}
void TracJC0() //เดินถึงเส้นและถอยแบบไม่จูน
{
  TracJCStop();
  MotorStop();
  //delay(100);
  BackwardSpeedTime(SlowSpeed,220);
  MotorStop();
}
void TracJC1() //เดินถึงเส้นจูนและถอยแบบไม่จูน
{
  TracJCBlack();
  MotorStop();
  //delay(100);
  BackwardSpeedTime(SlowSpeed,220);
}
void TracJCBlack() //วิ่งเข้าหลุมดำหรือพื้นที่วางสีเขียว
{
  TracJCStop();
  ForwardSpeedTime(SlowSpeed,1);
  ConvertADC();
  while((L2==1)&&(R2==1)) {ConvertADC();}
  MotorStop();  
  if((L2==0)&&(R2==1)) //เจอดำข้างซ้าย
  {     
      SL(SlowSpeed);
      while(R2==1) {ConvertADC();}
      delay(10);
  }
  else if((L2==1)&&(R2==0))  //เจอดำข้างขวา
  {
      SR(SlowSpeed);
      while(L2==1) {ConvertADC();}
      delay(10);
   }
  MotorStop();
}
void TracJCForward() //เดินถึงขอบสะพานบนและถอยเดินตรง
{
  TracJCStop();
  ForwardSpeedTime(Speed,300);
}
void TracJCSlowStop() 
{
  BaseSpeed = SlowSpeed;
  TracJCStop();
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracJCSpeedTime(int MotorSpeed, int TimeDelay) {
  BaseSpeed = MotorSpeed;
  TracJCStop();
  Forward();
  delay(TimeDelay);
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracSpeedTime(int TracSpeed, int TracTime) {
  int TempSpeed=BaseSpeed;
  StartTimer();
  ForwardSpeedTime(TracSpeed,100);
  BaseSpeed = TracSpeed;
  InitialSpeed();
  CalError();
  while(ReadTimer()<TracTime)
  {
    if(Error>=100) Error = 0;
    TracPID();
    delay(Kt);
    CalError();
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
}
void TracJCSpeedStop() 
{
  BaseSpeed = ACCSpeed;
  TracJCStop();
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracACC(int MotorSpeed,int Time)
{
  ForwardSpeedTime(MotorSpeed,100);
  TracSpeedTime(MotorSpeed,Time-100);
}
void TracJC0ACCTime(int MotorSpeed,int Time)
{
  TracACC(MotorSpeed,Time);
  TracJC0();
}
void TracJC1ACCTime(int MotorSpeed,int Time)
{
  TracACC(MotorSpeed,Time);
  TracJC1();
}
void TracJCACCTime(int MotorSpeed,int Time)
{
  TracACC(MotorSpeed,Time);
  TracJC();
}
void TracJCStopACCTime(int MotorSpeed,int Time)
{
  TracACC(MotorSpeed,Time);
  TracJCStop();
}

void TracJCStopBack() //แทกหลังถึงเส้นและออกจากฟังก์ชัน
{  
  //BackwardSpeedTime(BaseSpeed,100);
  InitialSpeed();
  CalErrorBack();
  while(Error<99)
  {
    TracPIDBack();
    StartTimer();
    while((ReadTimer()<Kt)&&(Error<100))
    {
      CalErrorBack();
    }
  }
}
void TracJC0Back() //เดินถึงเส้นและถอยแบบไม่จูน
{
  TracJCStopBack();
  MotorStop();
  //delay(100);
  ForwardSpeedTime(SlowSpeed,220);
  MotorStop();
}
void TracJC1Back() //ถอยถึงเส้นจูนและถอยแบบไม่จูน
{
  TracJCBlackBack();
  MotorStop();
  //delay(100);
  ForwardSpeedTime(SlowSpeed,220);
}
void TracJCBlackBack() //ถอยหลังเข้าหลุมดำหรือพื้นที่วางสีเขียว
{
  TracJCStopBack();
  BackwardSpeedTime(SlowSpeed,1);
  ConvertADCBack();
  while((BL2==1)&&(BR2==1)) {ConvertADCBack();}
  MotorStop(); 
  if((BL2==0)&&(BR2==1)) //เจอดำข้างซ้าย
  {     
      SR(SlowSpeed);
      while(BR2==1) {ConvertADCBack();}
      delay(10);
  }
  else if((BL2==1)&&(BR2==0))  //เจอดำข้างขวา
  {
      SL(SlowSpeed);
      while(BL2==1) {ConvertADCBack();}
      delay(10);
   }
  MotorStop();
}
void TracSpeedTimeBack(int TracSpeed, int TracTime) {
  int TempSpeed=BaseSpeed;
  StartTimer();
  BackwardSpeedTime(TracSpeed,100);
  BaseSpeed = TracSpeed;
  InitialSpeed();
  CalError();
  while(ReadTimer()<TracTime)
  {
    if(Error>=100) Error = 0;
    TracPIDBack();
    delay(Kt);
    CalErrorBack();
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
}
void TracACCBack(int MotorSpeed,int Time)
{
  BackwardSpeedTime(MotorSpeed,100);
  TracSpeedTimeBack(MotorSpeed,Time-100); 
}
void TracJC0ACCBackTime(int MotorSpeed,int Time)
{
  TracACCBack(MotorSpeed,Time);
  TracJC0Back();
}
void TracJC1ACCBackTime(int MotorSpeed,int Time)
{
  TracACCBack(MotorSpeed,Time);
  TracJC1Back();
}
void TracJCStopACCBackTime(int MotorSpeed,int Time)
{
  TracACCBack(MotorSpeed,Time);
  TracJCStopBack();
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

