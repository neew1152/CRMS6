void forward(int speed){
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
  float kp = 6;         // KP
  float kd = 1.2;         // KD
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
  float kp = 3.5;         // KP
  float kd = 1.5;         // KD
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
    spinDegree(-90);
  } else if (select == 'R') {
    spinDegree(90);
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
}

void BB(int speed, float timer, char select) {
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
  delay(delayALL);
  if (select == 'L') {
    spinDegree(-90);
  }
  if (select == 'R') {
    spinDegree(90);
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
    }
    else {
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
  motorStop(); delay(50);
  motorTimeDegree(-speed, timer);
  delay(delayALL);
}

void SetFront(int speed, float timer, char select) {
  SetFront(speed, timer);
  if (select == 'L') {
    spinDegree(-89);
  }
  if (select == 'R') {
    spinDegree(90);
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



void SetFront_Wall(int speed, float timer)
{
  lift(2);
  servoWrite(chanal_Swing_Right, 179);
  servoWrite(chanal_Swing_Left, 179);
  servoCloseRight();
  servoCloseLeft();
  SetFront(speed, timer);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Swing_Left, Swing_Left);
}
void SetFront_Wall(int speed, float timer, char select)
{
  lift(2);
  servoWrite(chanal_Swing_Right, 179);
  servoWrite(chanal_Swing_Left, 179);
  servoCloseRight();
  servoCloseLeft();
  SetFront(speed, timer, select);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Swing_Left, Swing_Left);
}

void SetBack(int speed) {
  previous_error_forward = 0;
  while (1) {
    readLine();
    if (line_value[5] <= 2 && line_value[2] <= 2) {
      motorStop();
      break;
    }
    else {
      if (line_value[2] <= 2) motorWrite(2, 15);
      else motorWrite(2, -speed);
      if (line_value[5] <= 2) motorWrite(1, 15);
      else motorWrite(1, -speed);
    }
  }
  delay(100);
  current_degree = angleRead(YAW);
}

void SetBack(int speed, float timer) {
  SetBack(speed);
  motorStop(); delay(50);
  motorTimeDegree(speed, timer);
  delay(delayALL);
}

void SetBack(int speed, float timer, char select) {
  SetBack(speed, timer);
  if (select == 'L') {
    spinDegree(-89);
  }
  if (select == 'R') {
    spinDegree(90);
  }
  delay(delayALL);
}

void SetBack(int speed, float timer, char select, float turnTimer) {
  previous_error_forward = 0;
  while (1) {
    readLine();
    if (line_value[4] <= 2 || line_value[3] <= 2) {
      break;
    } else if (line_value[5] >= 3 && line_value[2] >= 3) {
      BB(speed);
    } else if (line_value[5] <= 2 && line_value[2] >= 3) {
      // motorWrite(-50, -50, 0, 0);
      motorWrite(1, -50);
      motorWrite(2, 0);
      delay(100);
    } else if (line_value[5] >= 3 && line_value[2] <= 2) {
      // motorWrite(0, 0, -50, -50);
      motorWrite(1, 0);
      motorWrite(2, -50);
      delay(100);
    }
  }
  while (1) {
    readLine();
    BB(speed);
    if (line_value[5] <= 2 && line_value[2] <= 2) {
      motorStop();
      break;
    } else if (line_value[5] <= 2 && line_value[2] >= 3) {
      // motorWrite(speed, speed, 0, 0);
      motorWrite(1, speed);
      motorWrite(2, 0);
    } else if (line_value[5] >= 3 && line_value[2] <= 2) {
      // motorWrite(0, 0, speed, speed);
      motorWrite(1, 0);
      motorWrite(2, speed);
    }
  }
  delay(10);
  current_degree = angleRead(YAW);
  motorTimeDegree(speed, timer);
  delay(delayALL);

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

void motorTimeDegree_Enhanced(int acc_speed, int speed, float timer)
{
  motorTimeDegree(acc_speed, 150);
  motorTimeDegree(speed, timer);
  motorTimeDegree(acc_speed, 150);
}

void motorTimeDegree_Enhanced(int acc_speed, int speed, float timer, char select)
{
  motorStop(); delay(50);
  motorTimeDegree(acc_speed, 150);
  motorTimeDegree(speed, timer);
  motorTimeDegree(acc_speed, 150);

  motorStop(); delay(50);

  delay(delayALL);
  if (select == 'L') {
    spinDegree(-89);
  } else if (select == 'R') {
    spinDegree(90);
  } else if (select == 'l') {
    turnDegreeFront(-90);
  } else if (select == 'r') {
    turnDegreeFront(90);
  }
  delay(delayALL);

  motorStop(); delay(50);
}