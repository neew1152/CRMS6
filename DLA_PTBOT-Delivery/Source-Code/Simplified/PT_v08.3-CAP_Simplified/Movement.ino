void MotorTimeDegree(int speed, float timer) {
  int base_speed = speed;
  int max_speed = 80;
  float kp = 1.0;
  float kd = 1.0;
  unsigned long target_duration = (unsigned long)(timer * Power_Factor);
  unsigned long timer_forward = millis();
  float initial_error = Current_Degree - angleRead(YAW);
  if (initial_error > 180) initial_error -= 360;
  else if (initial_error < -180) initial_error += 360;
  Previous_Error_Forward = initial_error;
  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    if (elapsed_time >= target_duration) {
      motorStop();
      break;
    }
    float error = Current_Degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - Previous_Error_Forward;
    int pd_value = (int)((error * kp) + (derivative * kd));
    if (pd_value > max_speed) pd_value = max_speed;
    else if (pd_value < -max_speed) pd_value = -max_speed;
    int speed_left = base_speed + pd_value;
    int speed_right = base_speed - pd_value;
    if (speed_left > 100) {
      speed_right -= (speed_left - 100);
      speed_left = 100;
    } else if (speed_right > 100) {
      speed_left -= (speed_right - 100);
      speed_right = 100;
    }
    if (speed_left < -100) {
      speed_right += (-100 - speed_left);
      speed_left = -100;
    } else if (speed_right < -100) {
      speed_left += (-100 - speed_right);
      speed_right = -100;
    }
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    Previous_Error_Forward = error;
    vTaskDelay(Delay_HW / portTICK_PERIOD_MS);
  }
}

void FF(int speed) {
  int base_speed = speed;
  int max_speed = 80;
  float kp = 1.0;
  float kd = 1.0;
  unsigned long current_time = millis();
  float dt = (float)(current_time - Previous_Time);
  if (dt == 0) dt = 1;
  float error = Current_Degree - angleRead(YAW);
  if (error > 180) error -= 360;
  else if (error < -180) error += 360;
  float derivative = (error - Previous_Error_Forward) / dt;
  int pd_value = round((error * kp) + (derivative * kd));
  if (pd_value > max_speed) pd_value = max_speed;
  else if (pd_value < -max_speed) pd_value = -max_speed;
  int speed_left = base_speed + pd_value;
  int speed_right = base_speed - pd_value;
  int max_calculated_speed = max(abs(speed_left), abs(speed_right));
  if (max_calculated_speed > 100) {
    speed_left = map(speed_left, -max_calculated_speed, max_calculated_speed, -100, 100);
    speed_right = map(speed_right, -max_calculated_speed, max_calculated_speed, -100, 100);
  }
  motorWrite(1, speed_left);
  motorWrite(2, speed_right);
  Previous_Error_Forward = error;
  Previous_Time = current_time;
}

void FF(int speed, float timer) {
  int min_speed = 15;
  int max_speed = speed;
  float kp = 1.0;
  float kd = 1.0;
  int ramp_up = 250;
  int ramp_down = 200;
  int current_speed = min_speed;
  float actual_timer = timer * Power_Factor;
  if (actual_timer < (ramp_up + ramp_down)) {
    ramp_up = actual_timer / 2.0;
    ramp_down = actual_timer / 2.0;
  }
  unsigned long timer_forward = millis();
  unsigned long previous_time_loop = timer_forward;
  float previous_error = Current_Degree - angleRead(YAW);
  while (1) {
    unsigned long current_time = millis();
    unsigned long elapsed_time = current_time - timer_forward;
    long remaining_time = (long)actual_timer - (long)elapsed_time;
    float dt = (float)(current_time - previous_time_loop);
    if (dt == 0) dt = 1;
    if (elapsed_time >= actual_timer) {
      motorStop();
      break;
    }
    if (elapsed_time <= ramp_up && ramp_up > 0) {
      current_speed = min_speed + ((float)elapsed_time / ramp_up) * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down && ramp_down > 0) {
      current_speed = min_speed + ((float)remaining_time / ramp_down) * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else {
      current_speed = max_speed;
    }
    float error = Current_Degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = (error - previous_error) / dt;
    int pd_value = round((error * kp) + (derivative * kd));
    int pd_max_allowance = 80;
    if (pd_value > pd_max_allowance) pd_value = pd_max_allowance;
    else if (pd_value < -pd_max_allowance) pd_value = -pd_max_allowance;
    int speed_left = current_speed + pd_value;
    int speed_right = current_speed - pd_value;
    int max_calculated_speed = max(abs(speed_left), abs(speed_right));
    if (max_calculated_speed > 100) {
      speed_left = map(speed_left, -max_calculated_speed, max_calculated_speed, -100, 100);
      speed_right = map(speed_right, -max_calculated_speed, max_calculated_speed, -100, 100);
    }
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    previous_error = error;
    previous_time_loop = current_time;
    vTaskDelay(Delay_HW / portTICK_PERIOD_MS);
  }
}

void FF(int speed, float timer, char spin) {
  FF(speed, timer);
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
  int base_speed = -abs(speed);
  int max_speed = 80;
  float kp = 1.0;
  float kd = 1.0;
  unsigned long current_time = millis();
  float dt = (float)(current_time - Previous_Time);
  if (dt == 0) dt = 1;
  float error = Current_Degree - angleRead(YAW);
  if (error > 180) error -= 360;
  else if (error < -180) error += 360;
  float derivative = (error - Previous_Error_Backward) / dt;
  int pd_value = round((error * kp) + (derivative * kd));
  if (pd_value > max_speed) pd_value = max_speed;
  else if (pd_value < -max_speed) pd_value = -max_speed;
  int speed_left = base_speed + pd_value;
  int speed_right = base_speed - pd_value;
  int max_calculated_speed = max(abs(speed_left), abs(speed_right));
  if (max_calculated_speed > 100) {
    speed_left = map(speed_left, -max_calculated_speed, max_calculated_speed, -100, 100);
    speed_right = map(speed_right, -max_calculated_speed, max_calculated_speed, -100, 100);
  }
  motorWrite(1, speed_left);
  motorWrite(2, speed_right);
  Previous_Error_Backward = error;
  Previous_Time = current_time;
}

void BB(int speed, float timer) {
  int min_speed = 15;
  int max_speed = abs(speed);
  float kp = 1.0;
  float kd = 1.0;
  int ramp_up = 200;
  int ramp_down = 250;
  float current_speed = min_speed;
  float actual_timer = timer * Power_Factor;
  if (actual_timer < (ramp_up + ramp_down)) {
    ramp_up = actual_timer / 2.0;
    ramp_down = actual_timer / 2.0;
  }
  unsigned long start_time = millis();
  unsigned long previous_time_loop = start_time;
  float previous_error = Current_Degree - angleRead(YAW);
  while (1) {
    unsigned long current_time = millis();
    unsigned long elapsed_time = current_time - start_time;
    long remaining_time = (long)actual_timer - (long)elapsed_time;
    float dt = (float)(current_time - previous_time_loop);
    if (dt == 0) dt = 1;
    if (elapsed_time >= actual_timer) {
      motorStop();
      break;
    }
    if (elapsed_time <= ramp_up && ramp_up > 0) {
      current_speed = min_speed + ((float)elapsed_time / ramp_up) * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down && ramp_down > 0) {
      current_speed = min_speed + ((float)remaining_time / ramp_down) * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else {
      current_speed = max_speed;
    }
    float error = Current_Degree - angleRead(YAW);
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = (error - previous_error) / dt;
    int pd_value = round((error * kp) + (derivative * kd));
    int pd_max_allowance = 80;
    if (pd_value > pd_max_allowance) pd_value = pd_max_allowance;
    else if (pd_value < -pd_max_allowance) pd_value = -pd_max_allowance;
    int base_speed = -round(current_speed);
    int speed_left = base_speed + pd_value;
    int speed_right = base_speed - pd_value;
    int max_calculated_speed = max(abs(speed_left), abs(speed_right));
    if (max_calculated_speed > 100) {
      speed_left = map(speed_left, -max_calculated_speed, max_calculated_speed, -100, 100);
      speed_right = map(speed_right, -max_calculated_speed, max_calculated_speed, -100, 100);
    }
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    previous_error = error;
    previous_time_loop = current_time;
    delay(10);
  }
}

void BB(int speed, float timer, char spin) {
  BB(speed, timer);
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
    ReadIRLED();
    if (IRLED_Data[0] <= 50 && IRLED_Data[1] <= 50) {
      motorStop();
      break;
    } else {
      if (IRLED_Data[0] <= 50) motorWrite(1, -12);
      else motorWrite(1, speed);
      if (IRLED_Data[1] <= 50) motorWrite(2, -12);
      else motorWrite(2, speed);
    }
  }
  vTaskDelay(Default_Delay / portTICK_PERIOD_MS);
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
    ReadIRLED();
    if (IRLED_Data[3] <= 50 && IRLED_Data[2] <= 50) {
      motorStop();
      break;
    } else {
      if (IRLED_Data[2] <= 50) motorWrite(2, 12);
      else motorWrite(2, -speed);
      if (IRLED_Data[3] <= 50) motorWrite(1, 12);
      else motorWrite(1, -speed);
    }
  }
  vTaskDelay(Default_Delay / portTICK_PERIOD_MS);
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
  vTaskDelay(Delay_LOW / portTICK_PERIOD_MS);
  unsigned long timer_turn = millis();
  unsigned long timeout_timer = millis();
  const unsigned long MAX_TIMEOUT_MS = 5000;
  int min_speed = 20;
  int max_speed = 100;
  float kp = 1.0;
  float kd = 1.0;
  float stop_threshold = 1.0;
  float target_degree = Current_Degree + relative_degree;
  while (target_degree > 180) target_degree -= 360;
  while (target_degree < -180) target_degree += 360;
  float initial_angle = angleRead(YAW);
  float previous_error = target_degree - initial_angle;
  if (previous_error > 180) previous_error -= 360;
  else if (previous_error < -180) previous_error += 360;
  while (1) {
    if (millis() - timeout_timer > MAX_TIMEOUT_MS) {
      motorStop();
      break;
    }
    float current_angle = angleRead(YAW);
    float error = target_degree - current_angle;
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    float derivative = error - previous_error;
    if (derivative > 180) derivative -= 360;
    else if (derivative < -180) derivative += 360;
    int pd_value = round((error * kp) + (derivative * kd));
    if (pd_value > 0) {
      if (pd_value < min_speed) pd_value = min_speed;
      if (pd_value > max_speed) pd_value = max_speed;
    } else if (pd_value < 0) {
      if (pd_value > -min_speed) pd_value = -min_speed;
      if (pd_value < -max_speed) pd_value = -max_speed;
    }
    if (abs(error) <= stop_threshold) {
      motorStop();
      if (millis() - timer_turn >= 100) break;
    } else {
      motorWrite(1, pd_value);
      motorWrite(2, -pd_value);
      timer_turn = millis();
    }
    previous_error = error;
    vTaskDelay(Delay_HW / portTICK_PERIOD_MS);
  }
  Current_Degree = angleRead(YAW);
  vTaskDelay(Delay_LOW / portTICK_PERIOD_MS);
}

void FFUltrasonic(int speed, float distance) {
  Ultrasonic_State = 1;
  unsigned long int timer = millis();
  while (ReadUltrasonic() > distance || millis() - timer <= 500) {
    FF(speed);
  }
  motorStop();
  Ultrasonic_State = 0;
}

void FFToF(int speed, float distance) {
  unsigned long int timer = millis();
  while (ReadToF() > distance || millis() - timer <= 500) {
    FF(speed);
  }
  MotorTimeDegree(speed, Time_Withdraw / 1.4);
  motorStop();
}