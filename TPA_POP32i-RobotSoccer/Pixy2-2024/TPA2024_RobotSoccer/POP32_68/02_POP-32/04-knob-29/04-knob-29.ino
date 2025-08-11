#include <POP32.h>
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  oled.clear();
  oled.text(3, 5, "knob=%d", knob());
  oled.show();
}
