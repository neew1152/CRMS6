#include <POP32.h>
void setup() {
  oled.clear();
  oled.text(3, 5, "Press SW_OK");
  oled.show();  
  waitSW_OK();
}

void loop() {
  beep();
  delay(1000);
}
