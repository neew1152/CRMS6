void Operation() {
  delay(500);
  calibrate_BornpvYaw();
  oled.text(6, 1, "zeroYaw Successfully"); beep(1);
  oled.show();
  waitSW_OK();
  oled.clear();
  InitialSpeed();
  oled.text(3, 2, "Running Mission...");
  beep(1); delay(500);
  oled.show();

  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
  Mission_5();
}

void Mission_1() {
  TracDegreeSpeedTime(50, 500);
  TTL(90);
  TracDegreeSpeedTime(50, 500);
  TTL(90);
  TracDegreeSpeedTime(50, 500);
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