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

  else
  {
    sound(2000, 200);
    delay(200);
  }
}
