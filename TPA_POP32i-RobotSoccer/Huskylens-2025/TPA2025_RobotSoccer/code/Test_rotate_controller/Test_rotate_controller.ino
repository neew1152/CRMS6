#include <POP32.h>
#include <POP32_Huskylens.h>
POP32_Huskylens huskylens;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)

// rotate controller
#define rot_Kp 0.5
#define rot_Ki 0.0
#define rot_Kd 0.0
#define rotErrorGap 15  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
#define sp_rot 160      // ค่า setpoint ที่ลูกบอลอยู่ตรงกลางกล้องแกน x  320/2 = 160
float rot_error, rot_pError, rot_i, rot_d, rot_w;
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
    ballPosX = huskylens.blockInfo[1][0].x;  // เลือกใช้แกน x  ball ID 1 บล็อกแรก
    rot_error = sp_rot - ballPosX;
    rot_i = rot_i + rot_error;
    rot_i = constrain(rot_i, -100, 100);
    rot_d = rot_error - rot_pError;
    rot_w = rot_error * rot_Kp + rot_i * rot_Ki + rot_d * rot_Kd;
    rot_w = constrain(rot_w, -100, 100);
    holonomic(0, 0, rot_w); //ระบุค่าองศาพิกัดจากแกน y ที่ต้องหมุนไป
    rot_pError = rot_error;
    if (abs(rot_error) < rotErrorGap) { //ถ้าเข้าใกล้จุด setpoint 
      holonomic(0, 0, 0); // ให้หยุด
      beep();
    }
  }
}
