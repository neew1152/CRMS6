#include <POP32.h>
void zeroYaw() {
  Serial1.begin(115200);delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5);Serial1.write(0X54);delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5);Serial1.write(0X55);delay(100);
  // zero degree heading
  Serial1.write(0XA5);Serial1.write(0X52);delay(100);
  // automatic mode
}
float pvYaw;
uint8_t rxCnt = 0, rxBuf[8];
bool getIMU() {
  //อ่านค่าองศามุม Yaw
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return false;
    rxCnt++;
    if (rxCnt == 8) { // package is complete
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) { // data package is correct
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        return true;
      }}}
  return false;
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
void setup() {
  Auto_zero(); //เรียกใช้ฟังก์ชันเซ็ตมุมอัตโนมัติ
}
void loop() {
  if (SW_A()) {  //กดปุ่ม A เพื่อเรียกใช้ฟังก์ชันเซ็ตมุมอัตโนมัติ
    Auto_zero(); 
  }
  getIMU();
  oled.text(0, 0, "Yaw=%f   ",pvYaw);
  oled.show();
}
