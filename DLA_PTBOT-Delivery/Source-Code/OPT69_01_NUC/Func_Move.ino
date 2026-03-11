void forward(int speed) {
  motorWrite(1, speed);
  motorWrite(2, speed);
}
void FF(int speed) {
  int base_speed = speed;  // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = 80;      // ความเร็วสูงสุด
  float kp = 3.5;          // KP
  float kd = 1.0;          // KD
  float error = current_degree - angleRead(YAW);
  if (error > 180) error -= 360;
  else if (error < -180) error += 360;
  float derivative = error - previous_error_forward;
  int pd_value = (error * kp) + (derivative * kd);
  if (pd_value > max_speed) pd_value = max_speed;
  else if (pd_value < -max_speed) pd_value = -max_speed;
  int speed_left = base_speed + pd_value;
  int speed_right = base_speed - pd_value;
  // motorWrite(speed_left, speed_left, speed_right, speed_right);
  motorWrite(1, speed_left);
  motorWrite(2, speed_right);
  previous_error_forward = error;
}

void FF(int speed, float timer) {
  int min_speed = 10;     // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = speed;  // ความเร็วสูงสุด
  float kp = 3;           // KP
  float kd = 3;           // KD
  int ramp_up = 250;      // หุ่นยนต์จะเริ่มวิ่งจากความเร็วต่ำสุดไปที่ความเร็วสูงสุดภายในเวลาที่กำหนด
  int ramp_down = 200;    // หุ่นยนต์จะวิ่งจากความเร็วสูงสุดไปที่ความเร็วต่ำสุดภายในเวลาที่กำหนดก่อนที่จะหยุด
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  float previous_error = 0;
  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = timer - elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    int speed_left = current_speed + pd_value;
    int speed_right = current_speed - pd_value;
    // motorWrite(speed_left, speed_left, speed_right, speed_right);
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    if (elapsed_time >= timer * power_factor) {
      motorStop();
      break;
    }
    previous_error = error;
  }
}

void FF(int speed, float timer, char select) {
  int min_speed = 15;     // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = speed;  // ความเร็วสูงสุด
  float kp = 3;           // KP
  float kd = 3;           // KD
  int ramp_up = 250;      // หุ่นยนต์จะเริ่มวิ่งจากความเร็วต่ำสุดไปที่ความเร็วสูงสุดภายในเวลาที่กำหนด
  int ramp_down = 200;    // หุ่นยนต์จะวิ่งจากความเร็วสูงสุดไปที่ความเร็วต่ำสุดภายในเวลาที่กำหนดก่อนที่จะหยุด
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  float previous_error = 0;
  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = timer - elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    int speed_left = current_speed + pd_value;
    int speed_right = current_speed - pd_value;
    // motorWrite(speed_left, speed_left, speed_right, speed_right);
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    previous_error = error;
    if (elapsed_time >= timer * power_factor) {
      motorStop();
      break;
    }
  }

  delay(delayALL);
  if (select == 'L') {
    spinDegree_Enhanced(-90);
  } else if (select == 'R') {
    spinDegree_Enhanced(90);
  } else if (select == 'l') {
    turnDegreeFront(-90);
  } else if (select == 'r') {
    turnDegreeFront(90);
  }
  delay(delayALL);
}

void FF(int speed, float timer, char select, float turnTimer) {
  int min_speed = 15;     // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = speed;  // ความเร็วสูงสุด
  float kp = 3.5;         // KP
  float kd = 1.0;         // KD
  int ramp_up = 250;      // หุ่นยนต์จะเริ่มวิ่งจากความเร็วต่ำสุดไปที่ความเร็วสูงสุดภายในเวลาที่กำหนด
  int ramp_down = 200;    // หุ่นยนต์จะวิ่งจากความเร็วสูงสุดไปที่ความเร็วต่ำสุดภายในเวลาที่กำหนดก่อนที่จะหยุด
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  float previous_error = 0;
  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = timer - elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    int speed_left = current_speed + pd_value;
    int speed_right = current_speed - pd_value;
    // motorWrite(speed_left, speed_left, speed_right, speed_right);
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    if (elapsed_time >= timer * power_factor) {
      motorStop();
      break;
    }
    previous_error = error;
  }

  if (select == 'L') {
    LL(turnTimer);
  } else if (select == 'R') {
    RR(turnTimer);
  } else if (select == 'l') {
    TL(turnTimer);
  } else if (select == 'r') {
    TR(turnTimer);
  }
  delay(delayALL);
}

void BB(int speed) {
  int base_speed = speed;  // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = 80;      // ความเร็วสูงสุด
  float kp = 3.5;          // KP
  float kd = 1.0;          // KD
  float error = current_degree - angleRead(YAW);
  if (error > 180) error -= 360;
  else if (error < -180) error += 360;
  float derivative = error - previous_error_forward;
  int pd_value = (error * kp) + (derivative * kd);
  if (pd_value > max_speed) pd_value = max_speed;
  else if (pd_value < -max_speed) pd_value = -max_speed;
  int speed_left = base_speed - pd_value;
  int speed_right = base_speed + pd_value;
  // motorWrite(-speed_left, -speed_left, -speed_right, -speed_right);
  motorWrite(1, -speed_left);
  motorWrite(2, -speed_right);
  previous_error_forward = error;
}

void BB(int speed, float timer) {
  int min_speed = 10;     // ปรับให้ตรงกับ FF (เดิม 15)
  int max_speed = speed;  // ความเร็วสูงสุด
  float kp = 3;           // ปรับให้ตรงกับ FF (เดิม 3.5)
  float kd = 3;           // ปรับให้ตรงกับ FF (เดิม 1.0)
  int ramp_up = 250;      // ปรับให้ตรงกับ FF (เดิม 200)
  int ramp_down = 200;    // ปรับให้ตรงกับ FF (เดิม 250)
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  float previous_error = 0;

  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = timer - elapsed_time;

    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;

    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;

    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);

    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;

    // สำหรับถอยหลัง ลอจิกการหักเลี้ยวต้องสลับด้านกับ FF เพื่อให้หุ่นเลี้ยงตัวตรงได้
    int speed_left = current_speed - pd_value;
    int speed_right = current_speed + pd_value;

    // สั่งมอเตอร์ให้หมุนถอยหลัง (ใส่เครื่องหมายติดลบ)
    motorWrite(1, -speed_left);
    motorWrite(2, -speed_right);

    if (elapsed_time >= timer * power_factor) {
      motorStop();
      break;
    }
    previous_error = error;
  }
}

void BB(int speed, float timer, char select) {
  int min_speed = 15;     // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = speed;  // ความเร็วสูงสุด
  float kp = 3;           // KP
  float kd = 3;           // KD
  int ramp_up = 200;      // หุ่นยนต์จะเริ่มวิ่งจากความเร็วต่ำสุดไปที่ความเร็วสูงสุดภายในเวลาที่กำหนด
  int ramp_down = 250;    // หุ่นยนต์จะวิ่งจากความเร็วสูงสุดไปที่ความเร็วต่ำสุดภายในเวลาที่กำหนดก่อนที่จะหยุด
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  float previous_error = 0;
  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = timer - elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    int speed_left = current_speed - pd_value;
    int speed_right = current_speed + pd_value;
    // motorWrite(-speed_left, -speed_left, -speed_right, -speed_right);
    motorWrite(1, -speed_left);
    motorWrite(2, -speed_right);
    if (elapsed_time >= timer * power_factor) {
      motorStop();
      break;
    }
    previous_error = error;
  }
  delay(delayALL);
  if (select == 'L') {
    spinDegree_Enhanced(-90);
  }
  if (select == 'R') {
    spinDegree_Enhanced(90);
  }
  if (select == 'l') {
    turnDegreeBack(-90);
  }
  if (select == 'r') {
    turnDegreeBack(90);
  }
  delay(delayALL);
}

void BB(int speed, float timer, char select, float turnTimer) {
  int min_speed = 15;     // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = speed;  // ความเร็วสูงสุด
  float kp = 3.5;         // KP
  float kd = 1.0;         // KD
  int ramp_up = 200;      // หุ่นยนต์จะเริ่มวิ่งจากความเร็วต่ำสุดไปที่ความเร็วสูงสุดภายในเวลาที่กำหนด
  int ramp_down = 250;    // หุ่นยนต์จะวิ่งจากความเร็วสูงสุดไปที่ความเร็วต่ำสุดภายในเวลาที่กำหนดก่อนที่จะหยุด
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  float previous_error = 0;
  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = timer - elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    int speed_left = current_speed - pd_value;
    int speed_right = current_speed + pd_value;
    // motorWrite(-speed_left, -speed_left, -speed_right, -speed_right);
    motorWrite(1, -speed_left);
    motorWrite(2, -speed_right);
    if (elapsed_time >= timer * power_factor) {
      motorStop();
      break;
    }
    previous_error = error;
  }

  if (select == 'L') {
    LL(turnTimer);
  }
  if (select == 'R') {
    RR(turnTimer);
  }
  if (select == 'l') {
    TL_B(turnTimer);
  }
  if (select == 'r') {
    TR_B(turnTimer);
  }
  delay(delayALL);
}

void SetFront(int speed) {
  previous_error_forward = 0;
  while (1) {
    readLine();
    if (line_value[0] <= 2 && line_value[1] <= 2) {
      motorStop();
      break;
    } else {
      if (line_value[0] <= 2) motorWrite(1, -15);
      else motorWrite(1, speed);
      if (line_value[1] <= 2) motorWrite(2, -15);
      else motorWrite(2, speed);
    }
  }
  delay(100);
  current_degree = angleRead(YAW) + 2;
}

void SetFront(int speed, float timer) {
  SetFront(speed);
  motorStop();
  delay(50);
  motorTimeDegree(-speed, timer);
  delay(delayALL);
}

void SetFront(int speed, float timer, char select) {
  SetFront(speed, timer);
  if (select == 'L') {
    spinDegree_Enhanced(-90);
  }
  if (select == 'R') {
    spinDegree_Enhanced(90);
  }
  delay(delayALL);
}

void SetFront(int speed, float timer, char select, float turnTimer) {
  previous_error_forward = 0;
  while (0) {
    readLine();
    if (line_value[0] <= 2 || line_value[1] <= 2) {
      break;
    } else if (line_value[0] >= 3 && line_value[1] >= 3) {
      FF(speed);
    } else if (line_value[0] <= 2 && line_value[1] >= 3) {
      // motorWrite(50, 50, 0, 0);
      motorWrite(1, 50);
      motorWrite(2, 0);
      delay(100);
    } else if (line_value[0] >= 3 && line_value[1] <= 2) {
      // motorWrite(0, 0, 50, 50);
      motorWrite(1, 0);
      motorWrite(2, 50);
      delay(100);
    }
  }
  while (1) {
    readLine();
    FF(speed);
    if (line_value[0] <= 2 && line_value[1] <= 2) {
      motorStop();
      break;
    } else if (line_value[0] <= 2 && line_value[1] >= 3) {
      // motorWrite(-speed, -speed, 0, 0);
      motorWrite(1, -speed);
      motorWrite(2, 0);
    } else if (line_value[0] >= 3 && line_value[1] <= 2) {
      // motorWrite(0, 0, -speed, -speed);
      motorWrite(1, 0);
      motorWrite(2, -speed);
    }
  }
  delay(10);
  current_degree = angleRead(YAW);
  motorTimeDegree(-speed, timer);
  delay(delayALL);

  if (select == 'L') {
    LL(turnTimer);
  }
  if (select == 'R') {
    RR(turnTimer);
  }
  delay(delayALL);
}

void SetBack(int speed) {
  previous_error_forward = 0;
  while (1) {
    readLine();
    // ถ้าเซ็นเซอร์ซ้ายหลัง(5) และ ขวาหลัง(2) เจอเส้นทั้งคู่ ให้หยุด
    if (line_value[5] <= 2 && line_value[2] <= 2) {
      motorStop();
      break;
    } else {
      // มอเตอร์ซ้าย (1) คู่กับ เซ็นเซอร์ซ้ายหลัง (5)
      if (line_value[5] <= 2) motorWrite(1, 15);  // ถ้าซ้ายแตะเส้นแล้ว ให้เดินหน้าดันสู้เบาๆ
      else motorWrite(1, -speed);                 // ถ้ายังไม่แตะ ให้ถอยหลังต่อเพื่อหาเส้น

      // มอเตอร์ขวา (2) คู่กับ เซ็นเซอร์ขวาหลัง (2)
      if (line_value[2] <= 2) motorWrite(2, 15);  // ถ้าขวาแตะเส้นแล้ว ให้เดินหน้าดันสู้เบาๆ
      else motorWrite(2, -speed);                 // ถ้ายังไม่แตะ ให้ถอยหลังต่อเพื่อหาเส้น
    }
  }
  delay(100);
  current_degree = angleRead(YAW);
}

void SetBack(int speed, float timer) {
  SetBack(speed);
  motorStop();
  delay(50);
  motorTimeDegree(speed, timer);  // เดินหน้าออกจากเส้นเล็กน้อย
  delay(delayALL);
}

void SetBack(int speed, float timer, char select) {
  SetBack(speed, timer);
  if (select == 'L') {
    spinDegree_Enhanced(-90);
  }
  if (select == 'R') {
    spinDegree_Enhanced(90);
  }
  delay(delayALL);
}

void SetBack(int speed, float timer, char select, float turnTimer) {
  previous_error_forward = 0;

  // ลูปค้นหาเส้นและจัดทรง
  while (1) {
    readLine();
    if (line_value[5] <= 2 && line_value[2] <= 2) {
      // แตะเส้นครบสองข้าง ถือว่าตั้งตรงแล้ว
      motorStop();
      break;
    } else if (line_value[5] <= 2) {
      // ซ้ายแตะเส้นแล้ว แต่ขวายัง ให้ซ้ายดันสู้ ขวาถอยหลังต่อ
      motorWrite(1, 15);
      motorWrite(2, -speed);
    } else if (line_value[2] <= 2) {
      // ขวาแตะเส้นแล้ว แต่ซ้ายยัง ให้ขวาดันสู้ ซ้ายถอยหลังต่อ
      motorWrite(1, -speed);
      motorWrite(2, 15);
    } else {
      // ถ้ายังไม่มีเซ็นเซอร์ตัวไหนแตะเส้นเลย ให้ถอยตรงๆ ด้วย PID ไปก่อน
      BB(speed);
    }
  }

  delay(10);
  current_degree = angleRead(YAW);  // รีเซ็ตองศาเริ่มต้นใหม่ให้ตรงกับเส้น
  motorTimeDegree(speed, timer);    // ขยับเดินหน้าออกจากเส้น
  delay(delayALL);

  // สั่งเลี้ยว
  if (select == 'L') {
    LL(turnTimer);
  }
  if (select == 'R') {
    RR(turnTimer);
  }
  delay(delayALL);
}

void motorTimeDegree(int speed, float timer) {
  int base_speed = speed;  // ความเร็วเริ่มต้น และความเร็วก่อนหยุด
  int max_speed = 80;      // ความเร็วสูงสุด
  float kp = 3.5;          // KP
  float kd = 0.1;          // KD
  unsigned long timer_forward = millis();
  float previous_error = 0;
  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = timer - elapsed_time;
    float error = current_degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error_forward;
    int pd_value = (error * kp) + (derivative * kd);
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    int speed_left = base_speed + pd_value;
    int speed_right = base_speed - pd_value;
    // motorWrite(speed_left, speed_left, speed_right, speed_right);
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    previous_error_forward = error;
    if (elapsed_time >= timer * power_factor) {
      motorStop();
      break;
    }
  }
}

void motorTimeDegree_Enhanced(int acc_speed, int speed, float timer) {
  motorTimeDegree(acc_speed, 150);
  motorTimeDegree(speed, timer);
  motorTimeDegree(acc_speed, 150);
}

void motorTimeDegree_Enhanced(int acc_speed, int speed, float timer, char select) {
  motorStop();
  delay(50);
  motorTimeDegree(acc_speed, 150);
  motorTimeDegree(speed, timer);
  motorTimeDegree(acc_speed, 150);

  motorStop();
  delay(50);

  delay(delayALL);
  if (select == 'L') {
    spinDegree_Enhanced(-89);
  } else if (select == 'R') {
    spinDegree_Enhanced(90);
  } else if (select == 'l') {
    turnDegreeFront(-90);
  } else if (select == 'r') {
    turnDegreeFront(90);
  }
  delay(delayALL);

  motorStop();
  delay(50);
}

////////////////////////////////////

void SetFront_Wall(int speed) {
  lift(2);
  servoWrite(chanal_Swing_Right, 180);
  servoWrite(chanal_Swing_Left, 180);
  servoCloseRight();
  servoCloseLeft();
  SetFront(speed);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Swing_Left, Swing_Left);
}
void SetFront_Wall(int speed, float timer) {
  lift(2);
  servoWrite(chanal_Swing_Right, 180);
  servoWrite(chanal_Swing_Left, 180);
  servoCloseRight();
  servoCloseLeft();
  SetFront(speed, timer);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Swing_Left, Swing_Left);
}
void SetFront_Wall(int speed, float timer, char select) {
  lift(2);
  servoWrite(chanal_Swing_Right, 179);
  servoWrite(chanal_Swing_Left, 179);
  servoCloseRight();
  servoCloseLeft();
  SetFront(speed, timer, select);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Swing_Left, Swing_Left);
}