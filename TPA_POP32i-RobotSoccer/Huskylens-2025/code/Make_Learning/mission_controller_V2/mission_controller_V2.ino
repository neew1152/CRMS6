#include <POP32.h>
#include <POP32_Huskylens.h>
POP32_Huskylens huskylens;
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
// ค่าที่ใช้ปรับหุ่นให้เข้าด้านหน้าตรงลูกบอล
#define rot_Kp 0.35
#define rot_Ki 0.0
#define rot_Kd 0.0
#define sp_rot 160      // ค่า setpoint ที่ลูกบอลอยู่ตรงกลางกล้องแกน x  320/2 = 160
#define rotErrorGap 15  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
#define idleSpd 30      // ค่าความเร็วการหมุนเมื่อไม่เจอลูกบอล
float rot_error, rot_pError, rot_i, rot_d, rot_w;
int ballPosX;
// ค่าที่ใช้ปรับหุ่นให้เข้าใกล้ลูกบอล
#define fli_Kp 1.5
#define fli_Ki 0.0
#define fli_Kd 0.0
#define flingErrorGap 15  // ค่า Error ที่ยอมให้หุ่นหยุดทำงาน
float spFli = 170;        // ค่า setpoint ที่ยอมให้ลูกบอลอยู่ใกล้หุ่นมากที่สุด อาจเริ่มที่จุดกลางจอ แกน Y
float fli_error, fli_pError, fli_i, fli_d, fli_spd;
int ballPosY;
// ค่าที่ใช้ปรับหุ่นให้ตรงทิศอ้างอิง
#define alignErrorGap 4
float  vecCurve, radCurve;
int discoveState = 1;
// ค่าที่ใช้รักษาทิศหุ่นยนต์
#define head_Kp 2.3f
#define head_Ki 0.0f
#define head_Kd 0.5f
float head_error, head_pError, head_w, head_d, head_i;
/* >> ball shooting <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< */
#define limPin A0
#define reloadSpd 60


float thetaRad, vx, vy, spd1, spd2, spd3;
void zeroYaw() {
  Serial1.begin(115200);
  delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5);
  delay(100);
  Serial1.write(0X54);
  delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5);
  delay(100);
  Serial1.write(0X55);
  delay(100);
  // zero degree heading
  Serial1.write(0XA5);
  delay(100);
  Serial1.write(0X52);
  delay(100);
  // automatic mode
}
float pvYaw, lastYaw;
uint8_t rxCnt = 0, rxBuf[8];
bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return;
    rxCnt++;
    if (rxCnt == 8) {  // package is complete
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) {  // data package is correct
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        return true;
      }
    }
  }
  return false;
}
void Auto_zero() {
  zeroYaw();
  getIMU();
  int timer = millis();
  oled.clear();
  oled.text(1, 2, "Setting zero");
  while (abs(pvYaw) > 0.05) {  //วนทำซ้ำจนกว่าองศาจะน้อยกว่า 0.05
    if (getIMU()) {
      oled.text(3, 6, "Yaw: %f  ", pvYaw);
      oled.show();
      beep();
      if (millis() - timer > 5000) {  //เวลาเกิน 5 วิให้ zeroYaw อีกครั้ง
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
  spd1 = vy * cos30 - vx * sin30 + omega;
  spd2 = -vy * cos30 - vx * sin30 + omega;
  spd3 = vx + omega;
  wheel(spd1, spd2, spd3);
}
void heading(float spd, float theta, float spYaw) {
  head_error = spYaw - pvYaw;
  head_i = head_i + head_error;
  head_i = constrain(head_i, -180, 180);
  head_d = head_error - head_pError;
  head_w = (head_error * head_Kp) + (head_i * head_Ki) + (head_d * head_Kd);
  head_w = constrain(head_w, -100, 100);
  holonomic(spd, theta, head_w);
  head_pError = head_error;
}
void shoot() {
  motor(4, reloadSpd);
  delay(150);
  motor(4, 0);
  delay(50);
}
int timer = 0;
void reload() {
  motor(4, reloadSpd);
  timer = 0;
  for (int i = 0; i < 2000; i++) {
    timer++;
    if (analogRead(limPin) > 700) break;
    delay(1);
  }
  if (timer == 2000) {     // ถ้าก้านยิงติด
    motor(4, -reloadSpd);  // เลื่อนก้านยิงไปข้างหน้า
    delay(500);            //ก่อน 0.5 วินาที
    motor(4, reloadSpd);
    timer = 0;
    for (int i = 0; i < 2000; i++) {
      timer++;
      if ((analogRead(limPin) > 700)) break;
      delay(1);
    }
  }
  motor(4, 0);
}

void setup() {
  reload();
  while (!huskylens.begin(Wire)) {
    oled.text(1, 0, "Begin failed!");
    oled.show();
    delay(100);
  }
  delay(3000);
  Auto_zero();  //เรียกใช้ฟังก์ชันเซ็ตมุมอัตโนมัติ
  oled.text(2, 0, "SW_A => Test_Shoot");
  oled.text(3, 0, "SW_B => RUN");
  while (!SW_B()) {
    if (SW_A()) {
      shoot();   //ยิง
      reload();  //เก็บก้านยิง
    }
    getIMU();
    oled.text(0, 0, "Yaw=%f   ", pvYaw);
    oled.show();
  }
}
void loop() {
  if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
    ballPosX = huskylens.blockInfo[1][0].x;
    ballPosY = huskylens.blockInfo[1][0].y;
    for (int i = 0; i < 8; i++) {
      getIMU();
    }
    if (discoveState) {  //วิ่งปรับหุ่นยนต์ให้ใกล้ลูกบอลมากที่สุด discoveState=1
      rot_error = sp_rot - ballPosX;
      rot_d = rot_d + rot_error;
      rot_d = constrain(rot_d, -100, 100);
      rot_d = rot_error - rot_pError;
      rot_pError = rot_error;
      rot_w = (rot_error * rot_Kp) + (rot_i * rot_Ki) + (rot_d * rot_Kd);
      rot_w = constrain(rot_w, -100, 100);

      fli_error = spFli - ballPosY;
      fli_i = fli_i + fli_error;
      fli_i = constrain(fli_i, -100, 100);
      fli_d = fli_error - fli_pError;
      fli_pError = fli_error;
      fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
      fli_spd = constrain(fli_spd, -100, 100);

      holonomic(fli_spd, 90, rot_w);

      if ((abs(rot_error) < rotErrorGap) && (abs(fli_error) < flingErrorGap)) {
        wheel(0, 0, 0);
        lastYaw = pvYaw;  //บันทึกทิศล่า
        discoveState = 0;
      }
    } else {  //จะทำงานเมื่อเจอลูกบอลแต่ทิศไม่ตรงที่จะยิ่ง
      // หุ่นเลือกทิศทางที่ใกล้ที่สุด ที่จะปรับท้ายหุ่นหาลูกบอล
      if (lastYaw < 0) {
        vecCurve = 0;
        radCurve = 15;
      } else {
        vecCurve = 180;
        radCurve = -15;
      }
      holonomic(40, vecCurve, radCurve);
      if (abs(pvYaw) < alignErrorGap) {  //เมื่อทิศอยู่ในค่าที่รับได้
        rot_error = sp_rot - ballPosX;       //คำนวนหาค่า Error ว่าลูกบอลอยู่ตรงกลางหรือไม่
        if (abs(rot_error) < rotErrorGap) {  //ถ้าลูกบอลอยู่ตรงกลางให้ทำการยิง
          holonomic(50, 90, 0);              //เดินหน้าตรงความเร็ว 50%
          delay(1000);                       // นาน 1 วินาที
          beep();
          shoot();   //ยิง
          reload();  //เก็บก้านยิง
        }
        discoveState = 1;
      }
    }
  } else {                            //หมุนตัวหาลูกบอล
    int sideRot = sp_rot - ballPosX;  //คำนวนทิศการหมุนหาลูกบอลเมื่อเจอล่าสุด
    holonomic(0, 0, sideRot / abs(sideRot) * idleSpd);
    discoveState = 1;  //เตรียมพร้อมไปหาลูกบอลเมื่อเจอบอลอีกครั้ง
  }
}
