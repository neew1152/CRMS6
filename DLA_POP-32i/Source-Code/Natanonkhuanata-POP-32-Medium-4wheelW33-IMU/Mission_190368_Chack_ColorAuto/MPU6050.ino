#define BrakeSpeedIMU 90
#define BrakeTimeIMU 10


void zeroYaw()  //กำหนดมุมเริ่มต้นระนาบพื้นโลกเป็น 0
{
  Serial1.begin(115200);
  delay(100);
  Serial1.write(0XA5);
  Serial1.write(0X54);
  delay(60);
  Serial1.write(0XA5);
  Serial1.write(0X55);
  delay(60);
  Serial1.write(0XA5);
  Serial1.write(0X52);
  delay(60);
  getIMU();
  getIMU();
  getIMU();
  getIMU();
  getIMU();
  getIMU();
  beep();
}
bool getIMU() {  //0-360 องศา
  while (Serial1.available()) {
    rxBuf[rxCnt] = Serial1.read();
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return false;
    rxCnt++;
    if (rxCnt == 8) {
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) {   //data is correct ?
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;
        if (pvYaw < 0) pvYaw = 360.000 + pvYaw;  //เพิ่มเติม
        return true;
      }
    }
  }
  return false;
}
void ShowYaw() {  //0-360 หมุนทวนเข็มนาฬิกา
  oled.clear();
  while (1) {
    if (getIMU()) {
      oled.text(0, 0, "Yaw=%f  ", pvYaw);
      oled.show();
    }
  }
}
void Auto_zero(){
  zeroYaw();
  getIMU();
  int timer = millis();
  oled.clear();
  oled.text(1, 2, "Setting zero");
  oled.show();
  while (abs(pvYaw) > 0.02) {
    if(getIMU()){
      oled.text(3, 6,"Yaw: %f  " ,pvYaw);
      oled.show();
      if (millis() - timer > 5000) {
        zeroYaw();
        timer = millis();
      }
   }
  }
  oled.clear();
  oled.show();
}
void TurnLeftDegree(int TurnSpeed, float Degree, int Origin)  //เลี้ยวซ้ายใช้เข็มทิศ Degree 0-359
{                                                                //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้น
  int Status = 0;
  MotorStop();
  if (Origin != 1) zeroYaw();
  SL(BrakeSpeedIMU);
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
  else SL(40);
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
  MotorStop();
}
void dGS_Left(int TurnSpeed, float Degree, int Origin)  //เลี้ยวซ้ายใช้เข็มทิศ Degree 0-359
{                                                                //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้น
  int Status = 0;
  MotorStop();
  if (Origin != 1) zeroYaw();
  SL(TurnSpeed);
  getIMU();
  float target_Start = pvYaw;
  while ((pvYaw - target_Start <  Degree + 1.5)) {
    getIMU();
  }
  MotorStop();
}
void TurnRightDegree(int TurnSpeed, float Degree, int Origin)  //เลี้ยวขวาใช้เข็มทิศ 0-359
{                                                              //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  int Status = 0;
  MotorStop();
  if (Origin != 1) zeroYaw();
  if(WheelDrive==0) sr(TurnSpeed);
  else SR(TurnSpeed - 5);
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
  else SR(35);
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
  MotorStop();
}
void GS(int spd,float C,float os){ //gyro spin
  getIMU();
  float A =pvYaw;
  if(A<0)A+=360; //ตรงนี้คือส่วนที่ทำให้หุ่นมีค่าเป็น 360 คือบอกว่าหุ่นยนตรง ถ้ามันน้อยกว่า 0  
  if(C==A)return;
  float B = (A<180)?A+180:A-180;
  if(B>A){
    if(C>A&&C<=B){ // เช็คว่ามันควรหมุนไปทางไหนตามองศาที่หุ่นมันอยู่
      
      getIMU();
      float D = (pvYaw>=0)?pvYaw:pvYaw+360;
      while(D<C-os||D>C+os){getIMU();D = (pvYaw>=0)?pvYaw:pvYaw+360;SL(spd);}
      MotorStop();
    }
    else{
      
      getIMU();
      float D = (pvYaw>=0)?pvYaw:pvYaw+360;
      while(D<C-os||D>C+os){getIMU();D = (pvYaw>=0)?pvYaw:pvYaw+360;SR(spd);} // จะออกก่อนต่อเมื่อ D = C
      MotorStop();
    }
  }
  else{
    if(C>=B&&C<A){
      
      getIMU();
      float D = (pvYaw>=0)?pvYaw:pvYaw+360;
      while(D<C-os||D>C+os){getIMU();D = (pvYaw>=0)?pvYaw:pvYaw+360;SR(spd);}
      MotorStop();
    }
    else{
      
      getIMU();
      float D = (pvYaw>=0)?pvYaw:pvYaw+360;
      while(D<C-os||D>C+os){getIMU();D = (pvYaw>=0)?pvYaw:pvYaw+360;SL(spd);}
      MotorStop();
    }
  }
}
void dGS(float C){
  GS(50,C,1.5);
  GS(30,C,1);
}

float angleCal(float cur, float tar) {
    float diff = fmod((tar - cur + 540.0), 360.0) - 180.0;
    return diff;
}


void DS2(float speed, float C, float os) {
    getIMU();
    float diff = angleCal(pvYaw, C);

    
    while (fabs(diff) > os) {
        
        if (diff > 0) {
            SL(speed);
        } else {
            SR(speed);
        }
        getIMU();
        diff = angleCal(pvYaw, C);
    }
    MotorStop();
}


void dGS2(float C) {
    DS2(40, C, 1);
    DS2(20, C, 0.8);
}