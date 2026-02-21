#define Min 4000
#define Max 0
int Min1=Min,Max1=Max,
    Min2=Min,Max2=Max,
    MinC=Min,MaxC=Max,
    Min3=Min,Max3=Max,
    Min4=Min,Max4=Max;
int MinB1=Min,MaxB1=Max,
    MinB2=Min,MaxB2=Max,
    MinB3=Min,MaxB3=Max,
    MinB4=Min,MaxB4=Max;

void ShowAnF() //Front
{
  Read5Analog();
  //-- Min --//
  if (L2 < Min1)
  {
    Min1 = L2;
  }
  if (L1 < Min2)
  {
    Min2 = L1;
  }
  if (C < MinC)
  {
    MinC = C;
  }
  if (R1 < Min3)
  {
    Min3 = R1;
  }
  if (R2 < Min4)
  {
    Min4 = R2;
  }

  //-- Max --//
  if (L2 > Max1)
  {
    Max1 = L2;
  }
  if (L1 > Max2)
  {
    Max2 = L1;
  }
  if (C > MaxC)
  {
    MaxC = C;
  }
  if (R1 > Max3)
  {
    Max3 = R1;
  }
  if (R2 > Max4)
  {
    Max4 = R2;
  }
  oled.text(0, 0, "Front");
  oled.text(1, 0 , "L2 = %d ", (Min1 + Max1)/2);
  oled.text(2, 0 , "L1 = %d ", (Min2 + Max2)/2);
  oled.text(3, 0 , "C = %d ", (MinC + MaxC)/2);
  oled.text(4, 0 , "R1 = %d ", (Min3 + Max3)/2);
  oled.text(5, 0 , "R2 = %d ", (Min4 + Max4)/2);
  oled.text(6, 0 , "Checking Front         ");
  oled.text(7, 0 , "Press again to return");
  oled.show();
}

void ShowAnB() //Back
{
  Read4BackAnalog();
  //-- Min --//

    if (BL2 < MinB1)
    {
      MinB1 = BL2;
    }
    if (BL1 < MinB2)
    {
      MinB2 = BL1;
    }
    if (BR1 < MinB3)
    {
      MinB3 = BR1;
    }
    if (BR2 < MinB4)
    {
      MinB4 = BR2;
    }

    //-- Max --//
    if (BL2 > MaxB1)
    {
      MaxB1 = BL2;
    }
    if (BL1 > MaxB2)
    {
      MaxB2 = BL1;
    }
    if (BR1 > MaxB3)
    {
      MaxB3 = BR1;
    }
    if (BR2 > MaxB4)
    {
      MaxB4 = BR2;
    }
  oled.text(0, 10, "Back");
  oled.text(1, 10 , "BL2 = %d ", (MinB1 + MaxB1)/2);
  oled.text(2, 10 , "BL1 = %d ", (MinB2 + MaxB2)/2);
  oled.text(3, 10 , "BR1 = %d ", (MinB3 + MaxB3)/2);
  oled.text(4, 10 , "BR2 = %d ", (MinB4 + MaxB4)/2);
  oled.text(6, 0 , "Checking Back        ");
  oled.text(7, 0 , "Press again to return");
  oled.show();
}

void CheckAnalog()
{
  int CheckF, CheckB;
  CheckF = 0;
  CheckB = 0;
  oled.clear();
  oled.mode(0);
  oled.text(0, 0, "Front");
  oled.text(1, 0 , "L2 = --");
  oled.text(2, 0 , "L1 = --");
  oled.text(3, 0 , "C = --");
  oled.text(4, 0 , "R1 = --");
  oled.text(5, 0 , "R2 = --");

  oled.text(0, 10, "Back");
  oled.text(1, 10 , "BL2 = --");
  oled.text(2, 10 , "BL1 = --");
  oled.text(3, 10 , "BR1 = --");
  oled.text(4, 10 , "BR2 = --");
  oled.text(6, 0 , "Press A to check Front");
  oled.text(7, 0 , "Press B to check Back");
  oled.show();

  while(1)
  { 
    sound(500, 100);
    delay(50);  
    oled.text(6, 0 , "Press A to check Front");
    oled.text(7, 0 , "Press B to check Back");
    oled.show();
    waitAnykey(); //--Unnesseory

    if(SW_A() == 1 && CheckF == 0)
    {
      CheckF == 1;
      sound(500, 100);
      delay(100);
      while(SW_A() == 0)
      {
        ShowAnF();
      }
      CheckF = 0;
      oled.text(6, 0 , "                      ");
      oled.text(7, 0 , "Saving...             ");
      oled.show();
      sound(500, 100);
      delay(100);
      sound(500, 100);
      delay(300);
      AO();
      oled.text(6, 0 , "                      ");
      oled.text(7, 0 , "Saved!"                );
      oled.show();
      sound(5000, 100);
      delay(300);
    }
    if(SW_B() == 1 && CheckB == 0)
    {
      CheckB == 1;
      sound(500, 100);
      delay(100);
      while(SW_B() == 0)
      {
        ShowAnB();
      }
      CheckB = 0;
      oled.text(6, 0 , "                      ");
      oled.text(7, 0 , "Saving...             ");
      oled.show();
      sound(500, 100);
      delay(100);
      sound(500, 100);
      delay(300);
      AO();
      oled.text(6, 0 , "                      ");
      oled.text(7, 0 , "Saved!                ");
      oled.show();
      sound(5000, 100);
      delay(300);
    }
    if(SW_OK()== 1)
    {
      while(SW_OK() == 1)
      {
      oled.text(6, 0 , "Please use theese btn              ");
      oled.text(7, 0 , "A = Front, B = Back                ");
      oled.show();  
      sound(3000, 100);
      delay(100); 
      }   
    }
  }   
}

void Show7Analog() {
  oled.clear();
  oled.textSize(1);
  oled.text(0,1,"Black");
  oled.show();
  sw_ok_unpress();
  Wait_sw_ok_press();
  StartTimer();
  beep(1);
  sw_ok_unpress();
  if(ReadTimer()>3000) SetSpeed();
  else{
    CheckAnalog();
  }
}
