void TM()
{
  oled.clear();
  oled.textSize(1);
  int ln=0,rn=0,Time,MotorSpeed;
  while(1)
  {
    MotorSpeed = knob(10)*10;
    // ln = knob(1/0);
    oled.text(1,1,"Speed = %d  ",MotorSpeed);
    oled.text(2,1,"L:%d ",ln);
    oled.text(3,1,"R:%d ",rn);
    oled.text(4,1,"Time: %d  s",Time);
    oled.show();
    if(SW_OK()){beep();break;MotorStop();}
  }
  oled.clear();
  while(1)
  {
    ln = knob(20);
    oled.text(1,1,"Speed = %d  ",MotorSpeed);
    oled.text(2,1,"L:%d ",ln);
    oled.text(3,1,"R:%d ",rn);
    oled.text(4,1,"Time: %d  s",Time);
    oled.show();
    if(SW_OK()){beep();break;MotorStop();}
  }
  oled.clear();
  while(1)
  {
    rn = knob(20);
    oled.text(1,1,"Speed = %d  ",MotorSpeed);
    oled.text(2,1,"L:%d ",ln);
    oled.text(3,1,"R:%d ",rn);
    oled.text(4,1,"Time: %d  s",Time);
    oled.show();
    if(SW_OK()){beep();break;MotorStop();}
  }
  oled.clear();
  while(1)
  {
    Time = knob(10);
    oled.text(1,1,"Speed = %d  ",MotorSpeed);
    oled.text(2,1,"L:%d ",ln);
    oled.text(3,1,"R:%d ",rn);
    oled.text(4,1,"Time: %d  s",Time);
    oled.text(5,1,"SW_OK:Start");
    oled.show();
    if(SW_OK()){beep();break;MotorStop();}
  }
  Time=knob(10);
  oled.clear();
  oled.text(1,1,"Speed = %d  ",MotorSpeed);
  oled.text(2,1,"L:%d ",ln);
  oled.text(3,1,"R:%d ",rn);
  oled.text(4,1,"Time: %d s",Time);
  oled.text(5,1,"Start");
  oled.show();

  InitialSpeed();
  BaseSpeed=MotorSpeed;
  if(MotorSpeed>=70){
    InitialSpeed();
    BaseSpeed=60;FD2(LeftBaseSpeed,RightBaseSpeed);delay(200);
    BaseSpeed=MotorSpeed;FD2(LeftBaseSpeed-ln,RightBaseSpeed-rn);delay(Time*1000);
    BaseSpeed=60;FD2(LeftBaseSpeed,RightBaseSpeed);delay(100);
  }
  else if(MotorSpeed<=70){FD2(LeftBaseSpeed-ln,RightBaseSpeed-rn);delay(Time*1000);}
  MotorStop();
}

void TMB()
{
  oled.clear();
  oled.textSize(1);
  int ln=0,rn=0,Time,MotorSpeed;
  while(1)
  {
    MotorSpeed = knob(10)*10;
    // ln = knob(1/0);
    oled.text(1,1,"Speed = %d  ",MotorSpeed);
    oled.text(2,1,"L:%d ",ln);
    oled.text(3,1,"R:%d ",rn);
    oled.text(4,1,"Time: %d  s",Time);
    oled.show();
    if(SW_OK()){beep();break;MotorStop();}
  }
  oled.clear();
  while(1)
  {
    ln = knob(20);
    oled.text(1,1,"Speed = %d  ",MotorSpeed);
    oled.text(2,1,"L:%d ",ln);
    oled.text(3,1,"R:%d ",rn);
    oled.text(4,1,"Time: %d  s",Time);
    oled.show();
    if(SW_OK()){beep();break;MotorStop();}
  }
  oled.clear();
  while(1)
  {
    rn = knob(20);
    oled.text(1,1,"Speed = %d  ",MotorSpeed);
    oled.text(2,1,"L:%d ",ln);
    oled.text(3,1,"R:%d ",rn);
    oled.text(4,1,"Time: %d  s",Time);
    oled.show();
    if(SW_OK()){beep();break;MotorStop();}
  }
  oled.clear();
  while(1)
  {
    Time = knob(10);
    oled.text(1,1,"Speed = %d  ",MotorSpeed);
    oled.text(2,1,"L:%d ",ln);
    oled.text(3,1,"R:%d ",rn);
    oled.text(4,1,"Time: %d  s",Time);
    oled.text(5,1,"SW_OK:Start");
    oled.show();
    if(SW_OK()){beep();break;MotorStop();}
  }
  Time=knob(10);
  oled.clear();
  oled.text(1,1,"Speed = %d  ",MotorSpeed);
  oled.text(2,1,"L:%d ",ln);
  oled.text(3,1,"R:%d ",rn);
  oled.text(4,1,"Time: %d millis",Time);
  oled.text(5,1,"Start");
  oled.show();

  InitialSpeed();
  BaseSpeed=MotorSpeed;
  if(MotorSpeed>=70){
    InitialSpeed();
    BaseSpeed=60;BK2(BackLeftBaseSpeed,BackRightBaseSpeed);delay(100);
    BaseSpeed=MotorSpeed;BK2(BackLeftBaseSpeed-ln,BackRightBaseSpeed-rn);delay(Time*1000);
    BaseSpeed=60;BK2(BackLeftBaseSpeed,BackRightBaseSpeed);delay(100);
  }
  else if(MotorSpeed<=70){BK2(BackLeftBaseSpeed-ln,BackRightBaseSpeed-rn);delay(Time*1000);}
  MotorStop();
}