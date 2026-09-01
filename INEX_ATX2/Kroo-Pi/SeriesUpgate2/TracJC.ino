void TracJCStop()  //เดินถึงเส้นและออกจากฟังก์ชัน
{

  BaseSpeed = 40;
  InitialSpeed();
  CalError();
  while (Error < 99) {
    TracPID();
    CalError();
  }
  ao();
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
  TracSpeedTime(40,20);
  // TracJCStop();
}
void Trac2SpeedTime(int TimeSpeed, int TimeSlowSpeed)  //วิ่งด้วยเวลาเเบบ 2 สปีดเพื่อไม่หุ่นยนต์กระดก
{
  TracSpeedTime(Speed, TimeSpeed);
  TracSpeedTime(SlowSpeed, TimeSlowSpeed);
}
