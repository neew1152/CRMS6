void ReadAnalog() {
  L = analog(4);
  C = analog(3);
  R = analog(5);
}
void ShowAnalog() {
  oled.clear();
  while (1) {
    oled.text(0, 0, "C = %d ", analog(3));
    oled.text(1, 0, "L = %d ", analog(4));
    oled.text(2, 0, "R = %d ", analog(5));
    delay(500);
    oled.show();
  }
}