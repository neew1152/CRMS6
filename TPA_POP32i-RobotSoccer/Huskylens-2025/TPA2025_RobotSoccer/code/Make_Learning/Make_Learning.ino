#include "POP32.h"
#include "POP32_Huskylens.h"  // ผนวกไลบรารี
HUSKYLENS huskylens;
void setup() {
  Wire.begin();
  while (!huskylens.begin(Wire)) {
    oled.text(1, 0, "Begin failed!");oled.show();
    delay(100);
  }
  oled.clear();
  huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION); // เลือกโหมดรู้จำสี
}
void loop() {
  int ID = knob(1, 4);  // ปรับเลือก ID ในการเรียนรู้
  if (ID == 4) {        // เมื่อ ID เท่ากับ 4 จะเข้าเมนูรีเซตการเรียนรู้
    oled.text(1, 0, "Reset learn");oled.show();
  } else {
    oled.text(1, 0, "Learn ID=%d   ", ID);oled.show();
  }
  if (sw_OK()) {                        // เมื่อปุ่ม OK ถูกกด
    if (ID < 4) {                       // หากตัวแปร ID มีค่าน้อยกว่า 4 ให้เรียนรู้ภาพตัวอย่าง
      if (!huskylens.writeLearn(ID)) {  // ถ้าหากเรียนรู้สำเร็จ
        oled.text(2, 0, "ID%d success", ID);oled.show();
        sound(500,100);sound(1000,150);
        oled.text(2, 0, "            ");oled.show();
      } else {  // ถ้าหากเรียนไม่รู้สำเร็จ
        oled.text(2, 0, "ID%d failed", ID);oled.show();
        sound(500, 250);
        oled.text(2, 0, "         ");oled.show();
      }
    } else {
      huskylens.writeForget();  //รีเซตการเรียนรู้
      oled.text(2, 0, "Success    ");oled.show();
      sound(500, 100);sound(1000, 100);
      oled.text(2, 0, "           ");oled.show();
    }
  }
}
