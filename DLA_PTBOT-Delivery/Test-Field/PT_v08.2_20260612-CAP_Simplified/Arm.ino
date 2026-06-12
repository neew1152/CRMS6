void BalanceArm(char position) {
  switch (position) {
    case 'C':
      servoWrite(Channel_Gripper_Left, Close_Left);
      servoWrite(Channel_Gripper_Right, Close_Right);
      servoWrite(Channel_Swing_Left, Swing_Left - 15);
      servoWrite(Channel_Swing_Right, Swing_Right - 15);
      break;

    case 'O':
      servoWrite(Channel_Swing_Left, Swing_Left);
      servoWrite(Channel_Swing_Right, Swing_Right);
      servoWrite(Channel_Gripper_Left, Open_Left);
      servoWrite(Channel_Gripper_Right, Open_Right);
      break;

    case 'L':
      servoWrite(Channel_Gripper_Left, Close_Left);
      servoWrite(Channel_Gripper_Right, Close_Right);
      servoWrite(Channel_Swing_Left, Swing_Left + 100);
      servoWrite(Channel_Swing_Right, Swing_Right - 30);
      break;

    case 'R':
      servoWrite(Channel_Gripper_Left, Close_Left);
      servoWrite(Channel_Gripper_Right, Close_Right);
      servoWrite(Channel_Swing_Right, Swing_Right + 100);
      servoWrite(Channel_Swing_Left, Swing_Left - 30);
      break;

    case 'S':
      servoWrite(Channel_Swing_Left, Swing_Left);
      servoWrite(Channel_Swing_Right, Swing_Right);
      break;

    case 'W':
      servoWrite(Channel_Gripper_Left, Close_Left);
      servoWrite(Channel_Gripper_Right, Close_Right);
      servoWrite(Channel_Swing_Left, Swing_Left + 100);
      servoWrite(Channel_Swing_Right, Swing_Right + 100);
      break;
  }
  vTaskDelay(Delay_LOW / portTICK_PERIOD_MS);
}

void FFOBJ(int speed, int obj_height) {
  if (obj_height != 0) FFUltrasonic(speed, Ultrasonic_Pick_Distance);
  else FFToF(speed, ToF_Distance);
  vTaskDelay(Delay_LOW / portTICK_PERIOD_MS);
}

void FFOBJ(int speed, int obj_height, char gripper) {
  switch (gripper) {
    case 'L':
      SwingGripper('r', Swing_Right + 60);
      break;

    case 'R':
      SwingGripper('l', Swing_Left + 60);
      break;
  }
  FFOBJ(speed, obj_height);
}

void Lift(int position) {
  if (position < 0) position = 0;
  Lift_Target = position * 28;
  if (Lift_Target > 900) Lift_Target = 900;
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
    vTaskDelay(Delay_HW * 5 / portTICK_PERIOD_MS);
  }
}

void DropPosition(char gripper) {
  switch (gripper) {
    case 'L':
      servoWrite(Channel_Gripper_Left, Close_Left - 10);
      vTaskDelay(Default_Delay / portTICK_PERIOD_MS);
      servoWrite(Channel_Gripper_Left, Open_Left);
      break;

    case 'R':
      servoWrite(Channel_Gripper_Right, Close_Right - 10);
      vTaskDelay(Default_Delay / portTICK_PERIOD_MS);
      servoWrite(Channel_Gripper_Right, Open_Right);
      break;

    case 'A':
      servoWrite(Channel_Gripper_Left, Close_Left - 10);
      servoWrite(Channel_Gripper_Right, Close_Right - 10);
      vTaskDelay(Default_Delay / portTICK_PERIOD_MS);
      servoWrite(Channel_Gripper_Left, Open_Left);
      servoWrite(Channel_Gripper_Right, Open_Right);
      break;
  }
  vTaskDelay(Delay_HIGH / portTICK_PERIOD_MS);
}

void SwingGripper(char gripper, int degree) {
  switch (gripper) {
    case 'l':
      Swing_Current_Degree[0] = degree;
      servoWrite(Channel_Swing_Left, Swing_Current_Degree[0]);
      break;

    case 'r':
      Swing_Current_Degree[1] = degree;
      servoWrite(Channel_Swing_Right, Swing_Current_Degree[1]);
      break;
  }
}

void PickCan(int pick_height, int BB_speed, int BB_delay) {
  PickCan(pick_height, 'A', BB_speed, BB_delay);
}

void PickCan(int pick_height, char gripper, int BB_speed, int BB_delay) {
  BalanceArm('O');
  Lift(pick_height);
  FFOBJ(Speed_LOW, pick_height, gripper);
  switch (gripper) {
    case 'L':
      servoWrite(Channel_Gripper_Left, Close_Left);
      break;

    case 'R':
      servoWrite(Channel_Gripper_Right, Close_Right);
      break;

    default:
      servoWrite(Channel_Gripper_Left, Close_Left);
      servoWrite(Channel_Gripper_Right, Close_Right);
      break;
  }
  vTaskDelay(Delay_LOW / portTICK_PERIOD_MS);
  Lift(pick_height + 4);
  vTaskDelay(Default_Delay / portTICK_PERIOD_MS);
  BB(Speed_MID, Time_Withdraw);
  StableOBJ();
  BB(BB_speed, BB_delay);
}

void DropCan(int drop_height, char gripper, char drop_point, int BB_speed, int BB_delay) {
  int delay_time = Default_Delay + (drop_height * 25);
  if (delay_time < 0) delay_time = 0;
  Lift(drop_height + 2);
  vTaskDelay(delay_time / portTICK_PERIOD_MS);
  switch (gripper) {
    case 'L':
      switch (drop_point) {
        case 'L':
          SwingGripper('l', Swing_Left + 10);
          SwingGripper('r', Swing_Right + 60);
          break;
        case 'C':
          SwingGripper('l', Swing_Left - 20);
          SwingGripper('r', Swing_Right + 60);
          break;
        case 'A':
          servoWrite(Channel_Swing_Left, Swing_Left);
          servoWrite(Channel_Swing_Right, Swing_Right + 60);
          break;
      }
      break;

    case 'R':
      switch (drop_point) {
        case 'R':
          SwingGripper('l', Swing_Left + 60);
          SwingGripper('r', Swing_Right + 10);
          break;
        case 'C':
          SwingGripper('l', Swing_Left + 60);
          SwingGripper('r', Swing_Right - 20);
          break;
        case 'A':
          servoWrite(Channel_Swing_Left, Swing_Left + 60);
          servoWrite(Channel_Swing_Right, Swing_Right);
          break;
      }
      break;

    case 'A':
      switch (drop_point) {
        case 'A':
          BalanceArm('S');
          break;
      }
      break;
  }

  FFOBJ(Speed_MID / 2, drop_height);
  Lift(drop_height);
  vTaskDelay(Delay_LOW / portTICK_PERIOD_MS);
  DropPosition(gripper);
  vTaskDelay(Default_Delay / portTICK_PERIOD_MS);
  BB(Speed_MID, Time_Withdraw);
  BalanceArm('S');
  Lift(Default_Lift);
  vTaskDelay(delay_time / portTICK_PERIOD_MS);
  BB(BB_speed, BB_delay);
}

void StableOBJ() {
  BalanceArm('S');
  Lift(0);
  BB(Speed_LOW, Time_Withdraw / 2);
  vTaskDelay(Default_Delay / portTICK_PERIOD_MS);
  servoWrite(Channel_Gripper_Left, Close_Left - 15);
  servoWrite(Channel_Gripper_Right, Close_Right - 15);
  vTaskDelay(Default_Delay / portTICK_PERIOD_MS);
  FF(Speed_LOW, Time_Withdraw / 2);
  servoWrite(Channel_Gripper_Left, Close_Left);
  servoWrite(Channel_Gripper_Right, Close_Right);
  vTaskDelay(Delay_LOW / portTICK_PERIOD_MS);
  Lift(Default_Lift);
  vTaskDelay(Delay_LOW / portTICK_PERIOD_MS);
}