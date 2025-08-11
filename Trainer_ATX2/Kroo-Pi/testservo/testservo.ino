#include <POP32.h>

int grip;


void setup() {
  // put your setup code here, to run once:
  Testservo();
}

void loop() {
  // put your main code here, to run repeatedly:

}
void Testservo() {
  oled.clear();
  servo(6, 0);
  while (1) {
    grip = knob(360);
    servo(6, grip);
    oled.text(3, 3, "Degree = %d   ", grip);
    oled.show();
    delay(1000);
    if (SW_A()) break;
  }
  beep(500);
  servo(4, 0);
  while (1) {
    grip = knob(360);
    servo(4, grip);
    oled.text(4, 3, "Degree = %d   ", grip);
    oled.show();
    delay(1000);
    if (SW_A()) break;
  }
  beep(500);
  servo(5, 0);
  while (1) {
    grip = knob(360);
    servo(5, grip);
    oled.text(5, 3, "Degree = %d   ", grip);
    oled.show();
    delay(1000);
    if (SW_A()) break;
  }
}