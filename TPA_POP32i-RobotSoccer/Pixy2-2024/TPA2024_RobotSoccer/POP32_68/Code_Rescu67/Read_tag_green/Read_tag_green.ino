#include <POP32.h>
int tag_S0 = 1300; //อ่านค่าพื้นสีเขียว ด้านซ้าย
int tag_S3 = 1600; //อ่านค่าพื้นสีเขียว ด้านขวา
#define val_S0 abs(analog(0) - tag_S0)
#define val_S3 abs(analog(3) - tag_S3)

void setup() {
  while (!SW_OK()) { //กดปุ่ม OK เพื่อเริ่มต้นทำงาน
    oled.text(0, 0, "TagL=%d  ", analog(0));
    oled.text(2, 0, "TagR=%d  ", analog(3));
    oled.text(4, 0, "VS1=%d  ", val_S0);
    oled.text(6, 0, "VS3=%d  ", val_S3);
    oled.show();
  }
  beep();
}
void loop() {
  
}
