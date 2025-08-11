#include <POP32.h>
#include <POP32_Pixy2.h>
POP32_Pixy2 pixy;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
// rotate controller
#define rot_Kp 0.35
#define rot_Ki 0.0
#define rot_Kd 0.0
#define idleSpd 30  // speed when not discovered ball
#define rotErrorGap 15
#define spRot 150  //x
float rot_error, rot_pError, rot_i, rot_d, rot_w;
int ballPosX;
// fling controller
#define fli_Kp 1.5
#define fli_Ki 0.0
#define fli_Kd 0.0
#define flingErrorGap 20
float spFli = 180;  //y
float fli_error, fli_pError, fli_i, fli_d, fli_spd;
int ballPosY;
// align controller
#define ali_Kp 2.75
#define ali_Kd 0.0
#define alignErrorGap 4
float ali_error, ali_pError, ali_d, ali_vec, vecCurve, radCurve;
int discoveState = 1;

float thetaRad, vx, vy, spd1, spd2, spd3;

void setup() {
  Serial.begin(115200);
  oled.clear();
  pixy.init();
  while (1) {
    if (SW_A()) break;
    else if (pixy.updateBlocks() && pixy.sigSize[1]) {
      ballPosX = pixy.sigInfo[1][0].x;
      ballPosY = pixy.sigInfo[1][0].y;
      oled.text(5, 5, "%d ", ballPosY);
      oled.show();
    }
  }
  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    ballPosX = pixy.sigInfo[1][0].x;
    ballPosY = pixy.sigInfo[1][0].y;
    oled.text(5, 5, "%d ", ballPosY);
    oled.show();
  } else {
    oled.text(5, 5, "Not detect");
    oled.show();
  }
}
void loop() {

  oled.clear();
  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    ballPosX = pixy.sigInfo[1][0].x;
    ballPosY = pixy.sigInfo[1][0].y;
    oled.text(5, 5, "%d ", ballPosY);
    oled.show();

    if (ballPosY > 180) {
      ao();
      while (1)
        ;
    } else {
      wheel(20, -20, 0);
      oled.text(5, 5, "%d ", ballPosY);
      oled.show();
    }
  }
}
void wheel(int s1, int s2, int s3) {
  motor(1, s1);
  motor(2, s2);
  motor(3, s3);
}
void holonomic(float spd, float theta, float omega) {
  thetaRad = theta * degToRad;
  vx = spd * cos(thetaRad);
  vy = spd * sin(thetaRad);
  spd1 = vy * cos30 - vx * sin30 + omega;
  spd2 = -vy * cos30 - vx * sin30 + omega;
  spd3 = vx + omega;
  wheel(spd1, spd2, spd3);
}
// Convert Serial to OLED by ChatGPT-4o
// Prompt: Convert Display, Serial to oled