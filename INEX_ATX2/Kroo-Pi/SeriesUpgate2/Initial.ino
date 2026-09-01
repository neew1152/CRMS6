void InitialRef() {
  RefL2 = 1435;
  RefL1 = 3434;
  RefR1 = 1346;
  RefR2 = 3709;

  RefBL2 = 1699;
  RefBL1 = 1559;
  RefBR1 = 1522;
  RefBR2 = 2444;
}
void InitialSpeed() 
{
  //MaxSpeed = BaseSpeed;
  MaxSpeed = 100;
  Ki = 0;
  KiB = 0;
  Error = 0;
  PreError = 0;
  if(BaseSpeed<=30)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 5;       //forward PID
    Kd = 25;
    Kt = 10;
    KpB = 10;       //backward PID
    KdB = 25;
    KtB = 10;
  }
  else if(BaseSpeed<=40)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-3;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-3;
    Kp = 5;       //forward PID
    Kd = 25;
    Kt = 10;
    KpB = 10;       //backward PID
    KdB = 25;
    KtB = 10;
  }
  else if(BaseSpeed<=50)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 5;       //forward PID
    Kd = 25;
    Kt = 10;
    KpB = 10;       //backward PID
    KdB = 25;
    KtB = 10;
  }
  else if(BaseSpeed<=60)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-2;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-2;
    Kp = 5;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 13;       //backward PID
    KdB = 30;
    KtB = 10;
  }
  else if(BaseSpeed<=70)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 16;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 16;       //backward PID
    KdB = 30;
    KtB = 10;
  }
  else if(BaseSpeed<=80)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 19;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 19;       //backward PID
    KdB = 30;
    KtB = 8;
  }
  else if(BaseSpeed<=90)
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-1;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-1;
    Kp = 22;       //forward PID
    Kd = 35;
    Kt = 10;
    KpB = 22;       //backward PID
    KdB = 35;
    KtB = 10;
  }
  else
  {
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 25;       //forward PID
    Kd = 50;
    Kt = 10;
    KpB = 25;       //backward PID
    KdB = 50;
    KtB = 5;
  }
}  
