#include <POP32.h>
void setup() {
    // put your setup code here, to run once:

}

void loop() {
  if(SW_A())
  {
    beep();
    delay(200);
  }

  if(SW_B())
  {
    sound(2000, 200);
    delay(200);
  }
}
