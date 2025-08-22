void Experiment() {
  delay(500);
  calibrate_IMU();
  oled.text(5, 4, "Successfully");
  oled.show(); beep(1);
  waitSW_A();
  oled.clear();
  oled.text(3, 0, "Running Laboratory...");
  beep(1); delay(500);
  oled.show();

  Lab_1();
  Lab_2();
  Lab_3();

  oled.clear();
  oled.text(3, 5, "Experiment");
  oled.text(5, 4, "Successfully!");
  oled.show();
}

void Lab_1() {

}

void Lab_2() {

}

void Lab_3() {

}

