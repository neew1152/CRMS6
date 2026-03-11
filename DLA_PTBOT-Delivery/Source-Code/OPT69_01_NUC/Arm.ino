#define chanal_Swing_Left 0
#define chanal_Swing_Right 1
#define chanal_Gripper_Left 2
#define chanal_Gripper_Right 3

int Swing_Left = 86;   // SO
int Swing_Right = 82;  // S1

int Open_Left = 116;   // S2
int Close_Left = 155;  // S2

int Open_Right = 120;   // S3
int Close_Right = 154;  // S3
////////////////////////////////////////////////////
int switch_degree = 30;

int switch_flag = 0;
int lift_target = 0;
int swing_current_degree[] = { 0, 0 };
int can_in_gripper[] = { 0, 0 };

void setupServo() {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
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

void switchGripperLoop(void *pvParameters) {
  while (1) {
    if (switch_flag == -1) {
      servoWrite(chanal_Gripper_Left, Open_Left);
      servoWrite(chanal_Swing_Right, Swing_Right + 45);
      delay(200);
      servoWrite(chanal_Swing_Left, Swing_Left - 45);
      servoWrite(chanal_Swing_Right, Swing_Right - 55);
      delay(200);
      servoCloseLeft();
      delay(150);
      servoWrite(chanal_Gripper_Right, Open_Right);
      delay(150);
      swing_current_degree[0] = Swing_Left + switch_degree;
      swing_current_degree[1] = Swing_Right + 50;
      servoWrite(chanal_Swing_Left, swing_current_degree[0]);
      servoWrite(chanal_Swing_Right, swing_current_degree[1]);
      switch_flag = 0;
    } else if (switch_flag == 1) {
      servoWrite(chanal_Gripper_Right, Open_Right);
      servoWrite(chanal_Swing_Left, Swing_Left + 45);
      delay(200);
      servoWrite(chanal_Swing_Left, Swing_Left - 55);
      servoWrite(chanal_Swing_Right, Swing_Right - 45);
      delay(200);
      servoCloseRight();
      delay(150);
      servoWrite(chanal_Gripper_Left, Open_Left);
      delay(150);
      swing_current_degree[0] = Swing_Left + 50;
      swing_current_degree[1] = Swing_Right + switch_degree;
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
  ESP32Encoder encoder;
  encoder.attachHalfQuad(DT, CLK);
  encoder.setCount(0);
  while (1) {
    error = (encoder.getCount() / 2) - lift_target;
    p_value = Kp * error;
    integral += error;
    i_value = Ki * integral;
    derivative = error - previous_error;
    d_value = Kd * derivative;
    motor_speed = p_value + i_value + d_value;
    motor_speed = constrain(motor_speed, -255, 40);
    if (abs(error) >= 5) motorWrite(3, motor_speed);
    else motorStop();
    previous_error = error;
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void lift(int position) {
  if (position > 17) position = 17;
  lift_target = position * 30;
  if (lift_target > 900) lift_target = 900;
}

void moveToCan(float distance) {
  vTaskResume(sonarTaskHandle);
  delay(10);
  unsigned long int timer = millis();
  while (readSonar() > distance || millis() - timer <= 500) FF(10);
  vTaskSuspend(sonarTaskHandle);
  FF(10, 300);
}

void moveToCan0(int distance) {
  unsigned long int timer = millis();
  while (readCanDistance() > distance || millis() - timer <= 500) FF(10);
  FF(10, 275);
  motorStop();
}

void shakeGripper(char gripper) {
  int increment = 1;
  int delayTime = 5;
  int swingRange = 20;
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
  if (gripper == 'l') {
    servoWrite(chanal_Gripper_Left, Close_Left - 10);
    shakeGripper('l');
    delay(200);
    servoOpenLeft();
  } else if (gripper == 'r') {
    servoWrite(chanal_Gripper_Right, Close_Right - 10);
    shakeGripper('r');
    delay(200);
    servoOpenRight();
  } else if (gripper == 'a') {
    servoWrite(chanal_Gripper_Left, Close_Left - 10);
    servoWrite(chanal_Gripper_Right, Close_Right - 10);
    shakeGripper('a');
    delay(200);
    servoOpenLeft();
    servoOpenRight();
  }
}

void dropCan_NoShake(char gripper) {
  if (gripper == 'l') {
    servoWrite(chanal_Gripper_Left, Close_Left - 10);
    delay(200);
    servoOpenLeft();
  } else if (gripper == 'r') {
    servoWrite(chanal_Gripper_Right, Close_Right - 10);
    delay(200);
    servoOpenRight();
  } else if (gripper == 'a') {
    servoWrite(chanal_Gripper_Left, Close_Left - 10);
    servoWrite(chanal_Gripper_Right, Close_Right - 10);
    delay(200);
    servoOpenLeft();
    servoOpenRight();
  }
}

void pickCan_Old(int pick_height, bool switch_lr) {
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) moveToCan(4);
  else moveToCan0(0);
  delay(100);
  servoCloseLeft();
  servoCloseRight();
  delay(200);
  lift(pick_height + 2);
  delay(200);
  if (switch_lr == 1) {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    swingGripper('l', Swing_Left - (switch_degree + 13));
    delay(200);
    servoWrite(chanal_Gripper_Left, Open_Left);
    delay(200);
    lift(pick_height + 12);  //--Adjust hight (above cans)
    delay(500);
    switchGripper('r', 'l');
    delay(500);
    servoWrite(chanal_Gripper_Right, Open_Right);
    swingGripper('r', Swing_Right - (switch_degree + 10));
    lift(pick_height + 2);
    delay(500);
    FF(20, 100);
    servoCloseRight();
    delay(200);
    vTaskSuspend(switchGripperTaskHandle);
  }
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
}

void Switch_left_to_right(int stop) {
  servoWrite(chanal_Gripper_Right, Open_Right);
  delay(stop);
  servoWrite(chanal_Swing_Right, 40);
  delay(stop);
  servoWrite(chanal_Swing_Left, 40);
  delay(stop);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(stop);
  servoWrite(chanal_Gripper_Left, Open_Left);
  delay(stop);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(stop);
  servoWrite(chanal_Swing_Left, Swing_Left);
  delay(stop);
}
void Switch_right_to_left(int stop) {
  servoWrite(chanal_Gripper_Left, Open_Left);
  delay(stop);
  servoWrite(chanal_Swing_Left, 40);
  delay(stop);
  servoWrite(chanal_Swing_Right, 30);
  delay(stop);
  servoWrite(chanal_Gripper_Left, Close_Left);
  delay(stop);
  servoWrite(chanal_Gripper_Right, Open_Right);
  delay(stop);
  servoWrite(chanal_Swing_Left, Swing_Left);
  delay(stop);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(stop);
}

void Balance_Arm(char select) {
  if (select == 'C') {
    servoWrite(chanal_Gripper_Left, Close_Left);
    servoWrite(chanal_Gripper_Right, Close_Right);
    servoWrite(chanal_Swing_Left, 40);
    servoWrite(chanal_Swing_Right, 30);
  } else if (select == 'O') {
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
    servoWrite(chanal_Gripper_Left, Open_Left);
    servoWrite(chanal_Gripper_Right, Open_Right);
  }
}

void pickCan(int pick_height, bool switch_lr) {
  Balance_Arm('O');
  lift(pick_height);
  delay(150);
  if (pick_height != 0) moveToCan(5);
  else moveToCan0(38);
  delay(300); //100
  servoCloseLeft();
  servoCloseRight();
  delay(200);
  lift(pick_height + 3);
  delay(500);
  if (switch_lr == 1) {
    BB(30, 750);
    motorStop();
    delay(300);
    lift(0);
    delay(1000);
    servoWrite(chanal_Swing_Right, 40);
    delay(100);
    servoWrite(chanal_Gripper_Left, Open_Left);
    delay(100);
    servoWrite(chanal_Gripper_Left, Close_Left);
    delay(100);
    servoWrite(chanal_Gripper_Right, Open_Right);
    delay(100);
    lift(pick_height + 18);
    delay(1000);
    servoWrite(chanal_Swing_Left, 45);
    delay(100);
    servoWrite(chanal_Gripper_Right, Close_Right);
    delay(100);
    servoWrite(chanal_Gripper_Left, Open_Left);
    delay(100);
    servoWrite(chanal_Swing_Right, 140);
    delay(100);
    beep(100);
    lift(0); //ตอนลงมาจับเดิม
    delay(100);
    beep(100);
    delay(2000);
    servoWrite(chanal_Gripper_Left, Close_Left);
    delay(100);
    servoWrite(chanal_Swing_Left, Swing_Left);
    delay(100);
    servoWrite(chanal_Swing_Right, Swing_Right);
    delay(100);
    motorStop();
    delay(100);
    // lift(4);

  } else if (switch_lr == 0) {
    BB(30, 800);
    motorStop();
    delay(100);
  }
  lift(2);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  motorStop();
  delay(1000);
}


void placeCan1(int drop_height, int distance, char from_gripper, char drop_point) {
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  lift(drop_height + 3);
  if (from_gripper == 'l' && drop_point == 'l') {
    swingGripper('l', Swing_Left + switch_degree);
    swingGripper('r', Swing_Right + 90);
  } else if (from_gripper == 'l' && drop_point == 'c') {
    swingGripper('l', Swing_Left - (switch_degree + 10));
    swingGripper('r', Swing_Right + 90);
  } else if (from_gripper == 'r' && drop_point == 'r') {
    swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right + switch_degree);
  } else if (from_gripper == 'r' && drop_point == 'c') {
    swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right - (switch_degree + 10));
  } else {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    switchGripper(from_gripper, drop_point);
  }
  moveToCan(distance);
  lift(drop_height);
  delay(200);
  dropCan(from_gripper);
  delay(200);
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  vTaskSuspend(switchGripperTaskHandle);
}

void placeCan1_NoShake(int drop_height, int distance, char from_gripper) {
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  lift(drop_height + 3);
  delay(550);
  if (from_gripper == 'l') {
    servoWrite(chanal_Swing_Left, 65);
    delay(100);
    servoWrite(chanal_Swing_Right, 180);
    delay(100);
  } else if (from_gripper == 'r') {
    servoWrite(chanal_Swing_Right, 55);
    delay(100);
    servoWrite(chanal_Swing_Left, 180);
    delay(100);
  }
  moveToCan(distance);
  lift(drop_height);
  delay(200);
  dropCan_NoShake(from_gripper);
  delay(200);
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
}

void placeCan1_NoShake(int drop_height, int distance, char from_gripper, char drop_point) {
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  lift(drop_height + 3);
  delay(550);
  if (from_gripper == 'l' && drop_point == 'l') {
    swingGripper('l', Swing_Left + switch_degree);
    swingGripper('r', Swing_Right + 80);

  } else if (from_gripper == 'l' && drop_point == 'c') {
    swingGripper('l', Swing_Left - (switch_degree + 10));
    swingGripper('r', Swing_Right + 90);
  } else if (from_gripper == 'r' && drop_point == 'r') {
    swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right + switch_degree);
  } else if (from_gripper == 'r' && drop_point == 'c') {
    swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right - (switch_degree + 10));
  } else if (from_gripper == 'l' && drop_point == 's') {
    swingGripper('r', Swing_Right + 80);
  } else if (from_gripper == 'r' && drop_point == 's') {
    swingGripper('l', Swing_Left + 80);
  } else {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    switchGripper(from_gripper, drop_point);
  }
  moveToCan(distance);
  lift(drop_height);
  delay(200);
  dropCan_NoShake(from_gripper);
  delay(200);
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  vTaskSuspend(switchGripperTaskHandle);
}

void placeCan2(int drop_height, int distance, char left_gripper, char right_gripper) {
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  if (left_gripper == 'r' && right_gripper == 'l') {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    lift(0);
    delay(200);
    swingGripper('l', Swing_Left - (switch_degree + 13));
    delay(200);
    servoWrite(chanal_Gripper_Left, Open_Left);
    delay(200);
    lift(13);
    delay(1000);
    switchGripper('r', 'l');
    delay(1000);
    servoWrite(chanal_Gripper_Right, Open_Right);
    swingGripper('r', Swing_Right - (switch_degree + 10));
    lift(0);
    delay(1700);
    FF(20, 100);
    servoCloseRight();
    delay(200);
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
    lift(drop_height + 7);
    swingGripper('l', Swing_Left + switch_degree);
    swingGripper('r', Swing_Right + switch_degree);
    moveToCan(3);
    lift(drop_height + 4);
    delay(200);
    dropCan('a');
  } else {
    lift(drop_height + 3);
    if (left_gripper == 'l' && right_gripper == 'r') {
      swingGripper('l', Swing_Left + switch_degree);
      swingGripper('r', Swing_Right + switch_degree);
      moveToCan(distance);
      lift(drop_height);
      delay(200);
      dropCan('a');
    } else if (left_gripper == 'l' && right_gripper == 'c') {
      swingGripper('l', Swing_Left + switch_degree);
      swingGripper('r', Swing_Right - (switch_degree + 10));
      moveToCan(distance);
      lift(drop_height);
      delay(200);
      dropCan('a');
    } else if (left_gripper == 'c' && right_gripper == 'r') {
      swingGripper('l', Swing_Left - (switch_degree + 10));
      swingGripper('r', Swing_Right + switch_degree);
      moveToCan(distance);
      lift(drop_height);
      delay(200);
      dropCan('a');
    } else {
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      if (left_gripper == 'c') {
        swingGripper('l', Swing_Left - (switch_degree + 10));
        swingGripper('r', Swing_Right + 90);
        moveToCan(distance);
        lift(drop_height);
        delay(200);
        dropCan('l');
        delay(200);
        BB(30, 400);
        lift(drop_height + 3);
        switchGripper('r', 'l');
        delay(1000);
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('r', Swing_Right + 90);
        moveToCan(distance);
        dropCan('l');
      } else if (right_gripper == 'c') {
        swingGripper('r', Swing_Right - (switch_degree + 10));
        swingGripper('l', Swing_Left + 90);
        moveToCan(distance);
        lift(drop_height);
        delay(200);
        dropCan('r');
        delay(200);
        BB(30, 400);
        lift(drop_height + 3);
        switchGripper('l', 'r');
        delay(1000);
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('l', Swing_Left + 90);
        moveToCan(distance);
        dropCan('r');
      }
    }
  }
  delay(200);
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  vTaskSuspend(switchGripperTaskHandle);
}

void placeCan2_NoShake(int drop_height, int distance, char left_gripper, char right_gripper) {
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  if (left_gripper == 'r' && right_gripper == 'l') {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    lift(0);
    delay(200);
    swingGripper('l', Swing_Left - (switch_degree + 13));
    delay(200);
    servoWrite(chanal_Gripper_Left, Open_Left);
    delay(200);
    lift(13);
    delay(1000);
    switchGripper('r', 'l');
    delay(1000);
    servoWrite(chanal_Gripper_Right, Open_Right);
    swingGripper('r', Swing_Right - (switch_degree + 10));
    lift(0);
    delay(1700);
    FF(20, 100);
    servoCloseRight();
    delay(200);
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
    lift(drop_height + 7);
    swingGripper('l', Swing_Left + switch_degree);
    swingGripper('r', Swing_Right + switch_degree);
    moveToCan(3);
    lift(drop_height + 4);
    delay(200);
    dropCan_NoShake('a');
  } else {
    lift(drop_height + 3);
    if (left_gripper == 'l' && right_gripper == 'r') {
      swingGripper('l', Swing_Left + switch_degree);
      swingGripper('r', Swing_Right + switch_degree);
      moveToCan(distance);
      lift(drop_height);
      delay(200);
      dropCan_NoShake('a');
    } else if (left_gripper == 'l' && right_gripper == 'c') {
      swingGripper('l', Swing_Left + switch_degree);
      swingGripper('r', Swing_Right - (switch_degree + 10));
      moveToCan(distance);
      lift(drop_height);
      delay(200);
      dropCan_NoShake('a');
    } else if (left_gripper == 'c' && right_gripper == 'r') {
      swingGripper('l', Swing_Left - (switch_degree + 10));
      swingGripper('r', Swing_Right + switch_degree);
      moveToCan(distance);
      lift(drop_height);
      delay(200);
      dropCan_NoShake('a');
    } else if (left_gripper == 's' || right_gripper == 's') {
      moveToCan(distance + 1);
      lift(drop_height);
      delay(200);
      dropCan_NoShake('a');
    } else {
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      if (left_gripper == 'c') {
        swingGripper('l', Swing_Left - (switch_degree + 10));
        swingGripper('r', Swing_Right + 90);
        moveToCan(distance);
        lift(drop_height);
        delay(200);
        dropCan('l');
        delay(200);
        BB(30, 400);
        lift(drop_height + 3);
        switchGripper('r', 'l');
        delay(1000);
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('r', Swing_Right + 90);
        moveToCan(distance);
        dropCan_NoShake('l');
      } else if (right_gripper == 'c') {
        swingGripper('r', Swing_Right - (switch_degree + 10));
        swingGripper('l', Swing_Left + 90);
        moveToCan(distance);
        lift(drop_height);
        delay(200);
        dropCan('r');
        delay(200);
        BB(30, 400);
        lift(drop_height + 3);
        switchGripper('l', 'r');
        delay(1000);
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('l', Swing_Left + 90);
        moveToCan(distance);
        dropCan_NoShake('r');
      }
    }
  }
  delay(200);
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  vTaskSuspend(switchGripperTaskHandle);
}

////////////////////////////////
void placeCan1_NoShake_Enhanced(char color, char from_gripper, char drop_point, int B_speed, int B_delay) {
  int drop_height = 0;
  int drop_delay = 200;
  int UP_delay = 200;

  // เซ็ตความสูงและเวลาตามสี
  if (color == 'R' || color == 'r') { drop_height = 16; drop_delay = 950; UP_delay = 650;}      // สีแดง
  else if (color == 'Y' || color == 'y') { drop_height = 10; drop_delay = 650; UP_delay = 400;} // สีเหลือง
  else if (color == 'G' || color == 'g') { drop_height = 5; drop_delay = 300; UP_delay = 150;}  // สีเขียว

  // แปลงอักษรพิมพ์ใหญ่เป็นพิมพ์เล็ก ป้องกันการพิมพ์ผิด
  if (from_gripper == 'R') from_gripper = 'r';
  else if (from_gripper == 'L') from_gripper = 'l';
  
  if (drop_point == 'R') drop_point = 'r';
  else if (drop_point == 'L') drop_point = 'l';
  else if (drop_point == 'C') drop_point = 'c';
  else if (drop_point == 'S') drop_point = 's';

  int distance = 5;

  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  lift(drop_height + 4);
  delay(drop_height * 20);
  
  if (from_gripper == 'l' && drop_point == 'l') {
    swingGripper('l', Swing_Left + switch_degree);
    swingGripper('r', Swing_Right + 80);
  } else if (from_gripper == 'l' && drop_point == 'c') {
    swingGripper('l', Swing_Left - (switch_degree + 10));
    swingGripper('r', Swing_Right + 90);
  } else if (from_gripper == 'r' && drop_point == 'r') {
    swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right + switch_degree);
  } else if (from_gripper == 'r' && drop_point == 'c') {
    swingGripper('l', Swing_Left + 90);
    swingGripper('r', Swing_Right - (switch_degree + 10));
  } else if (from_gripper == 'l' && drop_point == 's') {
    swingGripper('r', Swing_Right + 80);
  } else if (from_gripper == 'r' && drop_point == 's') {
    swingGripper('l', Swing_Left + 80);
  } else {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    switchGripper(from_gripper, drop_point);
  }
  
  delay(UP_delay);
  moveToCan(distance);
  lift(drop_height + 2);
  delay(drop_height * 20); 
  dropCan_NoShake(from_gripper);
  BB(40, 500);
  delay(500);
  lift(3);
  delay(drop_height * 75);
  BB(B_speed, B_delay);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(drop_delay);
  vTaskSuspend(switchGripperTaskHandle);
}

void placeCan2_NoShake_Enhanced(char color, char left_gripper, char right_gripper, int B_speed, int B_delay) {
  int drop_height = 0;
  int drop_delay = 200; // ค่าเริ่มต้นเผื่อไว้
  int UP_delay = 200;

  // เซ็ตความสูงและเวลาตามสี
  if (color == 'R' || color == 'r') { drop_height = 16; drop_delay = 950; UP_delay = 650;}      // สีแดง
  else if (color == 'Y' || color == 'y') { drop_height = 10; drop_delay = 650; UP_delay = 400;} // สีเหลือง
  else if (color == 'G' || color == 'g') { drop_height = 5; drop_delay = 300; UP_delay = 150;}  // สีเขียว
  
  // แปลงอักษรพิมพ์ใหญ่เป็นพิมพ์เล็ก ป้องกันการพิมพ์ผิด
  if (left_gripper == 'R') left_gripper = 'r';
  else if (left_gripper == 'L') left_gripper = 'l';
  else if (left_gripper == 'C') left_gripper = 'c';
  else if (left_gripper == 'S') left_gripper = 's';

  if (right_gripper == 'R') right_gripper = 'r';
  else if (right_gripper == 'L') right_gripper = 'l';
  else if (right_gripper == 'C') right_gripper = 'c';
  else if (right_gripper == 'S') right_gripper = 's';

  int distance = 4; // ล็อคค่า distance ไว้ที่ 4

  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  if (left_gripper == 'r' && right_gripper == 'l') {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    lift(0);
    delay(200);
    swingGripper('l', Swing_Left - (switch_degree + 13));
    delay(200);
    servoWrite(chanal_Gripper_Left, Open_Left);
    delay(200);
    lift(13);
    delay(1000);
    switchGripper('r', 'l');
    delay(1000);
    servoWrite(chanal_Gripper_Right, Open_Right);
    swingGripper('r', Swing_Right - (switch_degree + 10));
    lift(0);
    delay(1700);
    FF(20, 100);
    servoCloseRight();
    delay(200);
    servoWrite(chanal_Swing_Left, Swing_Left);
    servoWrite(chanal_Swing_Right, Swing_Right);
    lift(drop_height + 7);
    swingGripper('l', Swing_Left + switch_degree);
    swingGripper('r', Swing_Right + switch_degree);
    moveToCan(distance);
    lift(drop_height + 4);
    delay(200);
    dropCan_NoShake('a');
  } else {
    lift(drop_height + 3);
    if (left_gripper == 'l' && right_gripper == 'r') {
      swingGripper('l', Swing_Left + switch_degree);
      swingGripper('r', Swing_Right + switch_degree);
      delay(UP_delay);
      moveToCan(distance);
      lift(drop_height);
      delay(200);
      dropCan_NoShake('a');
    } else if (left_gripper == 'l' && right_gripper == 'c') {
      swingGripper('l', Swing_Left + switch_degree);
      swingGripper('r', Swing_Right - (switch_degree + 10));
      delay(UP_delay);
      moveToCan(distance);
      lift(drop_height);
      delay(200);
      dropCan_NoShake('a');
    } else if (left_gripper == 'c' && right_gripper == 'r') {
      swingGripper('l', Swing_Left - (switch_degree + 10));
      swingGripper('r', Swing_Right + switch_degree);
      delay(UP_delay);
      moveToCan(distance);
      lift(drop_height);
      delay(200);
      dropCan_NoShake('a');
    } else if (left_gripper == 's' || right_gripper == 's') {
      delay(UP_delay);
      moveToCan(distance + 1);
      lift(drop_height);
      delay(200);
      dropCan_NoShake('a');
    } else {
      vTaskResume(switchGripperTaskHandle);
      delay(10);
      if (left_gripper == 'c') {
        swingGripper('l', Swing_Left - (switch_degree + 10));
        swingGripper('r', Swing_Right + 90);
        moveToCan(distance);
        lift(drop_height);
        delay(200);
        dropCan('l');
        delay(200);
        BB(B_speed, B_delay);
        lift(drop_height + 3);
        switchGripper('r', 'l');
        delay(1000);
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('r', Swing_Right + 90);
        moveToCan(distance);
        dropCan_NoShake('l');
      } else if (right_gripper == 'c') {
        swingGripper('r', Swing_Right - (switch_degree + 10));
        swingGripper('l', Swing_Left + 90);
        moveToCan(distance);
        lift(drop_height);
        delay(200);
        dropCan('r');
        delay(200);
        BB(B_speed, B_delay);
        lift(drop_height + 3);
        switchGripper('l', 'r');
        delay(1000);
        servoWrite(chanal_Gripper_Left, Close_Left);
        servoWrite(chanal_Gripper_Right, Close_Right);
        swingGripper('l', Swing_Left + 90);
        moveToCan(distance);
        dropCan_NoShake('r');
      }
    }
  }
  delay(200);
  BB(B_speed, B_delay);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(drop_delay);
  vTaskSuspend(switchGripperTaskHandle);
}

//////////////////////////////////////////