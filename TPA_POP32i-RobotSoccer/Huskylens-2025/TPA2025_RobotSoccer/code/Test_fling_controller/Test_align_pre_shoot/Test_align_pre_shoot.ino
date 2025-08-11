#include <POP32.h>
#include <POP32_Huskylens.h>
POP32_Huskylens huskylens;

#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
// align controller
#define alignErrorGap 4 // ค่าองศาที่ยอมรับได้
float vecCurve, radCurve;

float thetaRad, vx, vy, spd1, spd2, spd3;
void zeroYaw() {
  Serial1.begin(115200);
  delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5);
  Serial1.write(0X54);
  delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5);
  Serial1.write(0X55);
  delay(100);
  // zero degree heading
  Serial1.write(0XA5);
  Serial1.write(0X52);
  delay(100);
  // automatic mode
}
float pvYaw;
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
void setup() {
  while (!huskylens.begin(Wire)) {
    oled.text(1, 0, "Begin failed!");
    oled.show();
  }
  Auto_zero();  //เรียกใช้ฟังก์ชันเซ็ตมุมอัตโนมัติ
  oled.text(4, 0, "SW_B => RUN");
  while (!SW_B()) {
    getIMU();
    oled.text(0, 0, "Yaw=%f   ", pvYaw);
    oled.show();
  }
}
void loop() {
  getIMU();
  // หุ่นเลือกทิศทางที่ใกล้ที่สุด ที่จะปรับท้ายหุ่นหาลูกบอล
  if (pvYaw > 0) { 
    //องศาติด + หมุนแบบโค้งตามเข็มนาฬิกา
    vecCurve = 180; 
    radCurve = -15;
  } else {
    //องศาติด - หมุนแบบโค้งทวนเข็มนาฬิกา
    vecCurve = 0;
    radCurve = 15;
  }
  holonomic(40, vecCurve, radCurve);
  if (abs(pvYaw) < alignErrorGap) { //เมื่อทิศอยู่ในค่าที่รับได้
    holonomic(0, 0, 0);//หยุดทำงาน
    beep();
  }
}
