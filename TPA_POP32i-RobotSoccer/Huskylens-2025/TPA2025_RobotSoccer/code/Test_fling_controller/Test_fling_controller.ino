#include <POP32.h>
#include <POP32_Huskylens.h>
POP32_Huskylens huskylens;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)

// fling controller
#define fli_Kp 1.5
#define fli_Ki 0.0
#define fli_Kd 0.0
#define flingErrorGap 15 // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
float spFli = 160; // ค่า setpoint ที่ยอมให้ลูกบอลอยู่ใกล้หุ่นมากที่สุด อาจเริ่มที่จุดกลางจอ แกน Y
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
  spd1 = vy * cos30 - vx * sin30 + omega;
  spd2 = -vy * cos30 - vx * sin30 + omega;
  spd3 = vx + omega;
  wheel(spd1, spd2, spd3);
}
void setup() {
  while (!huskylens.begin(Wire)) {
    oled.text(1, 0, "Begin failed!");
    oled.show();
    delay(100);
  }
  waitSW_A_bmp();
}
void loop() {
  if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
    ballPosY = huskylens.blockInfo[1][0].y;  // เลือกใช้แกน y  ball ID 1 บล็อกแรก
    fli_error = spFli - ballPosY; 
    fli_i = fli_i + fli_error;
    fli_i = constrain(fli_i, -100, 100);
    fli_d = fli_error - fli_pError;
    fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd; //รวมเทอม PID
    fli_spd = constrain(fli_spd, -100, 100);
    fli_pError = fli_error;
    holonomic(fli_spd, 90, 0);
    if (abs(fli_error) < flingErrorGap) {
      holonomic(0, 0, 0);
      beep();
    }
  }else{
    holonomic(0, 0, 0); //เมื่อไม่เจอให้หยุด
  }
}
