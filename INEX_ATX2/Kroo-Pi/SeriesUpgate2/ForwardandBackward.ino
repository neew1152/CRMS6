  
/* This is function Motor all */ 


void Forward() {
  FD2(LeftBaseSpeed,RightBaseSpeed);
}
void ForwardSpeedTime(int MotorSpeed, int Time) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  Forward();
  delay(Time);
  BaseSpeed = Speed;
  InitialSpeed();
}
void Backward() {
  BK2(BackLeftBaseSpeed,BackRightBaseSpeed);
}
void BackwardSpeedTime(int MotorSpeed, int Time) {
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  Backward();
  delay(Time);
  BaseSpeed = Speed;
  InitialSpeed();
}
void MotorStop() {
  OffMotor();
  delay(100);
}
void OffMotor()
{
  AO();
}