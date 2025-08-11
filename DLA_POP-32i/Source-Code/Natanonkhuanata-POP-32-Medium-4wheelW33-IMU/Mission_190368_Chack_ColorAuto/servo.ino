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
void Startprogramservo() {
  servo(6, 20);
  delay(100);
  servo(5, 20);
  delay(100);
  servo(4, 116);
  delay(100);
}
void ReadyGrip() {
  servo(5, 180);
  delay(100);
  servo(4, 15);
  sound(300, 1000);
}
void ReadyPut() {
  servo(5, 180);
  delay(400);
  servo(4, 135);
  delay(100);
  servo(5, 20);
  delay(100);
}
void ReadyPut_01() {
  servo(5, 141);
  delay(100);
  servo(4, 50);
  delay(100);
  sound(3000, 500);
  sound(2000, 400);
  sound(1000, 200);
  sound(500, 200);
}
void Grip() {
  servo(6, 110);
  delay(100);
}
void downhelp() {
  servo(4, 40);
  delay(100);
}
void Put() {
  servo(4, 30);
  delay(100);
  servo(5,145);
  delay(100);
  for (int i = 110; i >= 20; i -= 5) {
    servo(6, i);
    delay(50);
  }
}



/*                                     box สูง 15                          */

void ReadyPut_02() {
  servo(5, 116);
  delay(100);
  servo(4, 56);
  delay(100);
  sound(3000, 500);
  sound(2000, 400);
  sound(1000, 200);
  sound(500, 200);
}
void Put_02() {
  servo(4, 45);
  delay(100);
  for (int i = 110; i >= 20; i -= 5) {
    servo(6, i);
    delay(50);
  }
}

/*                ที่วางกระป๋องสูง 30                                                  */


void ReadyPut_03() {
  servo(5, 145);
  delay(100);
  servo(4, 75);
  delay(100);
  sound(3000, 500);
  sound(2000, 400);
  sound(1000, 200);
  sound(500, 200);
}
void downhelp_03() {
  servo(5, 115);
  delay(100);
}
void Put_03() {
  servo(4, 69);
  delay(100);
  servo(5, 102);
  delay(100);
  for (int i = 110; i >= 20; i -= 5) {
    servo(6, i);
    delay(50);
  }
}