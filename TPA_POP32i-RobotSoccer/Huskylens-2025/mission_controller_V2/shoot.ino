void shoot() {
  motor(4, reloadSpd);
  delay(150);
  motor(4, 0);
  delay(50);
}
int timer = 0;
void reload() {
  motor(4, reloadSpd);
  timer = 0;
  for (int i = 0; i < 2000; i++) {
    timer++;
    if (analogRead(limPin) > 700) break;
    delay(1);
  }
  if (timer == 2000) {     // ถ้าก้านยิงติด
    motor(4, -reloadSpd);  // เลื่อนก้านยิงไปข้างหน้า
    delay(500);            //ก่อน 0.5 วินาที
    motor(4, reloadSpd);
    timer = 0;
    for (int i = 0; i < 2000; i++) {
      timer++;
      if ((analogRead(limPin) > 700)) break;
      delay(1);
    }
  }
  motor(4, 0);
}
