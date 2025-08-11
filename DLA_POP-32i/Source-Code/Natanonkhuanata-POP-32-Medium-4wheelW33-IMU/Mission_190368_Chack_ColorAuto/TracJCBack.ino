void TracJCStopBack() //แทกหลังถึงเส้นและออกจากฟังก์ชัน
{  
  //BackwardSpeedTime(BaseSpeed,100);
  BaseSpeed = 30;
  InitialSpeed();
  while(Error<99)
  {
    TracPIDBack();
    CalErrorBack();
  }
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
void Trac2SpeedBack(int Speed,int Time)
{
  TracSpeedTimeBack(Speed,Time);
  FunctionJuneBack();

}
void TracwhileBack(int Time)
{
  TracSpeedTimeBack(Speed,Time);
  InitialSpeed();
  ConvertADCBack();
  while((BL1==1) && (BR1==1))
  {
    Backward();
    ConvertADCBack();
    if((BL1==0) || (BR1==0))break;
  }
}