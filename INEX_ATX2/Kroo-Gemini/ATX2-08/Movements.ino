// ฟังก์ชันช่วยเพื่อดึงค่า Ref ให้ตรงกับพอร์ต sensor ที่รับเข้ามา
int getRefValue(int sensor) {
  switch (sensor) {
    case 0: return Ref_L0;
    case 1: return Ref_L1;
    case 2: return Ref_R2;
    case 3: return Ref_R3;
    default: return 600;  // ค่าเผื่อกันเหนียวกรณีระบุพอร์ตผิด
  }
}

// เดินตามเส้นตามจำนวนรอบลูป
void ForwardTrackLineTime(int speed, int time) {
  for (int i = 0; i <= time; i++) {
    TrackLine(speed);
  }
  MotorStop();
}

// เดินตามเส้นจนกว่าเซ็นเซอร์จะเจอเส้นตัดดำ
void ForwardTrackLineStop(int speed, int sensor) {
  int refVal = getRefValue(sensor);  // ดึงค่า Ref ให้ตรงกับ sensor
  while (1) {
    if (analog(sensor) < refVal) break;  // เจอดำ (ค่าน้อยกว่า Ref) ให้ออกจากลูป
    TrackLine(speed);
  }
  MotorStop();
}

// เดินหน้าตรงจนกว่าจะเจอเส้นดำ
void ForwardLineStop(int speed1, int speed2, int sensor) {
  int refVal = getRefValue(sensor);  // ดึงค่า Ref ให้ตรงกับ sensor
  while (1) {
    if (analog(sensor) < refVal) break;  // เจอดำ (ค่าน้อยกว่า Ref) ให้ออกจากลูป
    fd2(speed1, speed2);
  }
  MotorStop();
}

// เดินหน้าตามเวลาที่กำหนด (มิลลิวินาที)
void ForwardDelay(int speed1, int speed2, int time) {
  fd2(speed1, speed2);
  delay(time);
  MotorStop();
}

// หมุนตัวทางซ้าย (แบบตาบอดก่อนตามเวลาที่กำหนด แล้วหมุนต่อจนกว่าจะเจอเส้น)
void SLsensor(int sensor, int speed, int time) {
  sl(speed);
  delay(time);
  MotorStop();

  int refVal = getRefValue(sensor);  // ดึงค่า Ref ให้ตรงกับ sensor
  // อ่านค่าจาก sensor โดยตรง ไม่ต้องไปยุ่งกับตัวแปร L1 เดิม
  while (analog(sensor) > refVal) {  // ถ้ายังเป็นขาว (> ref) ให้หมุนต่อ
    sl(speed);
  }
  MotorStop();
}

// หมุนตัวทางขวา (แบบตาบอดก่อนตามเวลาที่กำหนด แล้วหมุนต่อจนกว่าจะเจอเส้น)
void SRsensor(int sensor, int speed, int time) {
  sr(speed);
  delay(time);
  MotorStop();

  int refVal = getRefValue(sensor);  // ดึงค่า Ref ให้ตรงกับ sensor
  // อ่านค่าจาก sensor โดยตรง ไม่ต้องไปยุ่งกับตัวแปร R2 เดิม
  while (analog(sensor) > refVal) {  // ถ้ายังเป็นขาว (> ref) ให้หมุนต่อ
    sr(speed);
  }
  MotorStop();
}

// ลอจิกการเดินตามเส้น (อิงค่า > Ref คือพื้นขาว, < Ref คือเส้นดำ)
void TrackLine(int speed) {
  L1 = analog(1);
  R2 = analog(2);

  if (L1 > Ref_L1 && R2 > Ref_R2) fd(speed);       // ขาว-ขาว -> เดินหน้า
  else if (L1 < Ref_L1 && R2 > Ref_R2) sl(speed);  // ดำ-ขาว  -> เลี้ยวซ้ายกลับเข้าเส้น
  else if (L1 > Ref_L1 && R2 < Ref_R2) sr(speed);  // ขาว-ดำ  -> เลี้ยวขวากลับเข้าเส้น
}

// หยุดมอเตอร์
void MotorStop() {
  ao();
  delay(100);
}