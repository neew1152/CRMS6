#include <POP32.h>
int min_S1 = 1410; //อ่านค่าเส้นสีดำ ด้านซ้าย
int max_S1 = 3700; //อ่านค่าพื้นสีขาว ด้านซ้าย
int min_S2 = 1380; //อ่านค่าเส้นสีดำ ด้านขวา
int max_S2 = 4095; //อ่านค่าพื้นสีขาว ด้านขวา
int maxSP = 50; //ความเร็วสูงสุดที่ต้องการ
float k = 1.0; //ค่าอัตราการขยายของความไวเซนเซอร์
#define val_S1 map(analog(1), min_S1, max_S1, 0, 100)
#define val_S2 map(analog(2), min_S2, max_S2, 0, 100)

int tag_S0 = 1550; //อ่านค่าพื้นสีเขียว ด้านซ้าย
int tag_S3 = 1420; //อ่านค่าพื้นสีเขียว ด้านขวา
int T0=0;
int T3=0;
#define val_S0 abs(analog(0) - tag_S0)
#define val_S3 abs(analog(3) - tag_S3)

#define Dist (analog(8) / 41) //อ่านค่าระยะทางวัตถุ
void setup() {
  while (!SW_OK()) { //กดปุ่ม OK เพื่อเริ่มต้นทำงาน
    oled.text(0, 0, "TagL=%d  ", analog(0));
    oled.text(1, 0, "TagR=%d  ", analog(3));
    oled.text(0, 10, "VS0=%d  ", val_S0);
    oled.text(1, 10, "VS3=%d  ", val_S3);

    oled.text(3, 0, "L=%d  ", analog(1));
    oled.text(4, 0, "R=%d  ", analog(2));
    oled.text(3, 10, "VS1=%d  ", val_S1);
    oled.text(4, 10, "VS2=%d  ", val_S2);

    oled.text(6, 0, "Dis=%d  ", Dist);
    oled.show();
  }
  beep();
}
void loop() {
  Tarck();
}
void Tarck(){
  while(1){
    if (val_S1 < 10 && val_S2 < 10) {
      getTag();
      T0=0;
      T3=0;
    } else {
      fd_Check_dis();
      if(val_S0 <100) T0++;
      if(val_S3 <100) T3++;
      int SP_M1 = constrain(val_S1 * k, 0, maxSP);
      int SP_M2 = constrain(val_S2 * k, 0, maxSP);
      motor(1, SP_M1);
      motor(2, SP_M2);
    }
  }
}
void getTag(){
  int Gain = 20;
  if(T0 < Gain && T3 < Gain){
   fd(30);sound(1500,150);
  }else if (T0 > Gain && T3 < Gain){
   L90();
  }else if (T0 < Gain && T3 > Gain){
   R90();
  }else if (T0 > Gain && T3 > Gain){
   UTurn();
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
void fd_Check_dis() {
  if (Dist < 20) {
    sr(30);delay(400);
    fd(20);delay(1500);
    sl(30);delay(300);
    fd(20);delay(1500);
    while (val_S2 > 10) { fd2(10, 30); }
    while (val_S2 < 10) { fd2(10, 30); }
    R90();
  }
}




