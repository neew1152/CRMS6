void SwingGripper(char gripper, int degree) {
  if (gripper == 'l') {
    Swing_Current_Degree[0] = degree;
    servoWrite(Chanal_Swing_Left, Swing_Current_Degree[0]);
  } else if (gripper == 'r') {
    Swing_Current_Degree[1] = degree;
    servoWrite(Chanal_Swing_Right, Swing_Current_Degree[1]);
  }
}

void LiftLoop(void *pvParameters) {
  const int CLK = 39;
  const int DT = 36;
  float error, previous_error = 0, integral = 0, derivative;
  float p_value, i_value, d_value, motor_speed;
  float Kp = 3.0, Ki = 0.001, Kd = 0.05;

  Encoder.attachHalfQuad(DT, CLK);
  Encoder.setCount(0);

  long last_Encoder_count = 0;
  unsigned long last_change_time = millis();
  const unsigned long timeout_ms = 500;

  int last_Lift_Target = Lift_Target;
  bool stopped_due_to_timeout = false;

  while (1) {
    long current_count = Encoder.getCount() / 2;
    error = current_count - Lift_Target;

    if (abs(current_count - last_Encoder_count) > 5) {
      last_change_time = millis();
      last_Encoder_count = current_count;
      stopped_due_to_timeout = false;
    }

    if (Lift_Target != last_Lift_Target) {
      stopped_due_to_timeout = false;
      last_change_time = millis();
      integral = 0;
      previous_error = 0;
      last_Lift_Target = Lift_Target;
    }

    if (!stopped_due_to_timeout && millis() - last_change_time > timeout_ms && abs(error) >= 5) {
      if (xSemaphoreTakeRecursive(i2cMutex, portMAX_DELAY) == pdTRUE) {
        motorWrite(3, 0);
        xSemaphoreGiveRecursive(i2cMutex);
      }
      stopped_due_to_timeout = true;
    }

    if (stopped_due_to_timeout) {
      continue;
    }

    p_value = Kp * error;
    integral += error;
    i_value = Ki * integral;
    derivative = error - previous_error;
    d_value = Kd * derivative;
    motor_speed = p_value + i_value + d_value;

    motor_speed = constrain(motor_speed, -100, 100);

    if (abs(error) >= 5) {
      if (xSemaphoreTakeRecursive(i2cMutex, portMAX_DELAY) == pdTRUE) {
        motorWrite(3, motor_speed);
        xSemaphoreGiveRecursive(i2cMutex);
      }
    } else {
      if (xSemaphoreTakeRecursive(i2cMutex, portMAX_DELAY) == pdTRUE) {
        motorWrite(3, 0);
        xSemaphoreGiveRecursive(i2cMutex);
      }
    }

    previous_error = error;
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void Lift(int position) {
  if (position < 0) position = 0;
  Lift_Target = position * 28;
  if (Lift_Target > 900) Lift_Target = 900;
}

void PickCan(int pick_height, int B_Speed, int B_delay) {
  servoWrite(Chanal_Swing_Left, Swing_Left);
  servoWrite(Chanal_Swing_Right, Swing_Right);
  servoWrite(Chanal_Gripper_Left, Open_Left);
  servoWrite(Chanal_Gripper_Right, Open_Right);
  Lift(pick_height);
  if (pick_height != 0) FFUltrasonic(Ultrasonic_Pick_Distance);
  else FFLaser(Laser_Distance);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  servoWrite(Chanal_Gripper_Left, Close_Left);
  servoWrite(Chanal_Gripper_Right, Close_Right);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  Lift(pick_height + 4);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  BB(25, 500);
  StableCAN();
  BB(B_Speed, B_delay);
}

void DropCan(int Drop_height, char from_gripper, char Drop_point, int B_Speed, int B_delay) {
  Lift(Drop_height + 2);
  int delay_time = 250 + (Drop_height * 70);
  if (delay_time < 0) delay_time = 0;
  vTaskDelay(delay_time / portTICK_PERIOD_MS);
  motorStop();
  if (from_gripper == 'L' && Drop_point == 'L') {
    SwingGripper('l', Swing_Left + 10);
    SwingGripper('r', Swing_Right + 60);
  } else if (from_gripper == 'L' && Drop_point == 'C') {
    SwingGripper('l', Swing_Left - 20);
    SwingGripper('r', Swing_Right + 60);
  } else if (from_gripper == 'R' && Drop_point == 'R') {
    SwingGripper('l', Swing_Left + 60);
    SwingGripper('r', Swing_Right + 10);
  } else if (from_gripper == 'R' && Drop_point == 'C') {
    SwingGripper('l', Swing_Left + 60);
    SwingGripper('r', Swing_Right - 20);
  } else if (from_gripper == 'A' && Drop_point == 'A') {
    servoWrite(Chanal_Swing_Left, Swing_Left);
    servoWrite(Chanal_Swing_Right, Swing_Right);
  } else if (from_gripper == 'L' && Drop_point == 'A') {
    servoWrite(Chanal_Swing_Left, Swing_Left);
    servoWrite(Chanal_Swing_Right, Swing_Right + 60);
  } else if (from_gripper == 'R' && Drop_point == 'A') {
    servoWrite(Chanal_Swing_Left, Swing_Left + 60);
    servoWrite(Chanal_Swing_Right, Swing_Right);
  }
  if (Drop_height != 0) FFUltrasonic(Ultrasonic_Drop_Distance);
  else FFLaser(Laser_Distance);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  Lift(Drop_height);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  DropPosition(from_gripper);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  BB(25, 500);
  BalanceArm('S');
  Lift(0);
  vTaskDelay(delay_time / portTICK_PERIOD_MS);
  Lift(Lift_Default);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  BB(B_Speed, B_delay);
}

void DropPosition(char gripper) {
  if (gripper == 'L') {
    servoWrite(Chanal_Gripper_Left, Close_Left - 10);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    servoWrite(Chanal_Gripper_Left, Open_Left);
  } else if (gripper == 'R') {
    servoWrite(Chanal_Gripper_Right, Close_Right - 10);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    servoWrite(Chanal_Gripper_Right, Open_Right);
  } else if (gripper == 'A') {
    servoWrite(Chanal_Gripper_Left, Close_Left - 10);
    servoWrite(Chanal_Gripper_Right, Close_Right - 10);
    vTaskDelay(250 / portTICK_PERIOD_MS);
    servoWrite(Chanal_Gripper_Left, Open_Left);
    servoWrite(Chanal_Gripper_Right, Open_Right);
  }
}

void BalanceArm(char select) {
  if (select == 'C') {
    servoWrite(Chanal_Gripper_Left, Close_Left);
    servoWrite(Chanal_Gripper_Right, Close_Right);
    servoWrite(Chanal_Swing_Left, Swing_Left - 30);
    servoWrite(Chanal_Swing_Right, Swing_Right - 30);
  } else if (select == 'O') {
    servoWrite(Chanal_Swing_Left, Swing_Left);
    servoWrite(Chanal_Swing_Right, Swing_Right);
    servoWrite(Chanal_Gripper_Left, Open_Left);
    servoWrite(Chanal_Gripper_Right, Open_Right);
  } else if (select == 'L') {
    servoWrite(Chanal_Gripper_Left, Close_Left);
    servoWrite(Chanal_Gripper_Right, Close_Right);
    servoWrite(Chanal_Swing_Left, Swing_Left + 100);
    servoWrite(Chanal_Swing_Right, Swing_Right - 30);
  } else if (select == 'R') {
    servoWrite(Chanal_Gripper_Left, Close_Left);
    servoWrite(Chanal_Gripper_Right, Close_Right);
    servoWrite(Chanal_Swing_Right, Swing_Right + 100);
    servoWrite(Chanal_Swing_Left, Swing_Left - 30);
  } else if (select == 'S') {
    servoWrite(Chanal_Swing_Left, Swing_Left);
    servoWrite(Chanal_Swing_Right, Swing_Right);
  } else if (select == 'W') {
    servoWrite(Chanal_Gripper_Left, Close_Left);
    servoWrite(Chanal_Gripper_Right, Close_Right);
    servoWrite(Chanal_Swing_Left, Swing_Left + 100);
    servoWrite(Chanal_Swing_Right, Swing_Right + 100);
  }
  vTaskDelay(250 / portTICK_PERIOD_MS);
}

void StableCAN() {
  Lift(0);
  BB(10, 300);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  servoWrite(Chanal_Gripper_Left, Close_Left - 15);
  servoWrite(Chanal_Gripper_Right, Close_Right - 15);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  FF(10, 300);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  servoWrite(Chanal_Gripper_Left, Close_Left);
  servoWrite(Chanal_Gripper_Right, Close_Right);
  vTaskDelay(250 / portTICK_PERIOD_MS);
  Lift(Lift_Default);
  vTaskDelay(250 / portTICK_PERIOD_MS);
}