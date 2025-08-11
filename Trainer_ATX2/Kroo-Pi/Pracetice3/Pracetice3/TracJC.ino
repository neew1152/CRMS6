void TracJCStop()  //เดินถึงเส้นและออกจากฟังก์ชัน
{
  ForwardSpeedTime(BaseSpeed, 100);
  InitialSpeed();
  CalError();
  while (Error < 99) {
    TracPID();
    StartTimer();
    while ((ReadTimer() < Kt) && (Error < 100)) {
      CalError();
      if (Error > 99) {
        MotorStop();
        break;
      }
    }
  }
}
void TracJC()  //เดินถึงเส้นที่ไม่ใช่ขอบและถอยแบบจูน
{
  TracJCBlack();
  MotorStop();
  delay(100);
  BackwardBalanceF();
  BackwardSpeedTime(60, 120);
}
void TracJC0()  //เดินถึงเส้นและถอยแบบไม่จูน
{
  TracJCStop();
  MotorStop();
  delay(100);
  BackwardSpeedTime(60, 200);
  MotorStop();
}
void TracJC1()  //เดินถึงเส้นจูนและถอยแบบจูน
{
  TracJCBlack();
  MotorStop();
  delay(50);
  BackwardSpeedTime(60, 90);
  MotorStop();
}
void TTS(double block) {
  TracSpeedTime(60, 50);
  TracSpeedTime(70, 50);
  TracSpeedTime(100, 200 * block);
}

void TTS1(double block) {
  TracSpeedTime(60, 50);
  TracSpeedTime(70, 50);
  TracSpeedTime(100, 130 * block);
  TracJC1();
  MotorStop();
  delay(80);
}

void TTSB(double block) {
  TracSpeedTime(60, 50);
  TracSpeedTime(70, 50);
  TracSpeedTime(100, 200 * block);
  TracJCBlack();
}
void TracJCBlack()  //วิ่งเข้าหลุมดำหรือพื้นที่วางสีเขียว
{
  TracJCStop();
  // BackwardSpeedTime(SlowSpeed,1);
  ConvertADC();
  while ((L1 == 1) && (R1 == 1)) { ConvertADC(); }
  MotorStop();
  if ((L1 == 0) && (R1 == 1))  //เจอดำข้างซ้าย
  {
    SL(SlowSpeed);
    while (R1 == 1) { ConvertADC(); }
    delay(10);
  } else if ((L1 == 1) && (R1 == 0))  //เจอดำข้างขวา
  {
    SR(SlowSpeed);
    while (L1 == 1) { ConvertADC(); }
    delay(10);
  }
  MotorStop();
}
void TracJCForward()  //เดินถึงขอบสะพานบนและถอยเดินตรง
{
  TracJCStop();
  ForwardSpeedTime(Speed, 300);
}
void TracJCSlowStop() {
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
void TracJCSpeedStop() {
  BaseSpeed = ACCSpeed;
  TracJCStop();
  BaseSpeed = Speed;
  InitialSpeed();
}
void TracACC(int MotorSpeed, int Time) {
  ForwardSpeedTime(60, 100);
  TracSpeedTime(MotorSpeed, Time - 100);
}
void TracJC0ACCTime(int MotorSpeed, int Time) {
  TracACC(MotorSpeed, Time);
  TracJC0();
}
void TracJC1ACCTime(int MotorSpeed, int Time) {
  TracACC(MotorSpeed, Time);
  TracJC1();
}
void TracJCACCTime(int MotorSpeed, int Time) {
  TracACC(MotorSpeed, Time);
  TracJC();
}
void TracJCStopACCTime(int MotorSpeed, int Time) {
  TracACC(MotorSpeed, Time);
  TracJCStop();
}
