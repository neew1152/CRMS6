void Experiment() {
  delay(500);
  zeroYaw();
  oled.text(3, 1, "zeroYaw Successfully");
  oled.show();
  waitSW_A();
  oled.clear();
  oled.text(4, 0, "Running Laboratory...");
  beep(1); delay(500);
  oled.show();

  Lab_1();
  Lab_2();
  Lab_3();
}

void Lab_1() {

}

void Lab_2() {

}

void Lab_3() {

}

