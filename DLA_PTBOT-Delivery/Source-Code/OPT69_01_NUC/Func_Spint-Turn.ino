void Turn_Curve(int speed, float timer, char select){

  delay(delayALL);
  if (select == 'L') {
    motorWrite(1, speed);
    motorWrite(2, speed);
  } else if (select == 'R') {
    motorWrite(1, speed);
    motorWrite(2, speed);
  }
  delay(delayALL);

  motorStop(); delay(100);
}

void spinDegree_original(int relative_degree) {
  int min_speed = 18;                             // ความเร็วต่ำสุด
  int max_speed = 60;                            // ความเร็วสูงสุด
  float kp = 1;                                 // KP
  float kd = 3.0;                                 // KD
  float small_angle_threshold = 30;               // หุ่นยนต์จะใช้ความเร็วต่ำสุดเมื่อเข้าใกล้องศาที่กำหนด
  float stop_threshold = 2.0;                     // กำหนดความคลาดเคลื่อนที่ยอมรับได้
  //  if (relative_degree > 0) stop_threshold = 11.5485;  // กำหนดความคลาดเคลื่อนที่ยอมรับได้ Spin Right 90
  //  else stop_threshold = 3.32585;                      // กำหนดความคลาดเคลื่อนที่ยอมรับได้ Spin Left -90
  unsigned long timer_turn = 0;
  float previous_error = 0;
  float target_degree = current_degree + relative_degree;
  if (target_degree > 180) target_degree -= 360;
  if (target_degree < -180) target_degree += 360;
  current_degree = target_degree;
  while (1) {
    float current_angle = angleRead(YAW);
    float error = target_degree - current_angle;
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    if (error > stop_threshold && error < small_angle_threshold) {
      // motorWrite(min_speed, min_speed, -min_speed, -min_speed);
      motorWrite(1, min_speed);
      motorWrite(2, -min_speed);
      timer_turn = millis();
    } else if (error < -stop_threshold && error > -small_angle_threshold) {
      // motorWrite(-min_speed, -min_speed, min_speed, min_speed);
      motorWrite(1, -min_speed);
      motorWrite(2, min_speed);
      timer_turn = millis();
    } else if (error >= -stop_threshold && error <= stop_threshold) {
      motorStop();
      if (millis() - timer_turn >= 50) break;
    } else {
      // motorWrite(pd_value, pd_value, -pd_value, -pd_value);
      motorWrite(1, pd_value);
      motorWrite(2, -pd_value);
      timer_turn = millis();
    }
    previous_error = error;
  }
}

void spinDegree_Enhanced(int relative_degree) {
  int min_speed = 18;                             // ความเร็วต่ำสุด (จุดที่มอเตอร์เริ่มขยับได้พอดี)
  int max_speed = 60;                             // ความเร็วสูงสุด
  float kp = 1;                                 // KP (อาจต้องเพิ่มจาก 0.8 นิดหน่อยเพราะไม่มีโหมดบังคับลดความเร็วแล้ว)
  float kd = 7;                                 // KD (ช่วยเบรกไม่ให้หุ่นเลยเป้า)
  float stop_threshold = 1.5;                     // กำหนดความคลาดเคลื่อนที่ยอมรับได้ (องศา)

  unsigned long timer_turn = millis();
  float previous_error = 0;

  // 1. คำนวณองศาเป้าหมายและจัดการการวนรอบ (Wrap-around)
  float target_degree = current_degree + relative_degree;
  while (target_degree > 180) target_degree -= 360;
  while (target_degree < -180) target_degree += 360;
  current_degree = target_degree;

  while (1) {
    float current_angle = angleRead(YAW);

    // 2. คำนวณ Error และจัดการการวนรอบ +/- 180 องศา
    float error = target_degree - current_angle;
    while (error > 180) error -= 360;
    while (error < -180) error += 360;

    // 3. เช็คเงื่อนไขการหยุด (อยู่ใน threshold ต่อเนื่อง 50ms)
    if (abs(error) <= stop_threshold) {
      motorStop();
      if (millis() - timer_turn >= 50) {
        break; // หยุดนิ่งแล้ว ออกจากฟังก์ชัน
      }
    } else {
      timer_turn = millis(); // รีเซ็ตเวลาหากหลุดกรอบ threshold

      // 4. คำนวณ PD Controller
      float derivative = error - previous_error;
      
      // ป้องกันบัคค่า derivative กระโดดเวลาหมุนข้ามรอยต่อ 180 / -180 องศา
      if (derivative > 180) derivative -= 360;
      if (derivative < -180) derivative += 360;

      int pd_value = (error * kp) + (derivative * kd);

      // 5. จำกัดขอบเขตความเร็วมอเตอร์ (Min/Max Speed Limits)
      // ป้องกันความเร็วตกต่ำกว่า min_speed ไม่งั้นมอเตอร์จะไม่มีแรงฮึดเข้าเป้าหมาย
      if (pd_value > 0) {
        if (pd_value > max_speed) pd_value = max_speed;
        if (pd_value < min_speed) pd_value = min_speed;
      } else if (pd_value < 0) {
        if (pd_value < -max_speed) pd_value = -max_speed;
        if (pd_value > -min_speed) pd_value = -min_speed;
      }

      // 6. สั่งงานมอเตอร์
      motorWrite(1, pd_value);
      motorWrite(2, -pd_value);
    }

    previous_error = error;
    
    // หน่วงเวลาเล็กน้อยให้เซนเซอร์ (IMU/Compass) อัปเดตค่าทัน และให้ค่า Derivative ทำงานได้ถูกต้อง
    delay(2); 
  }
}

void turnDegreeFront(int relative_degree) {
  int min_speed = 35;                // ความเร็วต่ำสุด
  int max_speed = 100;               // ความเร็วสูงสุด
  float kp = 0.8;                    // KP
  float kd = 0.1;                    // KD
  float small_angle_threshold = 60;  // หุ่นยนต์จะใช้ความเร็วต่ำสุดเมื่อเข้าใกล้องศาที่กำหนด
  float stop_threshold = 9.75;       // กำหนดความคลาดเคลื่อนที่ยอมรับได้
  unsigned long timer_turn = 0;
  float previous_error = 0;
  float target_degree = current_degree + relative_degree;
  if (target_degree > 180) target_degree -= 360;
  if (target_degree < -180) target_degree += 360;
  current_degree = target_degree;
  while (1) {
    float current_angle = angleRead(YAW);
    float error = target_degree - current_angle;
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    if (error > stop_threshold && error < small_angle_threshold) {
      // motorWrite(min_speed, min_speed, 0, 0);
      motorWrite(1, min_speed);
      motorWrite(2, 0);
      timer_turn = millis();
    } else if (error < -stop_threshold && error > -small_angle_threshold) {
      // motorWrite(0, 0, min_speed, min_speed);
      motorWrite(1, 0);
      motorWrite(2, min_speed);
      timer_turn = millis();
    } else if (error >= -stop_threshold && error <= stop_threshold) {
      motorStop();
      break;
    } else {
      if (error <= 0) {
        // motorWrite(20, 20, -pd_value, -pd_value);
        motorWrite(1, 20);
        motorWrite(2, -pd_value);
      }
      else if (error > 0) {
        // motorWrite(pd_value, pd_value, 20, 20);
        motorWrite(1, -pd_value);
        motorWrite(2, 20);
      }
      timer_turn = millis();
    }
    previous_error = error;
  }
}

void turnDegreeBack(int relative_degree) {
  int min_speed = 30;                // ความเร็วต่ำสุด
  int max_speed = 100;               // ความเร็วสูงสุด
  float kp = 1.25;                   // KP
  float kd = 0.1;                    // KD
  float small_angle_threshold = 60;  // หุ่นยนต์จะใช้ความเร็วต่ำสุดเมื่อเข้าใกล้องศาที่กำหนด
  float stop_threshold = 25.5;       // กำหนดความคลาดเคลื่อนที่ยอมรับได้
  unsigned long timer_turn = 0;
  float previous_error = 0;
  float target_degree = current_degree + relative_degree;
  if (target_degree > 180) target_degree -= 360;
  if (target_degree < -180) target_degree += 360;
  current_degree = target_degree;
  while (1) {
    float current_angle = angleRead(YAW);
    float error = target_degree - current_angle;
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    if (error > stop_threshold && error < small_angle_threshold) {
      // motorWrite(0, 0, -min_speed, -min_speed);
      motorWrite(1, 0);
      motorWrite(2, -min_speed);
      timer_turn = millis();
    } else if (error < -stop_threshold && error > -small_angle_threshold) {
      // motorWrite(-min_speed, -min_speed, 0, 0);
      motorWrite(1, -min_speed);
      motorWrite(2, 0);
      timer_turn = millis();
    } else if (error >= -stop_threshold && error <= stop_threshold) {
      motorStop();
      break;
    } else {
      if (error <= 0) {
        // motorWrite(pd_value, pd_value, -20, -20);
        motorWrite(1, pd_value);
        motorWrite(2, -20);
      }
      else if (error > 0) {
        // motorWrite(-20, -20, pd_value, pd_value);
        motorWrite(1, -20);
        motorWrite(2, pd_value);
      }
      timer_turn = millis();
    }
    previous_error = error;
  }
}

void LL(float time) {
  float target_degree = current_degree - 90;
  if (target_degree > 180) target_degree -= 360;
  if (target_degree < -180) target_degree += 360;
  current_degree = target_degree;
  // motorWrite(-100, -100, 100, 100);
  motorWrite(1, -100);
  motorWrite(2, 100);
  delay(time * power_factor);
  motorStop();
  delay(50);
}

void RR(float time) {
  float target_degree = current_degree + 90;
  if (target_degree > 180) target_degree -= 360;
  if (target_degree < -180) target_degree += 360;
  current_degree = target_degree;
  // motorWrite(100, 100, -100, -100);
  motorWrite(1, 100);
  motorWrite(2, -100);
  delay(time * power_factor);
  motorStop();
  delay(50);
}

void TL(float time) {
  float target_degree = current_degree - 90;
  if (target_degree > 180) target_degree -= 360;
  if (target_degree < -180) target_degree += 360;
  current_degree = target_degree;
  // motorWrite(20, 20, 100, 100);
  motorWrite(1, 20);
  motorWrite(2, 100);
  delay(time * power_factor);
  motorStop();
}

void TR(float time) {
  float target_degree = current_degree + 90;
  if (target_degree > 180) target_degree -= 360;
  if (target_degree < -180) target_degree += 360;
  current_degree = target_degree;
  // motorWrite(100, 100, 20, 20);
  motorWrite(1, 100);
  motorWrite(2, 20);
  delay(time * power_factor);
  motorStop();
}

void TL_B(float time) {
  float target_degree = current_degree + 90;
  if (target_degree > 180) target_degree -= 360;
  if (target_degree < -180) target_degree += 360;
  current_degree = target_degree;
  // motorWrite(20, 20, -100, -100);
  motorWrite(1, 20);
  motorWrite(2, -100);
  delay(time * power_factor);
  motorStop();
}

void TR_B(float time) {
  float target_degree = current_degree - 90;
  if (target_degree > 180) target_degree -= 360;
  if (target_degree < -180) target_degree += 360;
  current_degree = target_degree;
  // motorWrite(-100, -100, 20, 20);
  motorWrite(1, -100);
  motorWrite(2, 20);
  delay(time * power_factor);
  motorStop();
}
