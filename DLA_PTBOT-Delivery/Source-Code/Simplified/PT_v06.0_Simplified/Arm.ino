#define chanal_Swing_Left 0
#define chanal_Swing_Right 1
#define chanal_Gripper_Left 2
#define chanal_Gripper_Right 3

int Swing_Left = 45;
int Swing_Right = 45;

int Open_Left = 100;
int Open_Right = 100;

int Close_Left = 145;
int Close_Right = 145;

int swing_current_degree[] = { 0, 0 };

ESP32Encoder encoder;

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
    vTaskDelay(10 / portTICK_PERIOD_MS); 
    long current_count = encoder.getCount() / 2;
    error = current_count - lift_target;

    if (abs(current_count - last_encoder_count) > 5) {
      last_change_time = millis();
      last_encoder_count = current_count;
      stopped_due_to_timeout = false;
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

void moveToCan(float distance) {
  vTaskResume(sonarTaskHandle);
  sonar_enable = 1;
  vTaskDelay(10 / portTICK_PERIOD_MS);
  unsigned long int timer = millis();
  while (readSonar() > distance || millis() - timer <= 500) {
    vTaskDelay(10 / portTICK_PERIOD_MS); 
    FF(15);
  }
  FF(10, 200);
  motorStop();
  vTaskSuspend(sonarTaskHandle);
  sonar_enable = 0;
}

void moveToCan0(float distance) {
  unsigned long int timer = millis();
  int current_distance = 0;
  while ((current_distance != -1 && current_distance > distance) || millis() - timer <= 500) {
    vTaskDelay(10 / portTICK_PERIOD_MS); 
    current_distance = readCanDistance();
    FF(15);
  }
  FF(10, 250);
  motorStop();
}

void PickCan(int pick_height, int B_Speed, int B_delay) {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) moveToCan(pick_can_distance);
  else moveToCan0(can_distance);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  lift(pick_height - 1);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  lift(pick_height + 4);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  BB(20, 500);
  StableCAN();
  BB(B_Speed, B_delay);
}

void placeCan(int drop_height, int distance, char from_gripper, char drop_point, int B_Speed, int B_delay) {
  lift(drop_height + 2);
  vTaskDelay((250 + drop_height * 70) / portTICK_PERIOD_MS);
  motorStop();
  if (from_gripper == 'L' && drop_point == 'L') {
    swingGripper('l', Swing_Left + 10);
    swingGripper('r', Swing_Right + 60);
  } else if (from_gripper == 'L' && drop_point == 'C') {
    swingGripper('l', Swing_Left - 20);
    swingGripper('r', Swing_Right + 60);
  } else if (from_gripper == 'R' && drop_point == 'R') {
    swingGripper('l', Swing_Left + 60);
    swingGripper('r', Swing_Right + 10);
  } else if (from_gripper == 'R' && drop_point == 'C') {
    swingGripper('l', Swing_Left + 60);
    swingGripper('r', Swing_Right - 20);
  } else if (from_gripper == 'A' && drop_point == 'A') {
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
  } else if (from_gripper == 'L' && drop_point == 'A') {
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right + 60);
  } else if (from_gripper == 'R' && drop_point == 'A') {
    servoWrite(chanal_Swing_Left, Swing_Left + 60);
    servoWrite(chanal_Swing_Right, Swing_Right);
  } else {
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
  if (drop_height != 0) moveToCan(Place_can_distance);
  else moveToCan0(can_distance);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  lift(drop_height - 1);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  dropCan(from_gripper);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  BB(20, 500);
  BalanceArm('S');
  lift(0);
  vTaskDelay((250 + drop_height * 70) / portTICK_PERIOD_MS);
  lift(2);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  BB(B_Speed, B_delay);
}

void dropCan(char gripper) {
  if (gripper == 'L') {
    servoWrite(chanal_Gripper_Left, Close_Left - 10);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    servoWrite(chanal_Gripper_Left, Open_Left);
  } else if (gripper == 'R') {
    servoWrite(chanal_Gripper_Right, Close_Right - 10);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    servoWrite(chanal_Gripper_Right, Open_Right);
  } else if (gripper == 'A') {
    servoWrite(chanal_Gripper_Left, Close_Left - 10);
    servoWrite(chanal_Gripper_Right, Close_Right - 10);
    vTaskDelay(250 / portTICK_PERIOD_MS);
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
    servoWrite(chanal_Swing_Left, Swing_Left + 100);
    servoWrite(chanal_Swing_Right, Swing_Right - 30);
  } else if (select == 'R') {
    servoWrite(chanal_Gripper_Left, Close_Left);
    servoWrite(chanal_Gripper_Right, Close_Right);
    servoWrite(chanal_Swing_Right, Swing_Right + 100);
    servoWrite(chanal_Swing_Left, Swing_Left - 30);
  } else if (select == 'S') {
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
  } else if (select == 'W') {
    servoWrite(chanal_Gripper_Left, Close_Left);
    servoWrite(chanal_Gripper_Right, Close_Right);
    servoWrite(chanal_Swing_Left, Swing_Left + 100);
    servoWrite(chanal_Swing_Right, Swing_Right + 100);
  }
  vTaskDelay(250 / portTICK_PERIOD_MS);
}

void StableCAN() {
  lift(0);
  BB(10, 300);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  servoWrite(chanal_Gripper_Left, Close_Left - 15);
  servoWrite(chanal_Gripper_Right, Close_Right - 15);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  FF(10, 300);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  lift(2);
  vTaskDelay(250 / portTICK_PERIOD_MS);
}