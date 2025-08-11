
/////////////////////////////////

void FF_Test(int speed, float timer) {
  int min_speed = 20;
  int max_speed = speed;
  // ปรับค่า PD ให้ต่ำลงเพื่อลดการแกว่ง
  float kp = 1.0;           // ลด KP จาก 6 → 1.0
  float kd = 0.2;           // ลด KD จาก 1.2 → 0.2
  ///
  float integral = 0;
  float ki = 0.1;         // เพิ่มค่า KI สำหรับเทคนิค PID แบบสมบูรณ์
  int ramp_up = 200;
  int ramp_down = 200;
  int current_speed = min_speed;
  unsigned long timer_forward = millis();
  unsigned long previous_time = millis();
  
  // เพิ่มตัวแปรกรองสัญญาณ
  float previous_error = 0;
  float filtered_error = 0;
  float alpha = 0.2;         // ค่า Filter (0.1-0.3)
  
  while (1) {
    unsigned long elapsed_time = millis() - timer_forward;
    unsigned long remaining_time = timer - elapsed_time;
    unsigned long current_time = millis();
    unsigned long dt = current_time - previous_time;
    previous_time = current_time;
    
    // คำนวณความเร็ว (เหมือนเดิม)
    if (elapsed_time <= ramp_up) {
      current_speed = min_speed + (float)elapsed_time / ramp_up * (max_speed - min_speed);
    } else if (remaining_time <= ramp_down) {
      current_speed = min_speed + (float)remaining_time / ramp_down * (max_speed - min_speed);
      if (current_speed < min_speed) current_speed = min_speed;
    } else {
      current_speed = max_speed;
    }
    
    // อ่านมุมและกรองสัญญาณรบกวน
    float raw_angle = angleRead(YAW);
    static float prev_filtered = 0;
    float filtered_angle = alpha * raw_angle + (1 - alpha) * prev_filtered;
    prev_filtered = filtered_angle;
    
    // คำนวณ error
    float error = current_degree - filtered_angle;
    if (error > 180) error -= 360;
    else if (error < -180) error += 360;
    
    // กรอง error (ลดการเปลี่ยนแปลงฉับพลัน)
    filtered_error = alpha * error + (1 - alpha) * filtered_error;
    
    // คำนวณอนุพันธ์แบบกรองแล้ว
    float derivative = filtered_error - previous_error;
    previous_error = filtered_error;
    
    //คำนวนค่าKi
    integral = integral + error * (dt / 1000.0); // คำนวณค่า Integral
    if (integral > max_speed / ki) integral = max_speed / ki; // จำกัดค่า Integral
    if (integral < -max_speed / ki) integral = -max_speed / ki; // จำกัดค่า Integral

    // คำนวณ PID + จำกัดค่าสูงสุด
    int pid_value = (filtered_error * kp) + (derivative * kd) + (integral * ki);
    pid_value = constrain(pid_value, -max_speed/3, max_speed/3); // จำกัดผล PID
    
    int speed_left = current_speed + pid_value;
    int speed_right = current_speed - pid_value;
    
    motorWrite(1, speed_left);
    motorWrite(2, speed_right);
    
    if (elapsed_time >= timer * power_factor) {
      motorStop();
      break;
    }
  }
}