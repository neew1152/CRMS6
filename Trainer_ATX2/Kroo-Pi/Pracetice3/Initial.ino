void Read5Analog() {
  L2 = analog(0);
  L1 = analog(1);

  R1 = analog(3);
  R2 = analog(4);
}
void Read4BackAnalog() { 
  BL2 = analog(5);
  BL1 = analog(6);
  BR1 = analog(7);
  BR2 = analog(8);
}
void ShowCon()
{
  oled.clear();
  ConvertADC();
  ConvertADCBack();
  while(1)
  {
    ConvertADCBack();
    ConvertADC();
    oled.text(0,0,"0:Black 1:White");

    oled.text(1,0,"L2 =%d  ",L2);
    oled.text(2,0,"L1 =%d  ",L1);
    oled.text(3,0,"R1 =%d  ",R1);
    oled.text(4,0,"R2 =%d  ",R2);
    
    oled.text(1,5,"BL2 =%d  ",BL2);
    oled.text(2,5,"BL1 =%d  ",BL1);
    oled.text(3,5,"BR1 =%d  ",BR1);
    oled.text(4,5,"BR2 =%d  ",BR2);
    oled.show();
  }
}
void InitialRef() {  
  // RefL2 = 2411;
  // RefL1 = 2453;
  // RefC = 2165;
  // RefR1 = 2239;
  // RefR2 = 2122;

  // RefBL2 = 2199;
  // RefBL1 = 2453;
  // RefBR1 = 2466;
  // RefBR2 = 2354;
  
  RefL2 = 572;
  RefL1 = 3396;
  RefR1 = 897;
  RefR2 = 3324;

  RefBL2 = 1686;
  RefBL1 = 1471;
  RefBR1 = 1474;
  RefBR2 = 2374;
}
void InitialSpeed() 
{
  //MaxSpeed = BaseSpeed;
  MaxSpeed = 100;
  Ki = 0;
  KiB = 0;
  Error = 0;
  PreError = 0;
  if(BaseSpeed<=40)
  {
    LeftBaseSpeed = BaseSpeed-1;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-1;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 10;       //forward PID
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
    Kp = 10;       //forward PID
    Kd = 25;
    Kt = 10;
    KpB = 10;       //backward PID
    KdB = 25;
    KtB = 10;
  }
  else if(BaseSpeed<=60)
  {
    LeftBaseSpeed = BaseSpeed-1;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-1;
    BackRightBaseSpeed = BaseSpeed-0;
    Kp = 13;       //forward PID
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
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-0;
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
