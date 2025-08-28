void Experiment() {
  calibrate_IMU();
  waitSW_A();
  oled.clear();
  oled.text(3, 0, "Running Laboratory...");
  oled.show(); beep(1);
  delay(500);

  Lab_1();
  Lab_2();
  Lab_3();

  oled.text(5, 4, "Successfully!");
  oled.show(); beep(1);
}

// | ------------------------------------- |
// | TracDegreeSpeedTime(80); Motorstop(); |
// | ------------------------------------- |
// | 2B |               300T               |
// | 3B |               600T               |
// | 4B |               900T               |

// Forward_Balance(40, 250);
// Backward_Balance(40, 400);

void Lab_1() {
  Backward_Balance(40, 400);
}

void Lab_2() {

}

void Lab_3() {

}



