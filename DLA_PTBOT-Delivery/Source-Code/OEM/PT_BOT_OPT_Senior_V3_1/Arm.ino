#define chanal_Swing_Left 0
#define chanal_Swing_Right 1
#define chanal_Gripper_Left 2
#define chanal_Gripper_Right 3
#define chanal_Stock_Tray_Left 4
#define chanal_Stock_Tray_Right 5

////////////////////////////////////////////////////////
int Swing_Left = 59;          //S0 สวิงแขนซ้าย เพิ่มง้างออก ลด หุบเข้า
int Swing_Right = 57;         //S1 สวิงแขนขวา เพิ่มง้างออก ลด หุบเข้า
int Swing_Left_side = 67;     //S0 สวิงแขนซ้าย วางป๋องซ้าย เพิ่มง้างออก ลด หุบเข้า
int Swing_Left_center = 37;   //S0 สวิงแขนซ้าย วางป๋องกลาง เพิ่มง้างออก ลด หุบเข้า
int Swing_Right_side = 66;    //S1 สวิงแขนขวา วางป๋องขวา เพิ่มง้างออก ลด หุบเข้า
int Swing_Right_center = 32;  //S1 สวิงแขนขวา วางป๋องกลาง เพิ่มง้างออก ลด หุบเข้า
////////////////////////////////////////////////////////
int Open_Left = 96;    //S2 อ้ามือ ชุดมือจับมือซ้ายค่ามากยิ่งหุบ
int Close_Left = 127;  //S2 หุบมือ ชุดมือจับมือซ้ายค่าน้อยยิ่งอ้า
////////////////////////////////////////////////////////
int Open_Right = 95;    //S3 อ้ามือ ชุดมือจับมือขวา ค่ามากยิ่งหุบ
int Close_Right = 130;  //S3 หุบมือ ชุดมือจับมือขวา ค่าน้อยยิ่งอ้า
////////////////////////////////////////////////////////
int Tray_In_Left = 130;    // S4 เก็บถาดด้านซ้ายเข้า ค่ามากยิ่งเข้า
int Tray_Out_Left = 38;    // S4 เอาถาดด้านซ้ายออก ค่าน้อยยิ่งออก
int Tray_In_Right = 22;    // S5 เก็บถาดด้านซ้ายเข้า ค่าน้อยยิ่งเข้า
int Tray_Out_Right = 118;  // S5 เอาถาดด้านซ้ายออก ค่ามากยิ่งออก
int Stock_Left = 141;      // S0 สวิงแขนเก็บกระป๋องซ้าย เพิ่มง้างออก ลด หุบเข้า
int Stock_Right = 141;     // S1 สวิงแขนเก็บกระป๋องขวา เพิ่มง้างออก ลด หุบเข้า
////////////////////////////////////////////////////////

int Open_Drop_Left = 9;
int Open_Drop_Right = 9;

int switch_degree = 22;
int switch_flag = 0;
int stock_flag = 0;
int lift_target = 0;
int swing_current_degree[] = { 0, 0 };
char can_in_gripper[2] = { 'u', 'u' };
char can_in_stock[2] = { 'u', 'u' };
char station[3][3] = {
  { 'u', 'u', 'u' },
  { 'u', 'u', 'u' },
  { 'u', 'u', 'u' }
};
int station_count = 0;

ESP32Encoder encoder;

void setupServo() {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  servoWrite(chanal_Stock_Tray_Left, Tray_In_Left);
  servoWrite(chanal_Stock_Tray_Right, Tray_In_Right);
}

void servoOpenLeft() {
  for (int i = Close_Left; i > Open_Left; i--) {
    servoWrite(chanal_Gripper_Left, i);
    delay(5);
  }
}

void servoCloseLeft() {
  servoWrite(chanal_Gripper_Left, Close_Left);
}

void servoOpenRight() {
  for (int i = Close_Right; i > Open_Right; i--) {
    servoWrite(chanal_Gripper_Right, i);
    delay(5);
  }
}

void servoCloseRight() {
  servoWrite(chanal_Gripper_Right, Close_Right);
}

void extendArm() {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
}

void retractArm() {
  swingGripper('l', Swing_Left + 65);
  swingGripper('r', Swing_Right + 65);
}

void setPlaceTime(float timeleft_side, float timeleft_center, float timeright_side, float timeright_center) {
  place_left_side = timeleft_side;
  place_left_center = timeleft_center;
  place_right_side = timeright_side;
  place_right_center = timeright_center;
}

void assemblyMode() {
  lift(10);
  int swing_left = 60;
  int swing_right = 60;
  int close_left = 80;
  int open_left = close_left - 30;
  int close_right = 80;
  int open_right = close_right - 30;
  int tray_in_left = 120;
  int tray_in_right = 50;
  int tray_out_left = tray_in_left - 70;
  int tray_out_right = tray_in_right + 70;
  int stock_left = swing_left + 90;
  int stock_right = swing_right + 90;
  unsigned long timer_servo = 0;
  servoWrite(chanal_Swing_Left, swing_left);
  servoWrite(chanal_Swing_Right, swing_right);
  servoWrite(chanal_Gripper_Left, close_left);
  servoWrite(chanal_Gripper_Right, close_right);
  servoWrite(chanal_Stock_Tray_Left, Tray_In_Left);
  servoWrite(chanal_Stock_Tray_Right, Tray_In_Right);
  lcdClear();
  lcdSetTextSize(2);
  lcdPrintText(2, 55, "ASSEMBLY MODE", 0xf800);
  while (!switchRead(A) || !switchRead(B)) {};
  beep(50);
  while (switchRead(A) || switchRead(B)) {};
  Serial.println("หาค่า Swing Left");
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      swing_left += 1;
      beep(20);
    } else if (switchRead(B)) {
      swing_left -= 1;
      beep(20);
    }
    servoWrite(chanal_Swing_Left, swing_left);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Swing Right");
  swing_right = swing_left;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      swing_right -= 1;
      beep(20);
    } else if (switchRead(B)) {
      swing_right += 1;
      beep(20);
    }
    servoWrite(chanal_Swing_Right, swing_right);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Close Left");
  timer_servo = millis();
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      close_left -= 1;
      beep(20);
    } else if (switchRead(B)) {
      close_left += 1;
      beep(20);
    }
    if (millis() - timer_servo <= 1000) servoWrite(chanal_Gripper_Left, close_left);
    else if (millis() - timer_servo > 1000 && millis() - timer_servo <= 2000) servoWrite(chanal_Gripper_Left, close_left - 15);
    else timer_servo = millis();
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Close Right");
  timer_servo = millis();
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      close_right -= 1;
      beep(20);
    } else if (switchRead(B)) {
      close_right += 1;
      beep(20);
    }
    if (millis() - timer_servo <= 1000) servoWrite(chanal_Gripper_Right, close_right);
    else if (millis() - timer_servo > 1000 && millis() - timer_servo <= 2000) servoWrite(chanal_Gripper_Right, close_right - 15);
    else timer_servo = millis();
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Open Left");
  open_left = close_left - 30;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      open_left -= 1;
      beep(20);
    } else if (switchRead(B)) {
      open_left += 1;
      beep(20);
    }
    servoWrite(chanal_Gripper_Left, open_left);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Open Right");
  open_right = close_right - 30;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      open_right -= 1;
      beep(20);
    } else if (switchRead(B)) {
      open_right += 1;
      beep(20);
    }
    servoWrite(chanal_Gripper_Right, open_right);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Tray In Left");
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      tray_in_left -= 2;
      beep(20);
    } else if (switchRead(B)) {
      tray_in_left += 2;
      beep(20);
    }
    servoWrite(chanal_Stock_Tray_Left, tray_in_left);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Tray In Right");
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      tray_in_right -= 2;
      beep(20);
    } else if (switchRead(B)) {
      tray_in_right += 2;
      beep(20);
    }
    servoWrite(chanal_Stock_Tray_Right, tray_in_right);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Tray Out Left");
  tray_out_left = tray_in_left - 70;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      tray_out_left -= 2;
      beep(20);
    } else if (switchRead(B)) {
      tray_out_left += 2;
      beep(20);
    }
    servoWrite(chanal_Stock_Tray_Left, tray_out_left);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Tray Out Right");
  tray_out_right = tray_in_right + 70;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      tray_out_right -= 2;
      beep(20);
    } else if (switchRead(B)) {
      tray_out_right += 2;
      beep(20);
    }
    servoWrite(chanal_Stock_Tray_Right, tray_out_right);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Stock Left");
  stock_left = swing_left + 90;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      stock_left -= 1;
      beep(20);
    } else if (switchRead(B)) {
      stock_left += 1;
      beep(20);
    }
    servoWrite(chanal_Swing_Left, stock_left);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่า Stock Right");
  stock_right = swing_right + 90;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      stock_right += 1;
      beep(20);
    } else if (switchRead(B)) {
      stock_right -= 1;
      beep(20);
    }
    servoWrite(chanal_Swing_Right, stock_right);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่ามือจับซ้าย วางป๋องหลุมซ้าย Swing Left side");
  Swing_Left_side = Swing_Left + 12;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      Swing_Left_side += 1;
      beep(20);
    } else if (switchRead(B)) {
      Swing_Left_side -= 1;
      beep(20);
    }
    servoWrite(chanal_Swing_Left, Swing_Left_side);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่ามือจับซ้าย วางป๋องหลุมกลาง Swing Left center");
  Swing_Left_center = Swing_Left - 22;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      Swing_Left_center += 1;
      beep(20);
    } else if (switchRead(B)) {
      Swing_Left_center -= 1;
      beep(20);
    }
    servoWrite(chanal_Swing_Left, Swing_Left_center);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  servoWrite(chanal_Swing_Left, Swing_Left_side);
  Serial.println("หาค่ามือจับขวา วางป๋องหลุมขวา Swing Right side");
  Swing_Right_side = Swing_Right + 12;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      Swing_Right_side -= 1;
      beep(20);
    } else if (switchRead(B)) {
      Swing_Right_side += 1;
      beep(20);
    }
    servoWrite(chanal_Swing_Right, Swing_Right_side);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  Serial.println("หาค่ามือจับขวา วางป๋องหลุมกลาง Swing Right center");
  Swing_Right_center = Swing_Right - 22;
  while (1) {
    if (switchRead(A) && switchRead(B)) break;
    else if (switchRead(A)) {
      Swing_Right_center -= 1;
      beep(20);
    } else if (switchRead(B)) {
      Swing_Right_center += 1;
      beep(20);
    }
    servoWrite(chanal_Swing_Right, Swing_Right_center);
    delay(200);
  }
  beep(50);
  delay(50);
  beep(50);
  while (switchRead(A) || switchRead(B)) {};

  servoWrite(chanal_Swing_Left, swing_left);
  servoWrite(chanal_Swing_Right, swing_right);
  servoWrite(chanal_Gripper_Left, open_left);
  servoWrite(chanal_Gripper_Right, open_right);
  servoWrite(chanal_Stock_Tray_Left, tray_in_left);
  servoWrite(chanal_Stock_Tray_Right, tray_in_right);
  delay(1000);
  lift(3);

  Serial.println("////////////////////////////////////////////////////////");
  Serial.println("int Swing_Left = " + String(swing_left) + "; //S0 สวิงแขนซ้าย เพิ่มง้างออก ลด หุบเข้า");
  Serial.println("int Swing_Right = " + String(swing_right) + "; //S1 สวิงแขนขวา เพิ่มง้างออก ลด หุบเข้า");
  Serial.println("int Swing_Left_side = " + String(Swing_Left_side) + "; //S0 สวิงแขนซ้าย วางป๋องซ้าย เพิ่มง้างออก ลด หุบเข้า");
  Serial.println("int Swing_Left_center = " + String(Swing_Left_center) + "; //S0 สวิงแขนซ้าย วางป๋องกลาง เพิ่มง้างออก ลด หุบเข้า");
  Serial.println("int Swing_Right_side = " + String(Swing_Right_side) + "; //S1 สวิงแขนขวา วางป๋องขวา เพิ่มง้างออก ลด หุบเข้า");
  Serial.println("int Swing_Right_center = " + String(Swing_Right_center) + "; //S1 สวิงแขนขวา วางป๋องกลาง เพิ่มง้างออก ลด หุบเข้า");
  Serial.println("////////////////////////////////////////////////////////");
  Serial.println("int Open_Left = " + String(open_left) + "; //S2 อ้ามือ ชุดมือจับมือซ้ายค่ามากยิ่งหุบ");
  Serial.println("int Close_Left = " + String(close_left) + "; //S2 หุบมือ ชุดมือจับมือซ้ายค่าน้อยยิ่งอ้า");
  Serial.println("////////////////////////////////////////////////////////");
  Serial.println("int Open_Right = " + String(open_right) + "; //S3 อ้ามือ ชุดมือจับมือขวา ค่ามากยิ่งหุบ");
  Serial.println("int Close_Right = " + String(close_right) + "; //S3 หุบมือ ชุดมือจับมือขวา ค่าน้อยยิ่งอ้า");
  Serial.println("////////////////////////////////////////////////////////");
  Serial.println("int Tray_In_Left = " + String(tray_in_left) + "; // S4 เก็บถาดด้านซ้ายเข้า ค่ามากยิ่งเข้า");
  Serial.println("int Tray_Out_Left = " + String(tray_out_left) + "; // S4 เอาถาดด้านซ้ายออก ค่าน้อยยิ่งออก");
  Serial.println("int Tray_In_Right = " + String(tray_in_right) + "; // S5 เก็บถาดด้านซ้ายเข้า ค่าน้อยยิ่งเข้า");
  Serial.println("int Tray_Out_Right = " + String(tray_out_right) + "; // S5 เอาถาดด้านซ้ายออก ค่ามากยิ่งออก");
  Serial.println("int Stock_Left = " + String(stock_left) + "; // S0 สวิงแขนเก็บกระป๋องซ้าย เพิ่มง้างออก ลด หุบเข้า");
  Serial.println("int Stock_Right = " + String(stock_right) + "; // S1 สวิงแขนเก็บกระป๋องขวา เพิ่มง้างออก ลด หุบเข้า");
  Serial.println("////////////////////////////////////////////////////////");
}

void setCan() {
  lift(1);
  delay(150);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  delay(300);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(300);
  lift(3);
  delay(300);
}

void switchGripperLoop(void *pvParameters) {
  while (1) {
    if (switch_flag == -1) {
      servoWrite(chanal_Gripper_Left, Open_Left);
      servoWrite(chanal_Swing_Right, Swing_Right + 35);
      delay(200);
      servoWrite(chanal_Swing_Left, Swing_Left - 25);
      servoWrite(chanal_Swing_Right, Swing_Right - 25);
      delay(200);
      servoCloseLeft();
      delay(300);
      servoWrite(chanal_Gripper_Right, Open_Right);
      delay(300);
      swing_current_degree[0] = Swing_Left + (switch_degree - 10);
      swing_current_degree[1] = Swing_Right + 65;
      servoWrite(chanal_Swing_Left, swing_current_degree[0]);
      servoWrite(chanal_Swing_Right, swing_current_degree[1]);
      switch_flag = 0;
    } else if (switch_flag == 1) {
      servoWrite(chanal_Gripper_Right, Open_Right);
      servoWrite(chanal_Swing_Left, Swing_Left + 35);
      delay(200);
      servoWrite(chanal_Swing_Left, Swing_Left - 25);
      servoWrite(chanal_Swing_Right, Swing_Right - 25);
      delay(200);
      servoCloseRight();
      delay(300);
      servoWrite(chanal_Gripper_Left, 0);
      delay(300);
      swing_current_degree[0] = Swing_Left + 65;
      swing_current_degree[1] = Swing_Right + (switch_degree - 10);
      servoWrite(chanal_Swing_Left, swing_current_degree[0]);
      servoWrite(chanal_Swing_Right, swing_current_degree[1]);
      switch_flag = 0;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void switchGripper(char from_gripper, char to_gripper) {
  if (from_gripper == 'l' && to_gripper == 'r') switch_flag = 1;
  else if (from_gripper == 'r' && to_gripper == 'l') switch_flag = -1;
}

void swingGripper(char gripper, int degree) {
  if (gripper == 'l') {
    swing_current_degree[0] = degree;
    servoWrite(chanal_Swing_Left, swing_current_degree[0]);
  } else if (gripper == 'r') {
    swing_current_degree[1] = degree;
    servoWrite(chanal_Swing_Right, swing_current_degree[1]);
  }
}

void liftLoop(void *pvParameters) {
  const int CLK = 39;
  const int DT = 36;
  float error, previous_error = 0, integral = 0, derivative;
  float p_value, i_value, d_value, motor_speed;
  float Kp = 3.0, Ki = 0.001, Kd = 0.05;

  encoder.attachHalfQuad(DT, CLK);
  encoder.setCount(0);

  long last_encoder_count = 0;
  unsigned long last_change_time = millis();
  const unsigned long timeout_ms = 500;

  int last_lift_target = lift_target;
  bool stopped_due_to_timeout = false;

  while (1) {
    long current_count = encoder.getCount() / 2;
    error = current_count - lift_target;

    // ตรวจจับการเปลี่ยนแปลงของ encoder
    if (abs(abs(current_count) - abs(last_encoder_count)) > 5) {
      last_change_time = millis();
      last_encoder_count = current_count;
    }

    // ตรวจสอบว่ามีการเปลี่ยนแปลง lift_target หรือไม่
    if (lift_target != last_lift_target) {
      // หากเคยหยุดจาก timeout ให้เริ่มใหม่
      stopped_due_to_timeout = false;
      last_change_time = millis();
      integral = 0;
      previous_error = 0;
      last_lift_target = lift_target;
    }

    // หยุดหาก encoder ไม่ขยับเป็นระยะเวลาหนึ่ง
    if (!stopped_due_to_timeout && millis() - last_change_time > timeout_ms) {
      motorWrite(3, 0);
      stopped_due_to_timeout = true;
    }

    // หากอยู่ในสถานะหยุดจาก timeout ให้รอจน lift_target เปลี่ยนก่อนจะกลับมาทำงาน
    if (stopped_due_to_timeout) {
      vTaskDelay(10 / portTICK_PERIOD_MS);
      continue;
    }

    // PID control
    p_value = Kp * error;
    integral += error;
    i_value = Ki * integral;
    derivative = error - previous_error;
    d_value = Kd * derivative;
    motor_speed = p_value + i_value + d_value;

    motor_speed = constrain(motor_speed, -100, 100);

    if (abs(error) >= 5)
      motorWrite(3, motor_speed);
    else
      motorWrite(3, 0);

    previous_error = error;
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void lift(int position) {
  if (position > 17) position = 17;
  lift_target = position * 28;
  if (lift_target > 900) lift_target = 900;
}

void stockLoop(void *pvParameters) {
  while (1) {
    if (stock_flag == -1) {
      lift(13);
      while (abs((encoder.getCount() / 2) - lift_target) > 30) {};
      servoWrite(chanal_Stock_Tray_Left, Tray_Out_Left);
      servoWrite(chanal_Swing_Left, Stock_Left);
      delay(800);
      lift(9);
      while (abs((encoder.getCount() / 2) - lift_target) > 30) {};
      delay(300);
      servoWrite(chanal_Gripper_Left, Close_Left - 15);
      delay(200);
      servoWrite(chanal_Gripper_Left, 0);
      delay(200);
      servoWrite(chanal_Stock_Tray_Left, Tray_In_Left);
      delay(250);
      servoWrite(chanal_Swing_Left, Swing_Left);
      delay(250);
      servoWrite(chanal_Gripper_Left, Open_Left);
      lift(3);
      stock_flag = 0;
    } else if (stock_flag == 1) {
      lift(15);
      while (abs((encoder.getCount() / 2) - lift_target) > 30) {};
      servoWrite(chanal_Stock_Tray_Left, Tray_Out_Left);
      servoWrite(chanal_Gripper_Left, Open_Left);
      servoWrite(chanal_Swing_Left, Stock_Left);
      delay(550);
      lift(7);
      while (abs((encoder.getCount() / 2) - lift_target) > 30) {};
      delay(200);
      servoWrite(chanal_Gripper_Left, Close_Left + 3);
      delay(200);
      lift(15);
      delay(400);
      servoWrite(chanal_Swing_Left, Swing_Left);
      servoWrite(chanal_Stock_Tray_Left, Tray_In_Left);
      can_in_gripper[0] = can_in_stock[0];
      can_in_stock[0] = 'u';
      delay(500);
      lift(3);
      stock_flag = 0;
    } else if (stock_flag == -2) {
      lift(13);
      while (abs((encoder.getCount() / 2) - lift_target) > 30) {};
      servoWrite(chanal_Stock_Tray_Right, Tray_Out_Right);
      servoWrite(chanal_Swing_Right, Stock_Right);
      delay(800);
      lift(9);
      while (abs((encoder.getCount() / 2) - lift_target) > 30) {};
      delay(300);
      servoWrite(chanal_Gripper_Right, Close_Right - 15);
      delay(200);
      servoWrite(chanal_Gripper_Right, 0);
      delay(200);
      servoWrite(chanal_Stock_Tray_Right, Tray_In_Right);
      delay(250);
      servoWrite(chanal_Swing_Right, Swing_Right);
      delay(250);
      servoWrite(chanal_Gripper_Right, Open_Right);
      lift(3);
      stock_flag = 0;
    } else if (stock_flag == 2) {
      lift(15);
      while (abs((encoder.getCount() / 2) - lift_target) > 30) {};
      delay(200);
      servoWrite(chanal_Stock_Tray_Right, Tray_Out_Right);
      servoWrite(chanal_Gripper_Right, Open_Right);
      servoWrite(chanal_Swing_Right, Stock_Right);
      delay(550);
      lift(7);
      while (abs((encoder.getCount() / 2) - lift_target) > 30) {};
      delay(200);
      servoWrite(chanal_Gripper_Right, Close_Right + 3);
      delay(200);
      lift(15);
      delay(400);
      servoWrite(chanal_Swing_Right, Swing_Right);
      servoWrite(chanal_Stock_Tray_Right, Tray_In_Right);
      can_in_gripper[1] = can_in_stock[1];
      can_in_stock[1] = 'u';
      delay(500);
      lift(3);
      stock_flag = 0;
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void stockIn(char stock, char color, bool wait) {
  switch_flag = 0;
  if (stock == 'l') {
    stock_flag = -1;
    can_in_stock[0] = color;
  } else if (stock == 'r') {
    stock_flag = -2;
    can_in_stock[1] = color;
  }
  if (wait == true) {
    while (1) {
      if (stock_flag == 0) break;
      delay(10);
    }
  }
}

void stockOut(char stock, bool wait) {
  switch_flag = 0;
  if (stock == 'l') stock_flag = 1;
  else if (stock == 'r') stock_flag = 2;
  if (wait == true) {
    while (1) {
      if (stock_flag == 0) break;
      delay(10);
    }
  }
}

void moveToCan(int distance) {
  vTaskResume(sonarTaskHandle);
  sonar_enable = 1;
  delay(10);
  unsigned long int timer = millis();
  while (readSonar() > distance || millis() - timer <= 500) FF(15);
  FF(10, 250);
  motorWrite(1, 0);
  motorWrite(2, 0);
  vTaskSuspend(sonarTaskHandle);
  sonar_enable = 0;
}

void moveToCan0(int distance) {
  unsigned long int timer = millis();
  int current_distance = 0;
  while (current_distance == -1 || current_distance > distance || millis() - timer <= 500) {
    current_distance = readCanDistance();
    FF(15);
  }
  FF(10, 250);
  motorWrite(1, 0);
  motorWrite(2, 0);
}

void moveToCanTime(int time) {
  unsigned long int timer = millis();
  while (millis() - timer < time) FF(15);
  motorWrite(1, 0);
  motorWrite(2, 0);
}

void shakeGripper(char gripper) {
  int increment = 1;
  int delayTime = 18;
  int swingRange = 10;
  for (int i = 0; i < 3; i++) {
    if (gripper == 'l' || gripper == 'a') {
      for (int i = 0; i <= swingRange; i += increment) {
        servoWrite(chanal_Swing_Left, swing_current_degree[0] - i);
        if (gripper == 'a') servoWrite(chanal_Swing_Right, swing_current_degree[1] - i);
        delay(delayTime);
      }
      for (int i = 0; i <= swingRange * 2; i += increment) {
        servoWrite(chanal_Swing_Left, swing_current_degree[0] - swingRange + i);
        if (gripper == 'a') servoWrite(chanal_Swing_Right, swing_current_degree[1] - swingRange + i);
        delay(delayTime);
      }
      for (int i = 0; i <= swingRange; i += increment) {
        servoWrite(chanal_Swing_Left, swing_current_degree[0] + swingRange - i);
        if (gripper == 'a') servoWrite(chanal_Swing_Right, swing_current_degree[1] + swingRange - i);
        delay(delayTime);
      }
    }
    if (gripper == 'r' || gripper == 'a') {
      for (int i = 0; i <= swingRange; i += increment) {
        servoWrite(chanal_Swing_Right, swing_current_degree[1] - i);
        if (gripper == 'a') servoWrite(chanal_Swing_Left, swing_current_degree[0] - i);
        delay(delayTime);
      }
      for (int i = 0; i <= swingRange * 2; i += increment) {
        servoWrite(chanal_Swing_Right, swing_current_degree[1] - swingRange + i);
        if (gripper == 'a') servoWrite(chanal_Swing_Left, swing_current_degree[0] - swingRange + i);
        delay(delayTime);
      }
      for (int i = 0; i <= swingRange; i += increment) {
        servoWrite(chanal_Swing_Right, swing_current_degree[1] + swingRange - i);
        if (gripper == 'a') servoWrite(chanal_Swing_Left, swing_current_degree[0] + swingRange - i);
        delay(delayTime);
      }
    }
  }
}

void dropCan(char gripper) {
  int tmp_Open_Left, tmp_Open_Right;
  tmp_Open_Left = Open_Left - 15;
  tmp_Open_Right = Open_Right - 15;
  if (tmp_Open_Left <= 0) tmp_Open_Left = 0;
  else {}
  if (tmp_Open_Right <= 0) tmp_Open_Right = 0;
  else {}

  if (gripper == 'l') {
    servoWrite(chanal_Gripper_Left, Close_Left - Open_Drop_Left);
    shakeGripper('l');
    delay(200);
    servoWrite(chanal_Gripper_Left, tmp_Open_Left);
  } else if (gripper == 'r') {
    servoWrite(chanal_Gripper_Right, Close_Right - Open_Drop_Right);
    shakeGripper('r');
    delay(200);
    servoWrite(chanal_Gripper_Right, tmp_Open_Right);
  } else if (gripper == 'a') {
    servoWrite(chanal_Gripper_Left, Close_Left - Open_Drop_Left);
    servoWrite(chanal_Gripper_Right, Close_Right - Open_Drop_Right);
    shakeGripper('a');
    delay(200);
    servoWrite(chanal_Gripper_Left, tmp_Open_Left);
    servoWrite(chanal_Gripper_Right, tmp_Open_Right);
  }
}

void autoPickCan(int pick_height) {
  servoWrite(chanal_Swing_Left, Swing_Left - 3);
  servoWrite(chanal_Swing_Right, Swing_Right - 3);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) moveToCan(pick_can_distance);
  else moveToCan0(can_distance);
  delay(100);
  servoCloseLeft();
  servoCloseRight();
  delay(200);
  lift(pick_height + 2);
  delay(300);
  can_in_gripper[0] = readColor('l');
  can_in_gripper[1] = readColor('r');
  if (can_in_gripper[0] == can_in_gripper[1]) {
    if (can_in_gripper[0] == 'r') {
      if (can_in_stock[0] == 'u') {
        stockIn('l', can_in_gripper[0], false);
        can_in_gripper[0] = 'u';
        can_in_gripper[1] = 'r';
      } else if (can_in_stock[1] == 'u') {
        stockIn('r', can_in_gripper[0], false);
        can_in_gripper[0] = 'r';
        can_in_gripper[1] = 'u';
      } else {
        while (1) {
          beep(10000);
        }
      }
    } else {
      if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'l';
      else if (can_in_gripper[0] == 'y') can_in_gripper[0] = 'c';
      if (can_in_stock[1] == 'u') {
        stockIn('r', can_in_gripper[0], false);
        can_in_gripper[1] = 'u';
      } else if (can_in_stock[0] == 'u') {
        stockIn('l', can_in_gripper[0], false);
        can_in_gripper[1] = can_in_gripper[0];
        can_in_gripper[0] = 'u';
      } else {
        while (1) {
          beep(10000);
        }
      }
    }
    BB(30, 400);
  } else {
    if (can_in_gripper[0] == 'r' && can_in_gripper[1] == 'g') {
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      swingGripper('l', Swing_Left_center - 5);
      delay(200);
      servoWrite(chanal_Gripper_Left, Close_Left - 15);
      delay(200);
      servoWrite(chanal_Gripper_Left, 0);
      delay(500);
      BB(30, 400);
      switchGripper('r', 'l');
      delay(1200);
      swingGripper('l', Swing_Left_side + 5);
      servoWrite(chanal_Gripper_Right, 0);
      swingGripper('r', Swing_Right_center - 5);
      delay(200);
      moveToCan(pick_can_distance);
      lift(pick_height + 2);
      servoCloseRight();
      delay(200);
      vTaskSuspend(switchGripperTaskHandle);
      servoWrite(chanal_Swing_Left, Swing_Left);
      servoWrite(chanal_Swing_Right, Swing_Right);
      can_in_gripper[0] = 'l';
      can_in_gripper[1] = 'r';
      BB(30, 450);
    } else {
      if (can_in_gripper[0] == 'r') can_in_gripper[0] = 'r';
      else if (can_in_gripper[0] == 'g') can_in_gripper[0] = 'l';
      else if (can_in_gripper[0] == 'y') can_in_gripper[0] = 'c';
      if (can_in_gripper[1] == 'r') can_in_gripper[1] = 'r';
      else if (can_in_gripper[1] == 'g') can_in_gripper[1] = 'l';
      else if (can_in_gripper[1] == 'y') can_in_gripper[1] = 'c';
      BB(30, 400);
      lift(3);
    }
  }
}

void placeCan1(int drop_height, int distance, char from_gripper, char drop_point) {
  bool switch_can = 0;
  servoWrite(chanal_Gripper_Left, Close_Left + 3);
  servoWrite(chanal_Gripper_Right, Close_Right + 3);
  lift(drop_height + 3);
  if (from_gripper == 'l' && drop_point == 'l') {
    swingGripper('l', Swing_Left_side);
    swingGripper('r', Swing_Right + 65);
  } else if (from_gripper == 'l' && drop_point == 'c') {
    swingGripper('l', Swing_Left_center);
    swingGripper('r', Swing_Right + 65);
  } else if (from_gripper == 'r' && drop_point == 'r') {
    swingGripper('l', Swing_Left + 65);
    swingGripper('r', Swing_Right_side);
  } else if (from_gripper == 'r' && drop_point == 'c') {
    swingGripper('l', Swing_Left + 65);
    swingGripper('r', Swing_Right_center);
  } else {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    switchGripper(from_gripper, drop_point);
    switch_can = 1;
  }
  moveToCan(4.0);
  motorWrite(1, 10);
  motorWrite(2, 10);
  delay(400);
  motorWrite(1, 0);
  motorWrite(2, 0);
  delay(200);
  setAngleOffset();
  current_degree = 0;
  BB(10, distance);
  lift(drop_height);
  delay(200);
  if (switch_can == 0) dropCan(from_gripper);
  else dropCan(drop_point);
  delay(200);
  vTaskSuspend(switchGripperTaskHandle);
}

void autoPlaceCan2(int drop_height, char left_gripper, char right_gripper) {
  servoWrite(chanal_Gripper_Left, Close_Left + 3);
  servoWrite(chanal_Gripper_Right, Close_Right + 3);
  lift(drop_height + 3);
  if (left_gripper == 'r' && right_gripper == 'l') {
    moveToCan(place_left_center + 5);
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    swingGripper('l', Swing_Left - (switch_degree + 5));
    delay(200);
    servoWrite(chanal_Gripper_Left, Open_Left);
    delay(200);
    swingGripper('l', Swing_Left - switch_degree);
    delay(200);
    BB(30, 400);
    switchGripper('r', 'l');
    delay(1200);
    servoWrite(chanal_Gripper_Right, Open_Right);
    swingGripper('r', Swing_Right - (switch_degree + 5));
    lift(drop_height + 3);
    moveToCan(place_left_center + 5);
    servoCloseRight();
    delay(200);
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
    vTaskSuspend(switchGripperTaskHandle);
    BB(30, 500);
    placeCan1(drop_height, place_left_side, 'l', 'l');
    BB(30, 600);
    delay(200);
    placeCan1(drop_height, place_right_side, 'r', 'r');
  } else {
    if (left_gripper == 'l' && right_gripper == 'r') {
      placeCan1(drop_height, place_right_side, 'l', 'l');
      BB(30, 500);
      delay(200);
      placeCan1(drop_height, place_right_side, 'r', 'r');
    } else if (left_gripper == 'l' && right_gripper == 'c') {
      placeCan1(drop_height, place_right_center, 'r', 'c');
      BB(30, 500);
      delay(200);
      placeCan1(drop_height, place_left_side, 'l', 'l');
    } else if (left_gripper == 'c' && right_gripper == 'r') {
      placeCan1(drop_height, place_left_center, 'l', 'c');
      BB(30, 500);
      delay(200);
      placeCan1(drop_height, place_right_side, 'r', 'r');
    } else {
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      if (left_gripper == 'c') {
        swingGripper('l', Swing_Left_center);
        swingGripper('r', Swing_Right + 65);
        moveToCan(4.0);
        motorWrite(1, 10);
        motorWrite(2, 10);
        delay(400);
        motorWrite(1, 0);
        motorWrite(2, 0);
        delay(200);
        setAngleOffset();
        current_degree = 0;
        BB(10, place_left_center);
        lift(drop_height);
        delay(200);
        dropCan('l');
        delay(200);
        BB(30, 500);
        lift(drop_height + 3);
        switchGripper('r', 'l');
        delay(1200);
        if (drop_height >= 15) {
          lift(1);
          delay(900);
          setCan();
          lift(drop_height);
          delay(900);
        } else {
        }
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('r', Swing_Right + 65);
        moveToCan(4.0);
        motorWrite(1, 10);
        motorWrite(2, 10);
        delay(400);
        motorWrite(1, 0);
        motorWrite(2, 0);
        delay(200);
        setAngleOffset();
        current_degree = 0;
        BB(10, place_left_side);
        lift(drop_height);
        delay(200);
        dropCan('l');
      } else if (right_gripper == 'c') {
        swingGripper('r', Swing_Right_center);
        swingGripper('l', Swing_Left + 65);
        moveToCan(4.0);
        motorWrite(1, 10);
        motorWrite(2, 10);
        delay(400);
        motorWrite(1, 0);
        motorWrite(2, 0);
        delay(200);
        setAngleOffset();
        current_degree = 0;
        BB(10, place_right_center);
        lift(drop_height);
        delay(200);
        dropCan('r');
        delay(200);
        BB(30, 500);
        lift(drop_height + 3);
        switchGripper('l', 'r');
        delay(1200);
        if (drop_height >= 15) {
          lift(1);
          delay(900);
          setCan();
          lift(drop_height);
          delay(900);
        } else {
        }
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('l', Swing_Left + 65);
        moveToCan(4.0);
        motorWrite(1, 10);
        motorWrite(2, 10);
        delay(400);
        motorWrite(1, 0);
        motorWrite(2, 0);
        delay(200);
        setAngleOffset();
        current_degree = 0;
        BB(10, place_right_side);
        lift(drop_height);
        delay(200);
        dropCan('r');
      }
    }
  }
  delay(200);
  vTaskSuspend(switchGripperTaskHandle);
}

void autoPlaceCan(int drop_height, bool increment_count = true) {
  servoWrite(chanal_Gripper_Left, Close_Left + 3);
  servoWrite(chanal_Gripper_Right, Close_Right + 3);
  lift(drop_height + 3);
  if (can_in_gripper[0] != 'u' && can_in_gripper[1] != 'u') {
    autoPlaceCan2(drop_height, can_in_gripper[0], can_in_gripper[1]);
  } else {
    if (can_in_gripper[0] != 'u') {
      if (can_in_gripper[0] == 'l') placeCan1(drop_height, place_left_side, 'l', can_in_gripper[0]);
      else if (can_in_gripper[0] == 'c') placeCan1(drop_height, place_left_center, 'l', can_in_gripper[0]);
      else if (can_in_gripper[0] == 'r') {
        vTaskResume(switchGripperTaskHandle);
        swingGripper('l', Swing_Left);
        swingGripper('r', Swing_Right);
        delay(600);
        switchGripper('l', 'r');
        delay(1200);
        if (drop_height >= 15) {
          lift(1);
          delay(900);
          setCan();
          lift(drop_height);
          delay(900);
        } else {
        }
        placeCan1(drop_height, place_right_side, 'r', can_in_gripper[0]);
      }
    } else {
      if (can_in_gripper[1] == 'r') placeCan1(drop_height, place_right_side, 'r', can_in_gripper[1]);
      else if (can_in_gripper[1] == 'c') placeCan1(drop_height, place_right_center, 'r', can_in_gripper[1]);
      else if (can_in_gripper[1] == 'l') {
        vTaskResume(switchGripperTaskHandle);
        swingGripper('l', Swing_Left);
        swingGripper('r', Swing_Right);
        delay(600);
        switchGripper('r', 'l');
        delay(1200);
        if (drop_height >= 15) {
          lift(1);
          delay(900);
          setCan();
          lift(drop_height);
          delay(900);
        } else {
        }
        placeCan1(drop_height, place_left_side, 'l', can_in_gripper[1]);
      }
    }
  }
  vTaskSuspend(switchGripperTaskHandle);
  checkPlace(drop_height, station_count);
  if (increment_count) station_count += 1;
  servoCloseLeft();
  servoCloseRight();
}

void checkPlace(int drop_height, int current_station) {
  if (can_in_gripper[0] == 'l' || can_in_gripper[1] == 'l') station[current_station][0] = 'l';
  if (can_in_gripper[0] == 'c' || can_in_gripper[1] == 'c') station[current_station][1] = 'c';
  if (can_in_gripper[0] == 'r' || can_in_gripper[1] == 'r') station[current_station][2] = 'r';

  for (byte i = 0; i < 3; i++) {
    if (station[current_station][i] == 'u') {
      if (i == 0) {
        if (can_in_stock[0] == 'l') {
          BB(30, 400);
          delay(100);
          stockOut('l', true);
          can_in_gripper[0] = 'l';
          can_in_gripper[1] = 'u';
          autoPlaceCan(drop_height, false);
        } else if (can_in_stock[1] == 'l') {
          BB(30, 400);
          delay(100);
          stockOut('r', true);
          can_in_gripper[0] = 'u';
          can_in_gripper[1] = 'l';
          autoPlaceCan(drop_height, false);
        }
      } else if (i == 1) {
        if (can_in_stock[0] == 'c') {
          BB(30, 400);
          delay(100);
          stockOut('l', true);
          can_in_gripper[0] = 'c';
          can_in_gripper[1] = 'u';
          delay(200);
          setCan();
          autoPlaceCan(drop_height, false);
        } else if (can_in_stock[1] == 'c') {
          BB(30, 400);
          delay(100);
          stockOut('r', true);
          can_in_gripper[0] = 'u';
          can_in_gripper[1] = 'c';
          delay(200);
          setCan();
          autoPlaceCan(drop_height, false);
        }
      } else if (i == 2) {
        if (can_in_stock[0] == 'r') {
          BB(30, 400);
          delay(100);
          stockOut('l', true);
          can_in_gripper[0] = 'r';
          can_in_gripper[1] = 'u';
          autoPlaceCan(drop_height, false);
        } else if (can_in_stock[1] == 'r') {
          BB(30, 400);
          delay(100);
          stockOut('r', true);
          can_in_gripper[0] = 'u';
          can_in_gripper[1] = 'r';
          autoPlaceCan(drop_height, false);
        }
      }
    }
  }
  BB(30, 400);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  lift(3);
}