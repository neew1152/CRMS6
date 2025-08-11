#include <POP32.h>
int min_S1 = 2100; //อ่านค่าเส้นสีดำ ด้านซ้าย
int max_S1 = 3700; //อ่านค่าพื้นสีขาว ด้านซ้าย
int min_S2 = 2300; //อ่านค่าเส้นสีดำ ด้านขวา
int max_S2 = 3700; //อ่านค่าพื้นสีขาว ด้านขวา
int maxSP = 50; //ความเร็วสูงสุดที่ต้องการ
float k = 1.0; //ค่าอัตราการขยายของความไวเซนเซอร์
#define val_S1 map(analog(1), min_S1, max_S1, 0, 100)
#define val_S2 map(analog(2), min_S2, max_S2, 0, 100)

int tag_S0 = 1300; //อ่านค่าพื้นสีเขียว ด้านซ้าย
int tag_S3 = 1600; //อ่านค่าพื้นสีเขียว ด้านขวา
int T0=0;
int T3=0;
#define val_S0 abs(analog(0) - tag_S0)
#define val_S3 abs(analog(3) - tag_S3)

void setup() {
  while (!SW_OK()) { //กดปุ่ม OK เพื่อเริ่มต้นทำงาน
    oled.text(0, 0, "TagL=%d  ", analog(0));
    oled.text(2, 0, "TagR=%d  ", analog(3));
    oled.text(4, 0, "VS0=%d  ", val_S0);
    oled.text(6, 0, "VS3=%d  ", val_S3);
    oled.show();
  }
  beep();
}
void loop() {
  Tarck();
  ao();
  oled.clear();
  while(!SW_OK()){
    oled.text(0, 0, "T0=%d  ", T0);
    oled.text(2, 0, "T3=%d  ", T3);
    oled.show();
  }
  beep();
  T0=0;
  T3=0;
}
void Tarck(){
  while(1){
    if (val_S1 < 10 && val_S2 < 10) {
      break;
    } else {
      if(val_S0 <100) T0++;
      if(val_S3 <100) T3++;
      int SP_M1 = constrain(val_S1 * k, 0, maxSP);
      int SP_M2 = constrain(val_S2 * k, 0, maxSP);
      motor(1, SP_M1);
      motor(2, SP_M2);
    }
  }
}



