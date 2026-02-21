void Menu()
{
    oled.clear();
    oled.textSize(1);
    while (1)
    {
    x = knob(10);
    oled.text(0,0, "Menu %d  ", x);
    Menuname();
    oled.show();
   if(SW_OK()){DM();sound(3000,100);break;}
    if(SW_A()){DM();sound(4000,100);break;}
    if(SW_B()){DM();sound(5000,100);break;}
    }
    MotorStop();
    // while(1){M();sw_ok_press();}
    
}
void Menuname()
{
  if(x==0)
  {
    oled.text(2,0,"OK TMF      ");
    oled.text(3,0,"A  TMB      ");
    oled.text(4,0,"B  ShowCon      ");
  }
  if(x==1)
  {
    oled.text(2,0,"OK ShowAn      ");
    oled.text(3,0,"A  PIDBack             ");
    oled.text(4,0,"B  Forward40          ");
  }
  if(x==2)
  {
    oled.text(2,0,"OK Left90        ");
    oled.text(3,0,"A  Right90       ");
    oled.text(4,0,"B  BackBalance    ");
  }
  if(x==3)
  {
    oled.text(2,0,"OK TL              ");
    oled.text(3,0,"A  TR              ");
    oled.text(4,0,"B  Box1       ");
  }
  if(x==4)
  {
    oled.text(2,0,"OK Box2            ");
    oled.text(3,0,"A  Box3            ");
    oled.text(4,0,"B  Box4            ");
  }
  if(x==5)
  {
    oled.text(2,0,"OK Finish            ");
    oled.text(3,0,"A  SetServo           ");
    oled.text(4,0,"B                     ");
  }
  if(x==6)
  {
    oled.text(2,0,"OK                      ");
    oled.text(3,0,"A  TLB                  ");
    oled.text(4,0,"B  TRB                ");
  }
  if(x==7)
  {
    oled.text(2,0,"OK TracIMU                ");
    oled.text(3,0,"A  SpinL                  ");
    oled.text(4,0,"B  SpinR                  ");
  }
  
}
void DM()
{
  if(x==0)
  {
    if(SW_OK()==1){delay(300);TM();MotorStop();}
    if(SW_A()==1){delay(300);TMB();MotorStop();}
    if(SW_B()==1){delay(300);ShowCon();}
  }
  if(x==1)
  {
    if(SW_OK()==1){delay(300);Show7Analog();}
    if(SW_A()==1){delay(300);TracJCBlackBack();MotorStop();}
    if(SW_B()==1){delay(300);ForwardDelay(40,2400);MotorStop();}
  }
  if(x==2)
  {
    if(SW_OK()==1){delay(300);TurnLeftDegree(100,80,2);}
    if(SW_A()==1){delay(300);TurnRightDegree(100,80,2);}
    if(SW_B()==1){delay(300);BB();}
  }
  if(x==3)
  {
    if(SW_OK()==1){delay(300);TLD(100,90-10,1);MotorStop();} //550 UTurn
    if(SW_A()==1){delay(300);TRD(100,270-10,1);MotorStop();}
    if(SW_B()==1){delay(300);Box1();}
  }
  if(x==4)
  {
    if(SW_OK()==1){delay(300);Box2();}
    if(SW_A()==1){delay(300);Box3();}
    if(SW_B()==1){delay(300);Box4();}
  }
  if(x==5)
  {
    if(SW_OK()==1){delay(300);GoFinishAcc();}
    if(SW_A()==1){delay(300);SetServo();}
    if(SW_B()==1){delay(300);}
  }
  if(x==6)
  {
    if(SW_OK()==1){delay(300);}
    if(SW_A()==1){delay(300);TLDB(100,90,1);}
    if(SW_B()==1){delay(300);TRDB(100,270,1);}
  }
  if(x==7)
  {
    if(SW_OK()==1)
    {
      delay(300);
      TDT(50,0,100,0);
      TDT(60,0,100,0); 
      TDT(100,0,200,0);MotorStop();
    }
    if(SW_A()==1){delay(300);SpinDegree(100, 90, 0);}
    if(SW_B()==1){delay(300);SpinDegree(100, 270, 0);}
  }
}