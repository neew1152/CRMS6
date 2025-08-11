void Operation() {
  delay(500);
  zeroYaw();
  oled.text(5, 1, "zeroYaw Successfully");
  oled.show();
  waitSW_OK();
  oled.clear();
  oled.text(4, 2, "Running Mission...");
  beep(1); delay(500);
  oled.show();

  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
  Mission_5();
}

void Mission_1() {
  TracDegreeSpeedTime(60, 500);
  TTL(90);
  TracDegreeSpeedTime(60, 500);
  TTR(90);
  TracDegreeSpeedTime(60, 500);
  TTR(90);
}

void Mission_2() {
}

void Mission_3() {
}

void Mission_4() {
}

void Mission_5() {
}