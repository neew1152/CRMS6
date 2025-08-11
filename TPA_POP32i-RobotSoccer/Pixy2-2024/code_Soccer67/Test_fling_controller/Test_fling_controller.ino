#include <POP32.h>
#include <POP32_Pixy2.h>
POP32_Pixy2 pixy;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)

// fling controller
#define fli_Kp 1.5
#define fli_Ki 0.0
#define fli_Kd 0.0
#define flingErrorGap 15
float spFli = 120;
float fli_error, fli_pError, fli_i, fli_d, fli_spd;
int ballPosY;

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
  pixy.init();
  waitSW_A_bmp();
}

void loop() {
  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    ballPosY = pixy.sigInfo[1][0].y;
    fli_error = spFli - ballPosY;
    fli_i = fli_i + fli_error;
    fli_i  = constrain(fli_i , -100, 100);
    fli_d = fli_error - fli_pError;
    fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
    fli_spd = constrain(fli_spd , -100, 100);
    fli_pError = fli_error;
    holonomic(fli_spd, 90, 0);
    if (abs(fli_error) < flingErrorGap) {
      holonomic(0, 0, 0);
      beep();
    }
  }
}
