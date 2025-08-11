void Menu() {
  sound(3000, 100);
  sound(500, 200);
  oled.clear();
  while (!SW_OK()) {
    button = knob(1, 10);
    oled.text(3, 2, "Menu = %d ", button);
    delay(100);
    oled.show();
  }
  List_Menu();
}
void List_Menu() {
  sound(3000, 100);
  if (button == 1) { //                                          01 
    oled.clear();
    oled.text(2, 0, "SW_A => Test Shoot");                        
    oled.text(3, 0, "SW_B => RUN");
    oled.text(3, 0, "SW_ok => Read Analog");
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
      StartTimer();
      oled.text(2, 2, "Running......");
      oled.show();
      //Controball();
      discover_ball();
      OffMotor();
      oled.clear();
      Menu();
    }
  } else if (button == 2) { //                                        02
    oled.text(2, 0, "SW_A => Test Shoot");
    oled.text(3, 0, "SW_B => RUN");
    oled.text(3, 0, "SW_ok => Read Analog");
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
      oled.text(2, 2, "Running......");
      oled.show();
      //Goalkeepper();
      better();
      OffMotor();
      oled.clear();
      Menu();
    }
  } else if(button == 3)
  {
    beep();
    Resetdegree();
  }
}