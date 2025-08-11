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
float rot_error, rot_pError, rot_i, rot_d, rot_w;
int ballPosX;
// fling controller
#define fli_Kp 1.5
#define fli_Ki 0.0
#define fli_Kd 0.0
#define flingErrorGap 20
float spFli = 130;
float fli_error, fli_pError, fli_i, fli_d, fli_spd;
int ballPosY;
// align controller
#define ali_Kp 2.75
#define ali_Kd 0.0
#define alignErrorGap 3
float ali_error, ali_pError, ali_d, ali_vec, vecCurve, radCurve;
int discoveState = 1;
/* >> ball shooting <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */
#define limPin A0
#define reloadSpd 60

float thetaRad, vx, vy, spd1, spd2, spd3;
void zeroYaw() {
  Serial1.begin(115200); delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5); Serial1.write(0X54); delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5); Serial1.write(0X55); delay(100);
  // zero degree heading
  Serial1.write(0XA5); Serial1.write(0X52); delay(100);
  // automatic mode
}
volatile float pvYaw, lastYaw;
volatile uint8_t rxCnt = 0, rxBuf[8];
//float pvYaw, lastYaw;
//uint8_t rxCnt = 0, rxBuf[8];
bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return;
    rxCnt++;
    if (rxCnt == 8) { // package is complete
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) { // data package is correct
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        return true;
      }
    }
  }
  return false;
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
  spd1 =   vy * cos30 - vx * sin30 + omega;
  spd2 = - vy * cos30 - vx * sin30 + omega;
  spd3 =   vx + omega;
  wheel(spd1, spd2, spd3);
}
/* heading ..............   */
#define head_Kp 2.3f
#define head_Ki 0.0f
#define head_Kd 0.5f
float head_error, head_pError, head_w , head_d, head_i;
void heading(float spd, float theta, float spYaw) {
  head_error = spYaw - pvYaw;
  head_i = head_i  + head_error;
  head_i = constrain(head_i , -180, 180);
  head_d =  head_error - head_pError;
  head_w = (head_error * head_Kp) + (head_i * head_Ki) + (head_d * head_Kd);
  head_w = constrain(head_w , -100, 100);
  holonomic(spd, theta, head_w);
  head_pError = head_error;
}
void shoot() {
  motor(4, reloadSpd); delay(150);
  motor(4, 0); delay(50);
}
void reload() {
  motor(4, reloadSpd);
  for (int i = 0; i < 2000; i++) {
    if (in(limPin))break;
    delay(1);
  }
  motor(4, 0);
}
void setup() {
  pixy.init();
  reload();
  zeroYaw();
  oled.mode(2);
  oled.text(6, 0, "Press SW_B zeroYaw");
  oled.text(7, 0, "Press SW_A Run....");
  oled.show();
  while (!SW_A()) {
    if (SW_B()) {
      zeroYaw();
    }
    getIMU();
    oled.text(0, 0, "Yaw=%f     ", pvYaw);
    oled.show();
  }
}
void loop() {

  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    ballPosX = pixy.sigInfo[1][0].x;
    ballPosY = pixy.sigInfo[1][0].y;
    for (int i = 0; i < 8; i++) {
      getIMU();
    }
    if (discoveState) {
      rot_error = 150 - ballPosX;
      rot_d = rot_d + rot_error;
      rot_d = constrain(rot_d, -100, 100);
      rot_d = rot_error - rot_pError;
      rot_pError = rot_error;
      rot_w = (rot_error * rot_Kp) + (rot_i * rot_Ki) + (rot_d * rot_Kd);
      rot_w = constrain(rot_w, -100, 100);

      fli_error = spFli - ballPosY;
      fli_i = fli_i + fli_error;
      fli_i  = constrain(fli_i , -100, 100);
      fli_d = fli_error - fli_pError;
      fli_pError = fli_error;
      fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
      fli_spd = constrain(fli_spd , -100, 100);

      holonomic(fli_spd, 90, rot_w);

      if ((abs(rot_error) < rotErrorGap) && (abs(fli_error) < flingErrorGap)) {
        wheel(0, 0, 0);
        lastYaw = pvYaw;
        discoveState = 0;
      }
    } else {
      ali_error = ballPosY - spFli;
      ali_d = ali_error - ali_pError;
      ali_vec = ali_error * ali_Kp + ali_d * ali_Kd;
      ali_pError = ali_error;
      // select dir
      if (lastYaw < 0) {
        vecCurve = -ali_vec;
        radCurve = 15;
      }
      else {
        vecCurve = 270 + ali_vec;
        radCurve = -15;
      }
      holonomic(40, vecCurve, radCurve);
      if (abs(pvYaw) < alignErrorGap) {
        holonomic(0, 0, 0);
        discoveState = 1;
        if ((abs(150 - ballPosX) < rotErrorGap) && (abs(spFli - ballPosY) < flingErrorGap)) {
          beep();
          unsigned long loopTimer = millis();
          while (1) {
            getIMU(); heading(100, 90, 0);
            if (millis() - loopTimer >= 250)break;
          }
          shoot();
          reload();
        }
      }
    }
  } else {
    int sideRot = rot_error;
    holonomic(0, 0, sideRot / abs(sideRot) * idleSpd);
    reload();
  }
}
