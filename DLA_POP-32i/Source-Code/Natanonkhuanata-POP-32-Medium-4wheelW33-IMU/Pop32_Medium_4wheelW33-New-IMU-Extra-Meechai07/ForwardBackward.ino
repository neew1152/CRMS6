void RobotStart() 
{
  ForwardSpeedTime(Speed,200);
}

void Forward() {
  FD2(LeftBaseSpeed,RightBaseSpeed);
}
void ForwardDelay(int Time) {
  Forward();
  delay(Time);
}
void ForwardSpeedDelay(int Time) {
  BaseSpeed = ACCSpeed;
  InitialSpeed();
  Forward();
  delay(Time);
  BaseSpeed = Speed;
  InitialSpeed();
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
void BackwardDelay(int Time) {
  Backward();
  delay(Time);
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
  delay(10);
}
void OffMotor()
{
  AO();
}
