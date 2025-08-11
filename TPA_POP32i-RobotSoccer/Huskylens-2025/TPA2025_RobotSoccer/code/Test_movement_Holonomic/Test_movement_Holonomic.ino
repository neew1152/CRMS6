#include <POP32.h>
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
float thetaRad, vx, vy, spd1, spd2, spd3;
void wheel(int s1, int s2, int s3) {
  motor(1, s1);
  motor(2, s2);
  motor(3, s3);
}
void holonomic(float spd, float theta, float omega) {
  thetaRad = theta * degToRad;
  vx = spd * cos(thetaRad);
  vy = spd * sin(thetaRad);
  spd1 =   vy * cos30 - vx * sin30 + omega;
  spd2 = - vy * cos30 - vx * sin30 + omega;
  spd3 =   vx + omega;
  wheel(spd1, spd2, spd3);
}
void setup() {
}
void loop() {
  waitSW_A_bmp();
  holonomic(30, 0, 0);
  delay(2000);
  holonomic(30, 90, 0);
  delay(2000);
  holonomic(30, 180, 0);
  delay(2000);
  holonomic(30, 270, 0);
  delay(2000);
  ao();
}

