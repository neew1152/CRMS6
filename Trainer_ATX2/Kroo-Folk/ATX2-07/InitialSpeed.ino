void InitialSpeed(int MotorSpeed)
{
  Error = 0;
  PreError = 0;
  Integral = 0;
  Ki = 0;
  MaxSpeed = MotorSpeed;
  if(MotorSpeed <= 50)
  {
    Kp = 10;
    Kd = 20;
    LeftSpeed = MotorSpeed;
    RightSpeed = MotorSpeed;
  }

  else if (MotorSpeed <= 60){
    Kp = 13;
    Kd = 25;
    LeftSpeed = MotorSpeed - 0.005;
    RightSpeed = MotorSpeed - 0;
  }

  else if(MotorSpeed <= 70)
  {
    Kp = 15;
    Kd = 30;
    LeftSpeed = MotorSpeed;
    RightSpeed = MotorSpeed;
  }
  else if(MotorSpeed <= 100)
  {
    Kp = 20;
    Kd = 60;
    LeftSpeed = MotorSpeed;
    RightSpeed = MotorSpeed;
  }
}