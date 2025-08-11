void ServoKickF()   //องศาเตะเซอร์โวหน้า
{
  servo(1,90);
}
void ServoCloseF()  //องศาปิดเซอร์โวหน้า
{
  servo(1,155);
}
void ServoKickB()   //องศาเตะเซอร์โวหลัง
{
  servo(2,100);
}
void ServoCloseB()  //องศาปิดเซอร์โวหลัง
{
  servo(2,160);
}
void KickF()            //หยุดพร้อมเตะลูกบาศก์ด้านหน้า
{
  MotorStop();
  ServoKickF();
  delay(300);
  ServoCloseF(); 
}
void KickB()            //หยุดพร้อมเตะลูกบาศก์ด้านหลัง
{
  MotorStop();
  ServoKickB();
  delay(300);
  ServoCloseB(); 
}
void KickFBackward()    //ถอยหลังพร้อมเตะลูกบาศก์ด้านหน้า
{
  ServoKickF(); 
  MotorStop();  delay(150);
  BackwardSpeedTime(ACCSpeed,200); 
  ServoCloseF(); 
}
void KickBForward()   //เดินหน้าพร้อมเตะลูกบาศก์ด้านหลัง
{
  ServoKickB(); 
  MotorStop();  delay(150);
  ForwardSpeedTime(ACCSpeed,120); 
  ServoCloseB();
}
void KickFBackwardDegree(int MotorSpeed, int Degree ,int Time)   //ถอยหลังตามองศาพร้อมเตะลูกบาศก์ด้านหน้า
{
  ServoKickF(); 
  MotorStop(); 
  TracDegreeSpeedTimeBack(MotorSpeed,Degree,Time,0); 
  ServoCloseF();
}
void KickBForwardDegree(int MotorSpeed, int Degree ,int Time)   //เดินหน้าตามองศาพร้อมเตะลูกบาศก์ด้านหลัง
{
  ServoKickB(); 
  MotorStop(); 
  TracDegreeSpeedTime(MotorSpeed,Degree,Time,0); 
  ServoCloseB();
}
