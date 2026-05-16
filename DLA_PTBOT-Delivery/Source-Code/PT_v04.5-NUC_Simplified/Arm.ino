#define chanal_Swing_Left 0
#define chanal_Swing_Right 1
#define chanal_Gripper_Left 2
#define chanal_Gripper_Right 3

int Swing_Left = 58; // S0 เพิ่ม ง้างออก
int Swing_Right = 58; //S1 ลด หุบเข้า

int Open_Left = 110; // S2 เพิ่ม หุบเข้า
int Open_Right = 90; // S3 ลด หุบออก

int Close_Left = 144; // S2 เพิ่ม หุบเข้า
int Close_Right = 124; // S3 ลด หุบออก

int switch_degree = 20;
int switch_flag = 0;
int lift_target = 0;
int swing_current_degree[] = { 0, 0 };

ESP32Encoder encoder;

void TS(){
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);

  delay(2000);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
}

void switchGripperLoop(void *pvParameters) {
  while (1) {
    if (switch_flag == -1) {
      servoWrite(chanal_Gripper_Left, Open_Left);
      servoWrite(chanal_Swing_Right, Swing_Right + 35);
      delay(250);
      servoWrite(chanal_Swing_Left, Swing_Left - 25);
      servoWrite(chanal_Swing_Right, Swing_Right - 25);
      delay(250);
      servoWrite(chanal_Gripper_Left, Close_Left);
      delay(250);
      servoWrite(chanal_Gripper_Right, Open_Right);
      delay(250);
      swing_current_degree[0] = Swing_Left + (switch_degree - 10);
      swing_current_degree[1] = Swing_Right + 65;
      servoWrite(chanal_Swing_Left, swing_current_degree[0]);
      servoWrite(chanal_Swing_Right, swing_current_degree[1]);
      switch_flag = 0;
    } else if (switch_flag == 1) {
      servoWrite(chanal_Gripper_Right, Open_Right);
      servoWrite(chanal_Swing_Left, Swing_Left + 35);
      delay(250);
      servoWrite(chanal_Swing_Left, Swing_Left - 25);
      servoWrite(chanal_Swing_Right, Swing_Right - 25);
      delay(250);
      servoWrite(chanal_Gripper_Left, Close_Left);
      delay(250);
      servoWrite(chanal_Gripper_Left, 0);
      delay(250);
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

    if (abs(abs(current_count) - abs(last_encoder_count)) > 5) {
      last_change_time = millis();
      last_encoder_count = current_count;
    }

    if (lift_target != last_lift_target) {
      stopped_due_to_timeout = false;
      last_change_time = millis();
      integral = 0;
      previous_error = 0;
      last_lift_target = lift_target;
    }

    if (!stopped_due_to_timeout && millis() - last_change_time > timeout_ms) {
      motorWrite(3, 0);
      stopped_due_to_timeout = true;
    }

    if (stopped_due_to_timeout) {
      vTaskDelay(10 / portTICK_PERIOD_MS);
      continue;
    }

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

void moveToCan(int distance) {
  vTaskResume(sonarTaskHandle);
  sonar_enable = 1;
  delay(10);
  unsigned long int timer = millis();
  while (readSonar() > distance || millis() - timer <= 500) FF(15);
  FF(10, 200);
  motorStop();
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
  motorStop();
}

void placeCan(int drop_height, int distance, char from_gripper, char drop_point, int B_Speed, int B_delay) {
  bool switch_can = 0;
  lift(drop_height + 2);
  delay(drop_height * 75);
  motorStop();
  if (from_gripper == 'R') from_gripper = 'r';
  else if (from_gripper == 'L') from_gripper = 'l';
  else if (from_gripper == 'C') from_gripper = 'c';
  else if (from_gripper == 'A') from_gripper = 'a';

  if (drop_point == 'R') drop_point = 'r';
  else if (drop_point == 'L') drop_point = 'l';
  else if (drop_point == 'C') drop_point = 'c';
  else if (drop_point == 'A') drop_point = 'a';
  if (from_gripper == 'l' && drop_point == 'l') {
    swingGripper('l', Swing_Left + 10);
    swingGripper('r', Swing_Right + 60);
  } else if (from_gripper == 'l' && drop_point == 'c') {
    swingGripper('l', Swing_Left - 20);
    swingGripper('r', Swing_Right + 60);
  } else if (from_gripper == 'r' && drop_point == 'r') {
    swingGripper('l', Swing_Left + 60);
    swingGripper('r', Swing_Right + 10);
  } else if (from_gripper == 'r' && drop_point == 'c') {
    swingGripper('l', Swing_Left + 60);
    swingGripper('r', Swing_Right - 20);
  } else if (from_gripper == 'a' && drop_point == 'a') {
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
  } else if (from_gripper == 'l' && drop_point == 'a') {
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right + 60);
  } else if (from_gripper == 'r' && drop_point == 'a') {
    servoWrite(chanal_Swing_Left, Swing_Left + 60);
    servoWrite(chanal_Swing_Right, Swing_Right);
  } else {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    switchGripper(from_gripper, drop_point);
    switch_can = 1;
  }
  if (drop_height != 0) moveToCan(Place_can_distance);
  else moveToCan0(can_distance);
  delay(250);
  lift(drop_height - 2);
  delay(500);
  dropCan(from_gripper);
  delay(500);
  BB(20, 500);
  BalanceArm('S');
  lift(0);
  delay(drop_height * 75);
  lift(2);
  delay(250);
  BB(B_Speed, B_delay);
  vTaskSuspend(switchGripperTaskHandle);
}

void dropCan(char gripper) {
  if (gripper == 'l') {
    servoWrite(chanal_Gripper_Left, Close_Left - 10);
    delay(250);
    servoWrite(chanal_Gripper_Left, Open_Left);
  } else if (gripper == 'r') {
    servoWrite(chanal_Gripper_Right, Close_Right - 10);
    delay(250);
    servoWrite(chanal_Gripper_Right, Open_Right);
  } else if (gripper == 'a') {
    servoWrite(chanal_Gripper_Left, Close_Left - 10);
    servoWrite(chanal_Gripper_Right, Close_Right - 10);
    delay(250);
    servoWrite(chanal_Gripper_Left, Open_Left);
    servoWrite(chanal_Gripper_Right, Open_Right);
  }
}

void BalanceArm(char select) {
  if (select == 'C') {
    servoWrite(chanal_Gripper_Left, Close_Left);
    servoWrite(chanal_Gripper_Right, Close_Right);
    servoWrite(chanal_Swing_Left, Swing_Left - 30);
    servoWrite(chanal_Swing_Right, Swing_Right - 30);
  } else if (select == 'O') {
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
    servoWrite(chanal_Gripper_Left, Open_Left);
    servoWrite(chanal_Gripper_Right, Open_Right);
  } else if (select == 'L') {
    servoWrite(chanal_Gripper_Left, Close_Left);
    servoWrite(chanal_Gripper_Right, Close_Right);
    servoWrite(chanal_Swing_Left, Swing_Left + 90);
    servoWrite(chanal_Swing_Right, Swing_Right - 30);
  } else if (select == 'R') {
    servoWrite(chanal_Gripper_Left, Close_Left);
    servoWrite(chanal_Gripper_Right, Close_Right);
    servoWrite(chanal_Swing_Right, Swing_Right + 90);
    servoWrite(chanal_Swing_Left, Swing_Left - 30);
  } else if (select == 'S') {
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
  } else if (select == 'W') {
    servoWrite(chanal_Gripper_Left, Close_Left);
    servoWrite(chanal_Gripper_Right, Close_Right);
    servoWrite(chanal_Swing_Left, Swing_Left + 90);
    servoWrite(chanal_Swing_Right, Swing_Right + 90);
  }
  delay(250);
}

void PickCan(int pick_height, int B_Speed, int B_delay) {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) moveToCan(pick_can_distance);
  else moveToCan0(can_distance);
  delay(250);
  lift(pick_height - 1);
  delay(250);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(250);
  lift(pick_height + 4);
  delay(500);
  BB(20, 500);
  StableCAN();
  BB(B_Speed, B_delay);
}

void StableCAN() {
  lift(0);
  BB(10, 300);
  delay(250);
  servoWrite(chanal_Gripper_Left, Close_Left - 15);
  servoWrite(chanal_Gripper_Right, Close_Right - 15);
  delay(500);
  FF(10, 300);
  delay(250);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(250);
  lift(2);
  delay(250);
}