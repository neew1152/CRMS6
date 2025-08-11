void TracJCStop()  //เดินถึงเส้นและออกจากฟังก์ชัน
{

  BaseSpeed = 30;
  InitialSpeed();
  CalError();
  while (Error < 99) {
    TracPID();
    CalError();
  }
}
void TracSpeedTime(int TracSpeed, int TracTime) {
  int TempSpeed = BaseSpeed;
  StartTimer();
  ForwardSpeedTime(TracSpeed, 100);
  BaseSpeed = TracSpeed;
  InitialSpeed();
  CalError();
  while (ReadTimer() < TracTime) {
    if (Error >= 100) Error = 0;
    TracPID();
    delay(Kt);
    CalError();
  }
  BaseSpeed = TempSpeed;
  InitialSpeed();
}
void Trac2Speed(int Speed, int Time)  //วิ่ง 2 สปีดเพื่อไม่หุ่นยนต์กระดก
{
  TracSpeedTime(Speed, Time);
  TracJCStop();
  June();
}
void Trac2SpeedTime(int TimeSpeed, int TimeSlowSpeed)  //วิ่งด้วยเวลาเเบบ 2 สปีดเพื่อไม่หุ่นยนต์กระดก
{
  TracSpeedTime(Speed, TimeSpeed);
  TracSpeedTime(SlowSpeed, TimeSlowSpeed);
}
void Trac2SpeedTimeACC(int TimeSpeed, int TimeSlowSpeed,int StartTime)  //วิ่งด้วยเวลาเเบบ 2 สปีดเพื่อไม่หุ่นยนต์กระดก
{
  TracSpeedTime(SlowSpeed, StartTime);
  TracSpeedTime(ACCSpeed, TimeSpeed);
  TracSpeedTime(SlowSpeed, TimeSlowSpeed);
}