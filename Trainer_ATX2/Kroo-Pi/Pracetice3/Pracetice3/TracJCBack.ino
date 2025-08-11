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
  delay(100);
  ForwardSpeedTime(SlowSpeed,200);
  MotorStop();
}
void TracJC1Back() //ถอยถึงเส้นจูนและถอยแบบไม่จูน ไม่หยุด
{
  TracJCBlackBack();
  MotorStop();
  delay(100);
  ForwardSpeedTime(SlowSpeed,200);
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
