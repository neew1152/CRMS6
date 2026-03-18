void FF(int speed) {
  int base_speed = speed;
  int max_speed = 80;
  float kp = 2.8;
  float kd = 15.0;
  float error = current_degree - angleRead(YAW);
  if (error > 180) error -= 360;
  else if (error < -180) error += 360;
  float derivative = error - previous_error_forward;
  int pd_value = (error * kp) + (derivative * kd);
  if (pd_value > max_speed) pd_value = max_speed;
  else if (pd_value < -max_speed) pd_value = -max_speed;
  int speed_left = base_speed + pd_value;
  int speed_right = base_speed - pd_value;
  motorWrite(1, speed_left);
  motorWrite(2, speed_right);
  previous_error_forward = error;
}

void FF(int speed, float timer) {
  int min_speed = 10;
  int max_speed = speed;
  float kp = 2.8;
  float kd = 15.0;
  int ramp_up = 250;
  int ramp_down = 200;
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
  int min_speed = 15;
  int max_speed = speed;
  float kp = 2.8;
  float kd = 15.0;
  int ramp_up = 250;
  int ramp_down = 200;
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
  int min_speed = 15;
  int max_speed = speed;
  float kp = 2.8;
  float kd = 15.0;
  int ramp_up = 250;
  int ramp_down = 200;
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
  int base_speed = speed;
  int max_speed = 80;
  float kp = 2.8;
  float kd = 17.0;
  float error = current_degree - angleRead(YAW);
  if (error > 180) error -= 360;
  else if (error < -180) error += 360;
  float derivative = error - previous_error_forward;
  int pd_value = (error * kp) + (derivative * kd);
  if (pd_value > max_speed) pd_value = max_speed;
  else if (pd_value < -max_speed) pd_value = -max_speed;
  int speed_left = base_speed - pd_value;
  int speed_right = base_speed + pd_value;
  motorWrite(1, -speed_left);
  motorWrite(2, -speed_right);
  previous_error_forward = error;
}

void BB(int speed, float timer) {
  int min_speed = 15;
  int max_speed = speed;
  float kp = 2.8;
  float kd = 17.0;
  int ramp_up = 200;
  int ramp_down = 250;
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
  int min_speed = 15;
  int max_speed = speed;
  float kp = 2.8;
  float kd = 17.0;
  int ramp_up = 200;
  int ramp_down = 250;
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
  int min_speed = 15;
  int max_speed = speed;
  float kp = 2.8;
  float kd = 17.0;
  int ramp_up = 200;
  int ramp_down = 250;
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
    if (line_value[0] <= 50 && line_value[1] <= 50) {
      motorStop();
      break;
    } else {
      if (line_value[0] <= 50) motorWrite(1, -12);
      else motorWrite(1, speed);
      if (line_value[1] <= 50) motorWrite(2, -12);
      else motorWrite(2, speed);
    }
  }
  delay(200);
  current_degree = angleRead(YAW);
}

void SetFront(int speed, float timer) {
  SetFront(speed);
  delay(10);
  motorTimeDegree(-speed, timer);
  delay(delayALL);
}

void SetFront(int speed, float timer, char select) {
  SetFront(speed, timer);
  if (select == 'L') {
    spinDegree(-90);
  }
  if (select == 'R') {
    spinDegree(90);
  }
  delay(delayALL);
}

void SetFront(int speed, float timer, char select, float turnTimer) {
  SetFront(speed, timer);
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
    if (line_value[3] <= 50 && line_value[2] <= 50) {
      motorStop();
      break;
    } else {
      if (line_value[2] <= 50) motorWrite(2, 12);
      else motorWrite(2, -speed);
      if (line_value[3] <= 50) motorWrite(1, 12);
      else motorWrite(1, -speed);
    }
  }
  delay(200);
  current_degree = angleRead(YAW);
}

void SetBack(int speed, float timer) {
  SetBack(speed);
  delay(10);
  motorTimeDegree(speed, timer);
  delay(delayALL);
}

void SetBack(int speed, float timer, char select) {
  SetBack(speed, timer);
  if (select == 'L') {
    spinDegree(-90);
  }
  if (select == 'R') {
    spinDegree(90);
  }
  delay(delayALL);
}

void SetBack(int speed, float timer, char select, float turnTimer) {
  SetBack(speed, timer);
  if (select == 'L') {
    LL(turnTimer);
  }
  if (select == 'R') {
    RR(turnTimer);
  }
  delay(delayALL);
}

void motorTimeDegree(int speed, float timer) {
  int base_speed = speed;
  int max_speed = 80;
  float kp = 3.5;
  float kd = 0.1;
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
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    previous_error_forward = error;
    if (elapsed_time >= timer * power_factor) {
      motorStop();
      break;
    }
  }
}