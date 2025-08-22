void Operation() {
  delay(500);
  calibrate_IMU();
  oled.text(5, 4, "Successfully");
  oled.show(); beep(1);
  waitSW_OK();
  oled.clear();
  oled.text(3, 2, "Running Mission...");
  oled.show(); beep(1);
  delay(500);
  
  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
  Mission_5();

  oled.clear();
  oled.text(3, 6, "Operation");
  oled.text(5, 4, "Successfully!");
  oled.show(); beep(1);
}

void Mission_1() {
  TracDegreeSpeedTime(50, 250);
  TTL(90);
  TracDegreeSpeedTime(50, 250);
  TTL(90);
  TracDegreeSpeedTime(50, 250);
  TTL(90);
  TracDegreeSpeedTime(50, 250);
  TTL(90);
  TracDegreeSpeedTime(50, 250);
  TTR(270);
  TracDegreeSpeedTime(50, 250);
  TTR(270);
  TracDegreeSpeedTime(50, 250);
  TTR(270);
  TracDegreeSpeedTime(50, 250);
  TTR(270);
}

void Mission_2() {
}

void Mission_3() {
}

void Mission_4() {
}

void Mission_5() {
}