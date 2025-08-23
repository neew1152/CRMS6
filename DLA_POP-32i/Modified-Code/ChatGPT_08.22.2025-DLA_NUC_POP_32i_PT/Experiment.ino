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

  oled.clear();
  oled.text(3, 5, "Experiment");
  oled.text(5, 4, "Successfully!");
  oled.show(); beep(1);
}

void Lab_1() {

}

void Lab_2() {

}

void Lab_3() {

}



