#include <POP32.h>
#define limPin PA0
#define reloadSpd 60
void shoot() {
  motor(4, reloadSpd);
  delay(150);
  motor(4, 0);
  delay(50);
}
void reload() {
  motor(4, reloadSpd);
  int timer = 0;
  for (int i = 0; i < 2000; i++) {
    timer++;
    if (analog(limPin)>1000) break;
    delay(1);
  }
  if (timer == 2000) {           // ถ้าก้านยิงติด
    motor(4, -reloadSpd);  // เลื่อนก้านยิงไปข้างหน้า
    delay(500);                  //ก่อน 0.5 วินาที
    motor(4, reloadSpd);
    timer = 0;
    for (int i = 0; i < 2000; i++) {
      timer++;
      if (analog(limPin)>1000) break;
      delay(1);
    }
  }
  motor(4, 0);
}
void setup() {
  oled.mode(2);
  oled.text(0, 0, "SW_A reload");
  oled.text(1, 0, "SW_B shoot");
  oled.text(2, 0, "SW_OK shoot reload");
  oled.show();
}
void loop() {
  if (SW_A()) { reload(); }
  if (SW_B()) { shoot(); }
  if (SW_OK()) {
    shoot();reload();
  }
}
