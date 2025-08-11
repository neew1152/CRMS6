void InitialRef() {
  RefL2 = 1614;
  RefL1 = 2632;
  RefC = 1686;
  RefR1 = 1264;
  RefR2 = 1669;

  RefBL2 = 1592;
  RefBL1 = 978;
  RefBR1 = 1405;
  RefBR2 = 1462;
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
    LeftBaseSpeed = BaseSpeed-0;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-2;
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
    LeftBaseSpeed = BaseSpeed-1;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-4;
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
    LeftBaseSpeed = BaseSpeed-2;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
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
    LeftBaseSpeed = BaseSpeed-3;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-2;
    Kp = 16;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 16;       //backward PID
    KdB = 30;
    KtB = 10;
  }
  else if(BaseSpeed<=80)
  {
    LeftBaseSpeed = BaseSpeed-4;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-3;
    Kp = 19;       //forward PID
    Kd = 30;
    Kt = 10;
    KpB = 19;       //backward PID
    KdB = 30;
    KtB = 8;
  }
  else if(BaseSpeed<=90)
  {
    LeftBaseSpeed = BaseSpeed-3;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-3;
    Kp = 22;       //forward PID
    Kd = 35;
    Kt = 10;
    KpB = 22;       //backward PID
    KdB = 35;
    KtB = 10;
  }
  else
  {
    LeftBaseSpeed = BaseSpeed-1;
    RightBaseSpeed = BaseSpeed-0;
    BackLeftBaseSpeed = BaseSpeed-0;
    BackRightBaseSpeed = BaseSpeed-3;
    Kp = 25;       //forward PID
    Kd = 50;
    Kt = 10;
    KpB = 25;       //backward PID
    KdB = 50;
    KtB = 5;
  }
}

void SetSpeed()
{
  int SW_OK0;
  oled.clear();
  oled.text(0,0,"    Set Speed   ");
  oled.text(1,0,"Speed = %d",Speed);
  oled.show();
  SW_OK0 = No;
  while(SW_OK0 == No)  
  {  // waiting "OK" button
      if(Read_sw_OK()) 
      {
        StartTimer();
        beep(0);
        sw_ok_unpress();
        if(ReadTimer() >= 2000)     //Set Speed Ok
        {
          beep(1);
          SW_OK0 = Yes;
        }
        else      //Change Speed
        {
          SW_OK0 = No;
          Speed += 5;
          if(Speed>100) Speed = 60;
          oled.text(1,0,"Speed = %d  ",Speed);
          oled.show();       
        }
       }
  }
  oled.text(2,0,"ACCSpeed = %d",ACCSpeed);
  oled.show();
  SW_OK0 = No;
  while(SW_OK0 == No)  
  {  // waiting "OK" button
      if(Read_sw_OK()) 
      {
        StartTimer();
        beep(2);
        sw_ok_unpress();
        if(ReadTimer() >= 2000)     //Set Speed Ok
        {
          beep(100);
          SW_OK0 = Yes;
        }
        else      //Change Speed
        {
          SW_OK0 = No;
          ACCSpeed += 5;
          if(ACCSpeed>100) ACCSpeed = 60;
          oled.text(2,0,"ACCSpeed = %d  ",ACCSpeed);
          oled.show();       
        }
       }
  }
  BaseSpeed = Speed; 
  TurnSpeed = BaseSpeed;
  InitialSpeed();
  oled.text(3,0,"Press OK to Start");
  oled.show(); 
}

