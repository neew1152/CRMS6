#define BrakeSpeedIMU 100
#define BrakeTimeIMU 10

void InitSerial1(){
  Serial1.begin(115200); 
  delay(100);
}
void zeroYaw()  //กำหนดมุมเริ่มต้นระนาบพื้นโลกเป็น 0
{
  Serial1.write(0XA5);
  Serial1.write(0X54);
  delay(60);
  Serial1.write(0XA5);
  Serial1.write(0X55);
  delay(60);
  Serial1.write(0XA5);
  Serial1.write(0X52);
  delay(60);
}
bool getIMU() {//0-360 องศา
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return false;
    rxCnt++;
    if (rxCnt == 8) {
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) {
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        if(pvYaw<0) pvYaw = 360.000+pvYaw;  //เพิ่มเติม
        return true;
      }
    }
  }
  return false;
}
void ShowYaw() {//0-360 หมุนทวนเข็มนาฬิกา
  oled.clear();
  while (1) 
  {
    if (getIMU()) 
    {
      oled.text(0, 0, "Yaw=%f  ", pvYaw);
      oled.show();
    }
  }
}
void TurnLeftDegree(int TurnSpeed, float Degree, int Origin)  //เลี้ยวซ้ายใช้เข็มทิศ Degree 0-359
{                                                                //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้น
  int Status = 0;
  MotorStop();
  if (Origin != 1) zeroYaw();
  if(WheelDrive==0) sl(TurnSpeed);
  else SL(TurnSpeed);
  for(int i=0; i<10; i++)
  {
    getIMU();
  }
  while (Status == 0) {
    if (getIMU()) {
      if ((pvYaw >= Degree-30) && (pvYaw <= Degree-0)) {
        Status = 1; 
      }
      else if(Degree==0) {
        if ((pvYaw >= 345) && (pvYaw <= 360)) {
        Status = 1;
        }
      }
    }
  }
  Status = 0;
  if(WheelDrive==0) sl(20);
  else SL(20);
  while (Status == 0) {
    if (getIMU()) {
      if ((pvYaw >= Degree-5) && (pvYaw <= Degree+5)) {
        Status = 1; 
      }
      else if(Degree==0) {
        if ((pvYaw >= 355) || (pvYaw <= 5)) {
        Status = 1;
        }
      }
    }
  }
  if(WheelDrive==0) sr(BrakeSpeedIMU);
  else SR(BrakeSpeedIMU);
  delay(BrakeTimeIMU);
  MotorStop();
}
void TurnRightDegree(int TurnSpeed, float Degree, int Origin)  //เลี้ยวขวาใช้เข็มทิศ 0-359
{                                                              //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  int Status = 0;
  MotorStop();
  if (Origin != 1) zeroYaw();
  if(WheelDrive==0) sr(TurnSpeed);
  else SR(TurnSpeed);
  for(int i=0; i<10; i++)
  {
    getIMU();
  }
  while (Status == 0) {
    if (getIMU()) {
      if (Origin == 2) {
        if(Degree==0) break;
        if ((360-pvYaw >= Degree-30) && (360-pvYaw <= Degree-0)) {
        Status = 1; 
        }
      } else if ((pvYaw <= Degree+30) && (pvYaw >= Degree)) {
          Status = 1;
        } else if(Degree>=330) {
          if ((pvYaw <= Degree-330) || (pvYaw >= 330)) Status = 1;
        }
    }
  }
  Status = 0;
  if(WheelDrive==0) sr(20);
  else SR(20);
  while (Status == 0) {
    if (getIMU()) {
      if (Origin == 2) {
        if(Degree==0) break;
        if ((360-pvYaw >= Degree-5) && (360-pvYaw <= Degree+5)) {
          Status = 1;
        } else if(Degree>=355) {
          if ((360-pvYaw >= 355) || (360-pvYaw <= 5)) {
          Status = 1; 
          }
        }
      } else if ((pvYaw <= Degree+5) && (pvYaw >= Degree-5)) {
          Status = 1;
        } else if(Degree>=355) {
          if ((pvYaw <= Degree-355) || (pvYaw >= Degree-5)) Status = 1;
        }
    }
  }
  if(WheelDrive==0) sl(BrakeSpeedIMU);
  else SL(BrakeSpeedIMU);
  delay(BrakeTimeIMU);
  MotorStop();
}