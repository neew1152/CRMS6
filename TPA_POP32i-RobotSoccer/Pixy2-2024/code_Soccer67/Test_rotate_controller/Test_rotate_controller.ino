#include <POP32.h>
#include <POP32_Pixy2.h>
POP32_Pixy2 pixy;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)

// rotate controller
#define rot_Kp 0.5
#define rot_Ki 0.0
#define rot_Kd 0.2
#define rotErrorGap 15
float rot_error, rot_pError, rot_i,rot_d,rot_w;
// overall
int ballPosX;

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
  if (pixy.updateBlocks() && pixy.sigSize[1])  {
    ballPosX = pixy.sigInfo[1][0].x; // ball signature at index 0
    rot_error = 150 - ballPosX;
    rot_d = rot_d + rot_error;
    rot_d = constrain(rot_d,-100,100);
    rot_d = rot_error - rot_pError;
    rot_w = rot_error * rot_Kp + rot_i * rot_Ki + rot_d * rot_Kd;
    rot_w = constrain(rot_w,-100,100);
    holonomic(0, 0, rot_w);
    rot_pError = rot_error;
     if (abs(rot_error) < rotErrorGap) {
        holonomic(0, 0, 0);
        beep();
      }
  }
}
