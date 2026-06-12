void Operation() {
  calibrate_IMU();
  waitSW_OK();
  oled.clear();
  oled.text(3, 2, "Running Mission...");
  oled.show();
  beep(1);
  delay(500);

  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
  Mission_5();

  oled.text(5, 4, "Successfully!");
  oled.show();
  beep(1);
}

//  _______________________________________
// | TracDegreeSpeedTime(80); Motorstop(); |
// | ------------------------------------- |
// | 2B |               300T               |
// | 3B |               600T               |
// | 4B |               900T               |

// Forward_Balance(40, 250);
// Backward_Balance(40, 400);

void Mission_1() {
  TracDegreeSpeedTime(80, 900);
  Forward_Balance(40, 250);
  TTR(270);
  Backward_Balance(40, 400);
  TracDegreeSpeedTime(80, 600);
  Forward_Balance(40, 250);
  TTR(270);
  Backward_Balance(40, 400);
  TracDegreeSpeedTime(80, 300);
  Forward_Balance(40, 250);
  TTR(270);
  Backward_Balance(40, 400);
  TracDegreeSpeedTime(80, 300);
  Forward_Balance(40, 250);
  TTL(90);

  Backward_Balance(40, 400);
  TracDegreeSpeedTime(80, 300);
  TTL(90);
  Backward_Balance(40, 400);
  TracDegreeSpeedTime(80, 600);
  TTL(90);
  TracDegreeSpeedTimeBack(80, 300);
  Backward_Balance(40, 350);
}

void Mission_2() {
}

void Mission_3() {
}

void Mission_4() {
}

void Mission_5() {
}
