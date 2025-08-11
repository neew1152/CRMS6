#include <POP32.h>
void zeroYaw() {
  Serial1.begin(115200);delay(100);
  // Sets data rate to 115200 bps
  Serial1.write(0XA5);delay(10);Serial1.write(0X54);delay(100);
  // pitch correction roll angle
  Serial1.write(0XA5);delay(10);Serial1.write(0X55);delay(100);
  // zero degree heading
  Serial1.write(0XA5);delay(10);Serial1.write(0X52);delay(100);
  // automatic mode
}
float pvYaw,pvRoll,pvPitch;
uint8_t rxCnt = 0, rxBuf[8];
bool getIMU() {
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return;
    rxCnt++;
    if (rxCnt == 8) { // package is complete
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) { // data package is correct
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        pvPitch = (int16_t)(rxBuf[3] << 8 | rxBuf[4]) / 100.f;
        pvRoll = (int16_t)(rxBuf[5] << 8 | rxBuf[6]) / 100.f;
        return true;
      }}}
  return false;
}
void setup() {
  Serial.begin(115200);
while(!Serial);
  zeroYaw();
}
void loop() {
  if (SW_A()) {
    zeroYaw();
  }
  getIMU();

Serial.print(pvYaw,2);
Serial.print("\t");
Serial.print(pvPitch,2);
Serial.print("\t");
Serial.println(pvRoll,2);
 // oled.text(0, 0, "  Yaw=%f   ",pvYaw);
 // oled.text(1, 0, "Pitch=%f   ",pvPitch);
 // oled.text(2, 0, " Roll=%f   ",pvRoll);
 // oled.show();

}
