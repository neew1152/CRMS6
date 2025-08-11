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
