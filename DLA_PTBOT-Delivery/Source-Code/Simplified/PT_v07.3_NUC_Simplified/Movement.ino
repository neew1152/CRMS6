void FF(int speed) {
  int base_speed = speed;
  int max_speed = 80;
  float kp = 2.8;
  float kd = 15.0;
  float error = Current_Degree - angleRead(YAW);
  if (error > 180) error -= 360;
  else if (error < -180) error += 360;
  float derivative = error - Previous_Error_Forward;
  int pd_value = (error * kp) + (derivative * kd);
  if (pd_value > max_speed) pd_value = max_speed;
  else if (pd_value < -max_speed) pd_value = -max_speed;
  int speed_left = base_speed + pd_value;
  int speed_right = base_speed - pd_value;
  motorWrite(1, speed_left);
  motorWrite(2, speed_right);
  Previous_Error_Forward = error;
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
    float actual_timer = timer * Power_Factor;
    long remaining_time = (long)actual_timer - (long)elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = Current_Degree - angleRead(YAW);
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
    if (elapsed_time >= timer * Power_Factor) {
      motorStop();
      break;
    }
    previous_error = error;
  }
}

void FF(int speed, float timer, char spin) {
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
    float actual_timer = timer * Power_Factor;
    long remaining_time = (long)actual_timer - (long)elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = Current_Degree - angleRead(YAW);
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
    if (elapsed_time >= timer * Power_Factor) {
      motorStop();
      break;
    }
  }
  switch (spin) {
    case 'L':
      SpinDegree(-90);
      break;

    case 'R':
      SpinDegree(90);
      break;
  }
}

void BB(int speed) {
  int base_speed = speed;
  int max_speed = 80;
  float kp = 2.8;
  float kd = 17.0;
  float error = Current_Degree - angleRead(YAW);
  if (error > 180) error -= 360;
  else if (error < -180) error += 360;
  float derivative = error - Previous_Error_Forward;
  int pd_value = (error * kp) + (derivative * kd);
  if (pd_value > max_speed) pd_value = max_speed;
  else if (pd_value < -max_speed) pd_value = -max_speed;
  int speed_left = base_speed - pd_value;
  int speed_right = base_speed + pd_value;
  motorWrite(1, -speed_left);
  motorWrite(2, -speed_right);
  Previous_Error_Forward = error;
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
    float actual_timer = timer * Power_Factor;
    long remaining_time = (long)actual_timer - (long)elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = Current_Degree - angleRead(YAW);
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
    if (elapsed_time >= timer * Power_Factor) {
      motorStop();
      break;
    }
    previous_error = error;
  }
}

void BB(int speed, float timer, char spin) {
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
    float actual_timer = timer * Power_Factor;
    long remaining_time = (long)actual_timer - (long)elapsed_time;
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else current_speed = max_speed;
    float error = Current_Degree - angleRead(YAW);
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
    if (elapsed_time >= timer * Power_Factor) {
      motorStop();
      break;
    }
    previous_error = error;
  }
  switch (spin) {
    case 'L':
      SpinDegree(-90);
      break;

    case 'R':
      SpinDegree(90);
      break;
  }
}

void SetFront(int speed) {
  Previous_Error_Forward = 0;
  while (1) {
    ReadIR();
    if (IR_Data[0] <= 50 && IR_Data[1] <= 50) {
      motorStop();
      break;
    } else {
      if (IR_Data[0] <= 50) motorWrite(1, -12);
      else motorWrite(1, speed);
      if (IR_Data[1] <= 50) motorWrite(2, -12);
      else motorWrite(2, speed);
    }
  }
  vTaskDelay(250 / portTICK_PERIOD_MS);
  Current_Degree = angleRead(YAW);
}

void SetFront(int speed, float timer) {
  SetFront(speed);
  BB(speed, timer);
}

void SetFront(int speed, float timer, char spin) {
  SetFront(speed, timer);
  switch (spin) {
    case 'L':
      SpinDegree(-90);
      break;

    case 'R':
      SpinDegree(90);
      break;
  }
}

void SetBack(int speed) {
  Previous_Error_Forward = 0;
  while (1) {
    ReadIR();
    if (IR_Data[3] <= 50 && IR_Data[2] <= 50) {
      motorStop();
      break;
    } else {
      if (IR_Data[2] <= 50) motorWrite(2, 12);
      else motorWrite(2, -speed);
      if (IR_Data[3] <= 50) motorWrite(1, 12);
      else motorWrite(1, -speed);
    }
  }
  vTaskDelay(250 / portTICK_PERIOD_MS);
  Current_Degree = angleRead(YAW);
}

void SetBack(int speed, float timer) {
  SetBack(speed);
  FF(speed, timer);
}

void SetBack(int speed, float timer, char spin) {
  SetBack(speed, timer);
  switch (spin) {
    case 'L':
      SpinDegree(-90);
      break;

    case 'R':
      SpinDegree(90);
      break;
  }
}

void SpinDegree(int relative_degree) {
  vTaskDelay(100 / portTICK_PERIOD_MS);
  unsigned long timer_turn = millis();
  int min_speed = 20;
  int max_speed = 75;
  float kp = 1.5;
  float kd = 1.0;
  float small_angle_threshold = 30;
  float stop_threshold = 1.0;
  float previous_error = 0;
  float target_degree = Current_Degree + relative_degree;
  if (target_degree > 180) target_degree -= 360;
  if (target_degree < -180) target_degree += 360;
  Current_Degree = target_degree;
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
      motorWrite(1, min_speed);
      motorWrite(2, -min_speed);
      timer_turn = millis();
    } else if (error < -stop_threshold && error > -small_angle_threshold) {
      motorWrite(1, -min_speed);
      motorWrite(2, min_speed);
      timer_turn = millis();
    } else if (error >= -stop_threshold && error <= stop_threshold) {
      motorStop();
      if (millis() - timer_turn >= 100) break;
    } else {
      motorWrite(1, pd_value);
      motorWrite(2, -pd_value);
      timer_turn = millis();
    }
    previous_error = error;
  }
  vTaskDelay(100 / portTICK_PERIOD_MS);
}

void FFUltrasonic(float distance) {
  Ultrasonic_Enable = 1;
  unsigned long int timer = millis();
  while (ReadUltrasonic() > distance || millis() - timer <= 500) {
    FF(15);
  }
  FF(10, 200);
  motorStop();
  Ultrasonic_Enable = 0;
}

void FFLaser(float distance) {
  unsigned long int timer = millis();
  while (ReadLaser() > distance || millis() - timer <= 500) {
    FF(15);
  }
  FF(10, 250);
  motorStop();
}