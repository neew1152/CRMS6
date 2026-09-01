#define BrakeSpeed 100
#define BrakeTime 10
void TurnLeft()
{
  if(TurnStatus==0) TurnLeftTime(); //เลี้ยวซ้ายหน่วงเวลา
  else TurnLeftDegree(100,85,2); //เลี้ยวซ้ายใช้เข็มทิศ
}
void TurnRight()
{
  if(TurnStatus==0) TurnRightTime(); //เลี้ยวขวาหน่วงเวลา
  else TurnRightDegree(100,85,2); //เลี้ยวขวาใช้เข็มทิศ
}
void UTurnLeft()
{
  if(TurnStatus==0) UTurnLeftTime(); //กลับตัวซ้ายหน่วงเวลา
  else TurnLeftDegree(100,180,2); //กลับตัวซ้ายใช้เข็มทิศ
}
void UTurnRight()
{
  if(TurnStatus==0) UTurnRightTime(); //กลับตัวขวาหน่วงเวลา
  else TurnRightDegree(100,180,2); //กลับตัวขวาใช้เข็มทิศ
}
/////////////////////////////////////////////////////////////////////
void TurnLeftTime() {
  Left(TurnSpeed , 17500/TurnSpeed);
  if((BrakeTime>0)&&(TurnSpeed>70)) Right(BrakeSpeed,BrakeTime);
}
void TurnRightTime() {
  Right(TurnSpeed , 16500/TurnSpeed);
  if((BrakeTime>0)&&(TurnSpeed>70)) Left(BrakeSpeed,BrakeTime);
}
void UTurnLeftTime() {
  Left(TurnSpeed , 33000/TurnSpeed);
  if((BrakeTime>0)&&(TurnSpeed>70)) Right(BrakeSpeed,BrakeTime);
}
void UTurnRightTime() {
  Right(TurnSpeed , 32000/TurnSpeed);
  if((BrakeTime>0)&&(TurnSpeed>70)) Left(BrakeSpeed,BrakeTime);
}
void Left(int Speed , int Time){
  MotorStop();
  SL(Speed);
  delay(Time);
  MotorStop();
}
void Right(int Speed , int Time){
  MotorStop();
  SR(Speed);
  delay(Time);
  MotorStop();
}
void TurnLeftDelay(int Speed , int Time){
  TL(Speed);
  delay(Time);
}
void TurnRightDelay(int Speed , int Time){
  TR(Speed);
  delay(Time);
}