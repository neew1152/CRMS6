#include <POP32.h>
#include <POP32_Huskylens.h>
POP32_Huskylens huskylens;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
// rotate controller
#define rot_Kp 0.35
#define rot_Ki 0.0
#define rot_Kd 0.0
#define sp_rot 160      // ค่า setpoint ที่ลูกบอลอยู่ตรงกลางกล้องแกน x  320/2 = 160
#define rotErrorGap 15  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
float rot_error, rot_pError, rot_i, rot_d, rot_w;
int ballPosX;
// fling controller
#define fli_Kp 1.5
#define fli_Ki 0.0
#define fli_Kd 0.0
#define flingErrorGap 15  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
float spFli = 160;        // ค่า setpoint ที่ยอมให้ลูกบอลอยู่ใกล้หุ่นมากที่สุด อาจเริ่มที่จุดกลางจอ แกน Y
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
  if (huskylens.updateBlocks() && huskylens.blockSize[1]) {  //เมื่อเจอลูกบอล ID 1
    /* คำนวน ค่าความเร็วในแนวแกน x */
    ballPosX = huskylens.blockInfo[1][0].x;
    rot_error = 150 - ballPosX;
    rot_i = rot_i + rot_error;
    rot_i = constrain(rot_i, -100, 100);
    rot_d = rot_error - rot_pError;
    rot_pError = rot_error;
    rot_w = (rot_error * rot_Kp) + (rot_i * rot_Ki) + (rot_d * rot_Kd);
    rot_w = constrain(rot_w, -100, 100);
    
    /* คำนวน ค่าความเร็วในแนวแกน y */
    ballPosY = huskylens.blockInfo[1][0].y;
    fli_error = spFli - ballPosY;
    fli_i = fli_i + fli_error;
    fli_i = constrain(fli_i, -100, 100);
    fli_d = fli_error - fli_pError;
    fli_pError = fli_error;
    fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
    fli_spd = constrain(fli_spd, -100, 100);

    /* หุ่นหยุดเมื่อ ลูกบอลอยู่ในตำแหน่งที่ยอมรับได้ */
    if ((abs(rot_error) < rotErrorGap) && (abs(fli_error) < flingErrorGap)){
        wheel(0, 0, 0);
        beep();
      }
    else { /* หุ่นทำงานปรับหาลูกบอลตามที่คำนวนได้ */
      holonomic(fli_spd, 90, rot_w);
    }
  }else{ // เมื่อไม่พบลูกบอล
    holonomic(0, 0, (rot_w / abs(rot_w) * 20)); //หมุนตัวไปทิศล่าสุดที่ลูกบอลหายไป
  }
}
