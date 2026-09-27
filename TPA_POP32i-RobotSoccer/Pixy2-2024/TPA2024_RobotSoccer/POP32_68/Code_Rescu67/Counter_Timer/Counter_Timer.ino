#include <POP32.h>
unsigned long TotalTime = 5000;
unsigned long StartTime = 0;
unsigned long EndTime = 0;
void setup() {
  StartTime = millis();
  EndTime = StartTime + TotalTime;
  while (millis() <= EndTime) {
    oled.text(0, 0, "S_Time = %d  ", StartTime);
    oled.text(2, 0, "E_Time = %d  ", EndTime);
    oled.text(4, 0, "Countdown = %d  ", EndTime-millis());
    oled.show();
    if (SW_OK()) {
      StartTime = millis();
      EndTime = StartTime + TotalTime;
      beep();
    }
  }
  oled.clear();
  oled.text(0, 0, "Finish");
  oled.show();
}
void loop() {
}
