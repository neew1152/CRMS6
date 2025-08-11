#include <POP32.h>
void zeroYaw() {
  Serial1.begin(115200);delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5);delay(100);Serial1.write(0X54);delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5);delay(100);Serial1.write(0X55);delay(100);
  // zero degree heading
  Serial1.write(0XA5);delay(100);Serial1.write(0X52);delay(100);
  // automatic mode
}
float pvYaw;
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
      }}}
  return false;
}
void setup() {
 zeroYaw();
}
void loop() {
  if (SW_A()) {
    zeroYaw();
  }
  getIMU();
  oled.text(0, 0, "Yaw=%f   ",pvYaw);
  oled.show();
}
