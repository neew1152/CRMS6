int a,b,c;
void SetServo()
{
  oled.clear();
  oled.text(7,3,"- Set Servo -");
  
    oled.text(0,0,"A = %d    ",a);
    oled.text(1,0,"B = %d    ",b);
    oled.text(2,0,"C = %d    ",c);
    oled.show();
   while(1)
  { 
    if(SW_OK()==1){
      beep();
      while(SW_OK()==0){
      a=knob(180);
      servo(1,a);
      oled.text(0,0,"A = %d    ",a);
      oled.show();
      if(SW_OK()==1){delay(100);sound(4000,100);break;}
      }
    }
    if(SW_A()==1){
      beep();
      while(SW_A()==0){
      b=knob(180);
      servo(2,b);
      oled.text(1,0,"B = %d    ",b);
      oled.show();
      if(SW_A()==1){delay(100);sound(4000,100);break;}
      }
    }
    if(SW_B()==1){
      beep();
      while(SW_B()==0){
      c=knob(180);
      servo(3,c);
      oled.text(2,0,"C = %d    ",c);
      oled.show();
      if(SW_B()==1){delay(100);sound(4000,100);break;}
      }
    }

  }
}