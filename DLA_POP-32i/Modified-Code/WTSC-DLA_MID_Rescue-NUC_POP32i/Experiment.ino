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

//  _____________________________________
// | TracDegreeSpeedTime(60) MotorStop() |
// | ----------------------------------- |
// | 1B |              300T              |
// | 2B |              600T              |
// | 3B |              900T              |

// Forward_Balance(40, 250);
// Backward_Balance(40, 400);

void Lab_1() {
  Forward_Balance(40, 250);
  waitSW_A();
  Backward_Balance(40, 400);
}

void Lab_2() {

}

void Lab_3() {

}





