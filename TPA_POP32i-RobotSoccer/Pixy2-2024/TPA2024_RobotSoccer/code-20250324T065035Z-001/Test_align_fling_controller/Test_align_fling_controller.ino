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
#define spRot 160
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
#define alignErrorGap 4
float ali_error, ali_pError, ali_d, ali_vec, vecCurve, radCurve;
int discoveState = 1;

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
float pvYaw, lastYaw;
uint8_t rxCnt = 0, rxBuf[8];
bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return false;
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
void Auto_zero(){
  zeroYaw();
  getIMU();
  int timer = millis();
  oled.clear();
  oled.text(1, 2, "Setting zero");
  while (abs(pvYaw) > 0.02) {
    if(getIMU()){
      oled.text(3, 6,"Yaw: %f  " ,pvYaw);
      oled.show();
      beep();
      if (millis() - timer > 5000) {
        zeroYaw();
        timer = millis();
      }
   }
  }
  oled.clear();
  oled.show();
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
void setup() {
  pixy.init();
  Auto_zero();
  waitSW_A_bmp();
}
void loop() {
  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    ballPosX = pixy.sigInfo[1][0].x;
    ballPosY = pixy.sigInfo[1][0].y;

    int timeOut = millis();
    while (!getIMU()) {
      if (millis() - timeOut > 3000) break;
    }

    if (discoveState) {
      rot_error = spRot - ballPosX;
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
        discoveState = 0;
      }
    } else {
      ali_error = ballPosY - spFli;
      ali_d = ali_error - ali_pError;
      ali_vec = ali_error * ali_Kp + ali_d * ali_Kd;
      ali_pError = ali_error;

      int timeOut = millis();
      while (!getIMU()) {  //ปรับปรุงค่า IMU
        if (millis() - timeOut > 3000) break;
      }
      // select dir
      if (pvYaw < 0) {
        vecCurve = -ali_vec;
        radCurve = 15;
      }
      else {
        vecCurve = 180 + ali_vec;
        radCurve = -15;
      }
      holonomic(40, vecCurve, radCurve);
      if (abs(pvYaw) < alignErrorGap) {
        holonomic(0, 0, 0);
        discoveState = 1;
        beep();
      }
    }
  }else{
    int sideRot = 150 - ballPosX;
    holonomic(0, 0, sideRot / abs(sideRot) * idleSpd);
  }
}
