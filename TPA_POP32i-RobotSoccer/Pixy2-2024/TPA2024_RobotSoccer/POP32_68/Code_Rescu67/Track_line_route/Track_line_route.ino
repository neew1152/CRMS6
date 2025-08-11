#include <POP32.h>
int min_S1 = 1700; //อ่านค่าเส้นสีดำ ด้านซ้าย
int max_S1 = 4095; //อ่านค่าพื้นสีขาว ด้านซ้าย
int min_S2 = 1900; //อ่านค่าเส้นสีดำ ด้านขวา
int max_S2 = 3700; //อ่านค่าพื้นสีขาว ด้านขวา
int maxSP = 50; //ความเร็วสูงสุดที่ต้องการ
float k = 1.0; //ค่าอัตราการขยายของความไวเซนเซอร์
#define val_S1 map(analog(1), min_S1, max_S1, 0, 100)
#define val_S2 map(analog(2), min_S2, max_S2, 0, 100)

void setup() {
  while (!SW_OK()) { //กดปุ่ม OK เพื่อเริ่มต้นทำงาน
    oled.text(0, 0, "L=%d  ", analog(1));
    oled.text(2, 0, "R=%d  ", analog(2));
    oled.text(4, 0, "VS1=%d  ", val_S1);
    oled.text(6, 0, "VS2=%d  ", val_S2);
    oled.show();
  }
  beep();
}
void loop() {
  Tarck();R90();Tarck();L90();Tarck();ao();while(1);
}
void Tarck(){
  while(1){
    if (val_S1 < 10 && val_S2 < 10) {
      break;
    } else {
      int SP_M1 = constrain(val_S1 * k, 0, maxSP);
      int SP_M2 = constrain(val_S2 * k, 0, maxSP);
      motor(1, SP_M1);
      motor(2, SP_M2);
    }
  }
}
void R90(){
  fd(30);sound(1500,150);
  while(val_S2<10){sr(30);}
  while(val_S2>10){sr(30);}       
  while(val_S1>20){sr(30);}
}
void L90(){
  fd(30); sound(1500,150);  
  while(val_S1<10){sl(30);}  
  while(val_S1>10){sl(30);}      
  while(val_S2>20){sl(30);}
}
void UTurn(){
  bk(30);sound(1500,450);
  while(val_S2<10){sr(30);}
  while(val_S2>10){sr(30);}       
  while(val_S1>20){sr(30);}
}




