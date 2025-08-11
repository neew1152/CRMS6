void MotorStop() {
  AO();
  delay(MotorStop_Delay);
}

void Left(int Speed , int Time)
{
  MotorStop();
  SL(Speed);
  delay(Time);
  MotorStop();
}

void Right(int Speed , int Time)
{
  MotorStop();
  SR(Speed);
  delay(Time);
  MotorStop();
}

void TurnLeftDelay(int Speed , int Time)
{
  TL(Speed);
  delay(Time);
}

void TurnRightDelay(int Speed , int Time)
{
  TR(Speed);
  delay(Time);
}

void CurveLeftDegree(int TurnSpeed, float Degree, int Origin)  //โค้งซ้ายใช้เข็มทิศ Degree 0-359
{                                                              //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้น
  int Status = 0;
  if (Origin != 1) zeroYaw();
  if (WheelDrive == 0) tl(TurnSpeed);
  else TL(TurnSpeed);
  for (int i = 0; i < 10; i++) {
    getIMU();
  }
  while (Status == 0) {
    if (getIMU()) {
      if ((pvYaw >= Degree - 25) && (pvYaw <= Degree - 0)) {
        Status = 1;
      } else if (Degree == 0) {
        if ((pvYaw >= 345) && (pvYaw <= 360)) {
          Status = 1;
        }
      }
    }
  }
}

void CurveRightDegree(int TurnSpeed, float Degree, int Origin)  //โค้งขวาใช้เข็มทิศ 0-359
{                                                               //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  int Status = 0;
  if (Origin != 1) zeroYaw();
  if (WheelDrive == 0) tr(TurnSpeed);
  else TR(TurnSpeed);
  for (int i = 0; i < 10; i++) {
    getIMU();
  }
  while (Status == 0) {
    if (getIMU()) {
      if (Origin == 2) {
        if (Degree == 0) break;
        if ((360 - pvYaw >= Degree - 25) && (360 - pvYaw <= Degree - 0)) {
          Status = 1;
        }
      } else if ((pvYaw <= Degree + 25) && (pvYaw >= Degree)) {
        Status = 1;
      } else if (Degree >= 330) {
        if ((pvYaw <= Degree - 335) || (pvYaw >= 335)) Status = 1;
      }
    }
  }
}

void CurveLeftDegreeBack(int TurnSpeed, float Degree, int Origin)  //ถอยโค้งซ้ายใช้เข็มทิศ Degree 0-359
{                                                                  //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้น
  int Status = 0;
  if (Origin != 1) zeroYaw();
  if (WheelDrive == 0) {
    motor(1, -TurnSpeed);
    motor(2, 0);
  } else {
    motor(1, -TurnSpeed);
    motor(2, -TurnSpeed);
    motor(3, 0);
    motor(4, 0);
  }
  for (int i = 0; i < 10; i++) {
    getIMU();
  }
  while (Status == 0) {
    if (getIMU()) {
      if ((pvYaw >= Degree - 25) && (pvYaw <= Degree - 0)) {
        Status = 1;
      } else if (Degree == 0) {
        if ((pvYaw >= 345) && (pvYaw <= 360)) {
          Status = 1;
        }
      }
    }
  }
}

void CurveRightDegreeBack(int TurnSpeed, float Degree, int Origin)  //ถอยโค้งขวาใช้เข็มทิศ 0-359
{                                                                   //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  int Status = 0;
  if (Origin != 1) zeroYaw();
  if (WheelDrive == 0) {
    motor(1, 0);
    motor(2, -TurnSpeed);
  } else {
    motor(1, 0);
    motor(2, 0);
    motor(3, -TurnSpeed);
    motor(4, -TurnSpeed);
  }
  for (int i = 0; i < 10; i++) {
    getIMU();
  }
  while (Status == 0) {
    if (getIMU()) {
      if (Origin == 2) {
        if (Degree == 0) break;
        if ((360 - pvYaw >= Degree - 25) && (360 - pvYaw <= Degree - 0)) {
          Status = 1;
        }
      } else if ((pvYaw <= Degree + 25) && (pvYaw >= Degree)) {
        Status = 1;
      } else if (Degree >= 330) {
        if ((pvYaw <= Degree - 335) || (pvYaw >= 335)) Status = 1;
      }
    }
  }
}

void TestGyro()
{
  TracDegreeSpeedTime(BaseSpeed,0,1000,0); MotorStop();
  TracDegreeSpeedTime(BaseSpeed,90,1000,0); MotorStop();
  TracDegreeSpeedTime(BaseSpeed,180,1000,0); MotorStop();
  TracDegreeSpeedTime(BaseSpeed,270,1000,0); MotorStop();
  TracDegreeSpeedTimeBack(BaseSpeed,270,1000,0); MotorStop();
  TracDegreeSpeedTimeBack(BaseSpeed,180,1000,0); MotorStop();
  TracDegreeSpeedTimeBack(BaseSpeed,90,1000,0); MotorStop();
  TracDegreeSpeedTimeBack(BaseSpeed,0,1000,0); MotorStop();
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
  FD2(LeftBaseSpeed, RightBaseSpeed);
  delay(TimeDelay);
  BaseSpeed = Speed;
  InitialSpeed();
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