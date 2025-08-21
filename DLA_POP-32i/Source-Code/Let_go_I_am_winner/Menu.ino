void Menu() {
  sound(3000, 100);
  sound(500, 200);
  oled.clear();
  while (!SW_OK()) {
    button = knob(1, 15);
    oled.text(3, 2, "Menu = %d ", button);
    delay(100);
    oled.show();
  }
  beep(500);
  List_Menu();
}
void List_Menu() {
  reload();
  if (button == 1) {  //                                          01  Offend and defend
    oled.clear();
    oled.text(2, 0, "SW_A => defend");
    oled.text(3, 0, "SW_B => offend");
    //oled.text(4, 0, "SW_ok => Shoot_now");
    while (1) {
      if (SW_A()) {
        Count = 2;
        break;
      } else if (SW_B()) {
        Count = 1;
        break;
      } 
      getIMU();
      oled.text(0, 0, "Yaw=%f   ", pvYaw);
      oled.show();
    }
    beep(100);
    oled.clear();
    while (1) {
      if (Count == 1) {
        Mode = 1;
        discoveState = 1;
        StartTimer();
        oled.text(2, 2, "offend......");
        oled.show();
        Offend(); /*                              เกมรุกที่มีรับก่อนเเล้วมี technical ในการทำประตู (ใช้ได้บ่อยๆ)                          */
        OffMotor();
        oled.clear();
        Menu();
      } else if (Count == 2) {
        sound(3000, 4500);
        Mode = 1;
        discoveState = 1;
        oled.text(2, 2, "denfend......");
        oled.show();
        better(); /*                         เกมรับที่ใช้ถ่วงเวลารับอย่างเดียว (เมื่อนำเเล้ว)                                     */
        OffMotor();
        oled.clear();
        Menu();
      } 
    }
  } else if (button == 2) {  //                                        02  shoot_naw
    oled.text(2, 0, "SW_A => Test_Shoot");
    oled.text(3, 0, "SW_B => Shoot_naw");
    oled.text(3, 0, "SW_ok => ReadAnalog");
    while (!SW_B()) {
      if (SW_A()) {
        shoot();   //ยิง
        reload();  //เก็บก้านยิง
      } else if (SW_OK()) {
        ReadAnalog();
      }
      getIMU();
      oled.text(0, 0, "Yaw=%f   ", pvYaw);
      oled.show();
    }
    Check_shootnow = 1;
    oled.clear();
    while (1) {
      oled.text(2, 2, "shoot_now");
      oled.show();
      Shoot_now();
      OffMotor();
      oled.clear();
      Menu();
    }
  } else if (button == 3)  //                                                    03  Out_line
  {
    oled.text(2, 0, "SW_A => Test_Shoot");
    oled.text(3, 0, "SW_B => Out_line");
    oled.text(3, 0, "SW_ok => ReadAnalog");
    while (!SW_B()) {
      if (SW_A()) {
        shoot();   //ยิง
        reload();  //เก็บก้านยิง
      } else if (SW_OK()) {
        ReadAnalog();
      }
      getIMU();
      oled.text(0, 0, "Yaw=%f   ", pvYaw);
      oled.show();
    }
    Check_outline = 1;
    oled.clear();
    while (1) {
      oled.text(2, 2, "Outline......");
      oled.show();
      Out_line();
      OffMotor();
      oled.clear();
      Menu();
    }
  }else if(button == 4){
    oled.text(2, 0, "SW_A => Test_Shoot");
    oled.text(3, 0, "SW_B => Not delay");
    oled.text(4, 0, "SW_ok => ReadAnalog");
    while (!SW_B()) {
      if (SW_A()) {
        shoot();   //ยิง
        reload();  //เก็บก้านยิง
      } else if (SW_OK()) {
        ReadAnalog();
      }
      getIMU();
      oled.text(0, 0, "Yaw=%f   ", pvYaw);
      oled.show();
    }
    beep(100);
    oled.clear();
    Mode = 1;
    discoveState = 1;  //เตรียมพร้อมไปหาลูกบอลเมื่อเจอบอลอีกครั้ง
    Technic = 1;
    while (1) {
      oled.text(2, 2, "better Not delay");
      oled.show();
      better();
      OffMotor();
      oled.clear();
      Menu();
    }
  }  else if(button == 10){
    oled.text(2, 0, "SW_A => Test_Shoot");
    oled.text(3, 0, "SW_B => Goalkeeper");
    oled.text(4, 0, "SW_ok => ReadAnalog");
    while (!SW_B()) {
      if (SW_A()) {
        shoot();   //ยิง
        reload();  //เก็บก้านยิง
      } else if (SW_OK()) {
        ReadAnalog();
      }
      getIMU();
      oled.text(0, 0, "Yaw=%f   ", pvYaw);
      oled.show();
    }
    beep(100);
    oled.clear();
    while (1) {
      oled.text(2, 2, "Goalkeepper......");
      oled.show();
      Goalkeepper();
      OffMotor();
      oled.clear();
      Menu();
    }
  } else if(button == 11){
    oled.text(2, 0, "SW_A => Test_Shoot");
    oled.text(3, 0, "SW_B => Peniality_spot");
    oled.text(4, 0, "SW_ok => ReadAnalog");
    while (!SW_B()) {
      if (SW_A()) {
        shoot();   //ยิง
        reload();  //เก็บก้านยิง
      } else if (SW_OK()) {
        ReadAnalog();
      }
      getIMU();
      oled.text(0, 0, "Yaw=%f   ", pvYaw);
      oled.show();
    }
    beep(100);
    oled.clear();
    discoveState = 1;  //เตรียมพร้อมไปหาลูกบอลเมื่อเจอบอลอีกครั้ง
    while (1) {
      oled.text(2, 2, "Penality_spot.........");
      oled.show();
      Penality_spot();
      OffMotor();
      oled.clear();
      Menu();
    }
  } else if(button == 12){
    oled.text(2, 0, "SW_A => Test_Shoot");
    oled.text(3, 0, "SW_B => TestShoot");
    oled.text(3, 0, "SW_ok => ReadAnalog");
    while (!SW_B()) {
      if (SW_A()) {
        shoot();   //ยิง
        reload();  //เก็บก้านยิง
      } else if (SW_OK()) {
        ReadAnalog();
      }
      getIMU();
      oled.text(0, 0, "Yaw=%f   ", pvYaw);
      oled.show();
    }
    oled.clear();
    while (1) {
      oled.text(2, 2, "shoot_now");
      oled.show();
      TriesShooting();
      OffMotor();
      oled.clear();
      Menu();
    }
  }
}