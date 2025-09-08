void Operation() {
  calibrate_IMU();
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

  oled.text(5, 4, "Successfully!");
  oled.show(); beep(1);
}

//  _____________________________________
// | TracDegreeSpeedTime(60) MotorStop() |
// | ----------------------------------- |
// | 1B |              300T              |
// | 2B |              600T              |
// | 3B |              900T              |

// Forward_Balance(40, 250);
// Backward_Balance(40, 400);

void Mission_1() {
  TracDegreeSpeedTime(60, 300);
  TTR(270);
  TracDegreeSpeedTime(60, 300);
  TTL(90);
  TracDegreeSpeedTime(60, 300);
  TTR(180);
  Kick_Front(90, 250);
}

void Mission_2() {
}

void Mission_3() {
}

void Mission_4() {
}

void Mission_5() {
}


