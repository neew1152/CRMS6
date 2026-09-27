void SpinDegree(int relative_degree) {
  delay(125);
  const unsigned long MAX_TIMEOUT_MS = 5000;
  unsigned long timeout_timer = millis();
  unsigned long timer_turn = millis();
  int min_speed = 20;
  int max_speed = 100;
  float kp = 1.0;
  float kd = 1.0;
  float small_angle_threshold = 30.0;
  float stop_threshold = 2.0;
  float target_degree = current_degree + relative_degree;
  while (target_degree > 180)  target_degree -= 360;
  while (target_degree < -180) target_degree += 360;
  float previous_error = 0;

  while (1) {
    if (millis() - timeout_timer > MAX_TIMEOUT_MS) {
      motorStop();
      break;
    }
    float current_angle = angleRead(YAW);
    float error = target_degree - current_angle;
    if (error > 180)       error -= 360;
    else if (error < -180) error += 360;
    if (abs(error) <= stop_threshold) {
      motorStop();
      if (millis() - timer_turn >= 80) {
        break;
      }
    } 
    else if (error > 0 && error < small_angle_threshold) {
      motorWrite(1, min_speed);
      motorWrite(2, -min_speed);
      timer_turn = millis();
    } 
    else if (error < 0 && error > -small_angle_threshold) {
      motorWrite(1, -min_speed);
      motorWrite(2, min_speed);
      timer_turn = millis();
    } 
    else {
      float derivative = error - previous_error;
      if (derivative > 180)       derivative -= 360;
      else if (derivative < -180) derivative += 360;

      int pd_value = round((error * kp) + (derivative * kd));
      if (error > 0) {
        if (pd_value < min_speed) pd_value = min_speed;
        if (pd_value > max_speed) pd_value = max_speed;
      } else {
        if (pd_value > -min_speed) pd_value = -min_speed;
        if (pd_value < -max_speed) pd_value = -max_speed;
      }
      motorWrite(1, pd_value);
      motorWrite(2, -pd_value);
      timer_turn = millis();
    }
    previous_error = error;
  }
  motorStop();
  current_degree = angleRead(YAW);
  delay(125);
}
