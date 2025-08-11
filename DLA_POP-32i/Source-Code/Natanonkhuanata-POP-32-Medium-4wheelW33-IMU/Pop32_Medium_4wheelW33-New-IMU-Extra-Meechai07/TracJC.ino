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
