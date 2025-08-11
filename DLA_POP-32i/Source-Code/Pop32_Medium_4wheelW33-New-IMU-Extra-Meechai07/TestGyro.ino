void TestGyro()
{
  TracDegreeSpeedTime(BaseSpeed,0,1000,0); MotorStop();
  TracDegreeSpeedTime(BaseSpeed,90,1000,0); MotorStop();
  TracDegreeSpeedTime(BaseSpeed,180,1000,0); MotorStop();
  TracDegreeSpeedTime(BaseSpeed,270,1000,0); MotorStop();
  TracDegreeSpeedTimeBack(BaseSpeed,270,1000,0); MotorStop();
  TracDegreeSpeedTimeBack(BaseSpeed,180,1000,0); MotorStop();
  TracDegreeSpeedTimeBack(BaseSpeed,90,1000,0); MotorStop();
  TracDegreeSpeedTimeBack(BaseSpeed,0,1000,0); MotorStop();
}
