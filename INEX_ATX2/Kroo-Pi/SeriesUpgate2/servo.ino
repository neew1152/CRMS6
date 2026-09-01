void Testservo() {
  oled.clear();
  servo(6, 0);
  while (1) {
    grip = knob(360);
    servo(6, grip);
    oled.text(3, 3, "Degree = %d", grip);
    oled.show();
    delay(1000);
    if (SW_A()) break;
  }
  beep(500);
  servo(4, 0);
  while (1) {
    grip = knob(360);
    servo(4, grip);
    oled.text(4, 3, "Degree = %d", grip);
    oled.show();
    delay(1000);
    if (SW_A()) break;
  }
  beep(500);
  servo(5, 0);
  while (1) {
    grip = knob(360);
    servo(5, grip);
    oled.text(5, 3, "Degree = %d", grip);
    oled.show();
    delay(1000);
    if (SW_A()) break;
  }
}
/*
void Testservo() {
  oled.clear();
  if (SW_OK()) {
    sound(1000, 200);
    while (1) {
      grip = knob(360);
      servo(6, grip);
      oled.text(3, 3, "servo1 = %d", grip);
      oled.show();
      delay(1000);
      if (SW_A()) break;
    }
  } else if (SW_A()) {
    sound(1000, 200);
    sound(800, 100);
    while (1) {
      grip = knob(360);
      servo(5, grip);
      oled.text(4, 3, "servo2 = %d", grip);
      oled.show();
      delay(1000);
      if (SW_B()) break;
    }
  } else if (SW_B()) {
    sound(1000, 300);
    sound(800, 200);
    sound(600, 100);
    while (1) {
      grip = knob(360);
      servo(1, grip);
      oled.text(4, 3, "servo3 = %d", grip);
      oled.show();
      delay(1000);
    }
  }
}
 */
void Startprogramservo() {
  servo(6, 35);
  delay(100);
  servo(5, 0);
  delay(100);
  servo(4, 116);
  delay(100);
}
void LadyGrip() {
  servo(5, 150);
  delay(100);
  servo(4, 19);
  sound(300, 1000);
}
void LedyPut() {
  servo(4, 116);
  delay(100);
  servo(5, 0);
  delay(100);
}
void Grip() {
  servo(6, 110);
  delay(100);
}
void S4()  //---ยก
{
  delay(100);
  servo(4, 110);
  delay(200);
}
void s4()  //---วาง
{
  delay(100);
  servo(4, 10);
  delay(200);
}
void S5()  //---วางตัวจับ
{
  delay(100);
  servo(5, 170);
  delay(200);
}
void s5()  //---ยกตัวจับ
{
  delay(100);
  servo(5, 0);
  delay(200);
}
void S6()  //---กางที่หนีบ
{
  delay(100);
  servo(6, 10);
  delay(200);
}
void s6()  //---คีบ
{
  delay(100);
  servo(6, 60);
  delay(200);
}
void Box1gripL()
{
  S5();
  s4();
  ao();
  SL(60);
  delay(135);
  MotorStop();
  FD2(40, 40);
  delay(275);
  ao();
  s6();
  S4();
  s5();
  ao();
  SR(60);
  delay(135);
  MotorStop();
}
void Box1gripR()
{
  S5();
  s4();
  ao();
  SR(60);
  delay(135);
  MotorStop();
  FD2(40, 40);
  delay(275);
  ao();
  s6();
  S4();
  s5();
  ao();
  SL(60);
  delay(135);
  MotorStop();
}
void Box1put()
{
}