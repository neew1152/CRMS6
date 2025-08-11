#include <POP32.h>
#define degToRad 0.0174f
#define sin30 sin(30.f * degToRad)
#define cos30 cos(30.f * degToRad)
float thetaRad, vx, vy, spd1, spd2, spd3;
uint8_t rxCnt = 0, rxBuf[8];
float pvYaw;
#define head_Kp 0.5f //ปรับความคลาดเคลื่อนได้รวดเร็ว
#define head_Ki 0.0f //ปรับช่วยให้หุ่นยนต์หมุนเข้าใกล้สู่จุดที่ค่าผิดผลาดเท่ากับ 0 มากขึ้น
#define head_Kd 0.0f //ปรับช่วยลดการสะบัด ให้หุ่นยนต์เข้าสู่จุดที่ค่าผิดผลาดเท่ากับ 0 ได้เร็ว
float head_error, head_pError, head_w, head_d, head_i;
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
bool getIMU() {  //อ่านค่าทิศอ้างอิง
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
void zeroYaw() {
  Serial1.begin(115200);delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5);Serial1.write(0X54);delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5); Serial1.write(0X55);delay(100);
  // zero degree heading
  Serial1.write(0XA5);Serial1.write(0X52);delay(100);
  // automatic mode
}
void Auto_zero(){
  zeroYaw();getIMU();
  int timer = millis();
  oled.clear(); oled.text(1, 2,"Setting zero");
  while (abs(pvYaw) > 0.05){ //วนทำซ้ำจนกว่าองศาจะน้อยกว่า 0.05 
    if(getIMU()){
      oled.text(3, 6,"Yaw: %f  " ,pvYaw);oled.show();
      beep();
      if (millis() - timer > 5000){ //เวลาเกิน 5 วิให้ zeroYaw อีกครั้ง
        zeroYaw();
        timer = millis();
      }}}
  oled.clear();oled.show();
}
void heading(float spd, float theta, float spYaw) {
  head_error = spYaw - pvYaw;  //หาค่า Error จากทิศอ้างอิง
  head_i = head_i + head_error;
  head_i = constrain(head_i, -180, 180);
  head_d = head_error - head_pError;
  head_w = (head_error * head_Kp) + (head_i * head_Ki) + (head_d * head_Kd);
  head_w = constrain(head_w, -100, 100);
  holonomic(spd, theta, head_w);
  head_pError = head_error;
}
void setup() {
  Auto_zero(); //เรียกใช้ฟังก์ชันเซ็ตมุมอัตโนมัติ
  waitSW_A_bmp();
}
void loop() {
  if (SW_A()) {  //กดปุ่ม A เพื่อเรียกใช้ฟังก์ชันเซ็ตมุมอัตโนมัติ
    wheel(0,0,0);
    Auto_zero(); 
  }
  getIMU();
  heading(0, 0, 0);
}
