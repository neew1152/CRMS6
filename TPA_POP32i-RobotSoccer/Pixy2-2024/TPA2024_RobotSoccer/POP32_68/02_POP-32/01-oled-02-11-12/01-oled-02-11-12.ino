#include <POP32.h>
void setup() {
  //2//
  if (SW_B()) {
    oled.clear();
    oled.text(3, 5, "Hello POP-32");
    oled.show();
  }

  //11//
  if (SW_A()) {
    oled.clear();
    oled.textColor(BLACK, WHITE);
    oled.text(3, 5, "Hello world");
    oled.show();
  }

  //12//
  if (SW_OK()) {
    oled.clear();
    oled.textSize(1);
    oled.textColor(BLACK, WHITE);
    oled.text(2, 0, "Hello world");
    oled.show();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
