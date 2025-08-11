#define chanal_Swing_Left 0
#define chanal_Swing_Right 1
#define chanal_Gripper_Left 2
#define chanal_Gripper_Right 3
////////////////////////////////////////////////////////
int Swing_Left = 90;   //SO สวิงแขนซ้ายเพิ่มง้างออก ลด หุบเข้า
int Swing_Right = 90;  //S1 สวิงแขนขวาเพิ่มง้างออก ลด หุบเข้า

int Open_Left = 50;   //S2 อ้ามือ ชุดมือจับมือซ้ายค่ามากยิ่งหุบ 35 เขียว
int Close_Left = 101;  //S2 หุบมือ ชุดมือจับมือซ้ายค่าน้อยยิ่งอ้า เขียว

int Open_Right = 50;   //S3 อ้ามือ ชุดมือจับมือขวาค่ามากยิ่งหุบ 35 เขียว
int Close_Right = 86;  //S3 หุบมือ ชุดมือจับมือขวา ค่าน้อยยิ่งอ้า เขียว
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
  for (int i = Close_Left; i > Open_Left - 1; i--) {
    servoWrite(chanal_Gripper_Left, i);
    delay(5);
  }
}

void servoCloseLeft() {
  servoWrite(chanal_Gripper_Left, Close_Left);
}

void servoOpenRight() {
  for (int i = Close_Right; i > Open_Right - 1; i--) {
    servoWrite(chanal_Gripper_Right, i);
    delay(5);
  }
}

void servoCloseRight() {
  servoWrite(chanal_Gripper_Right, Close_Right);
}
void ServoTest_LR(int pick_height) {
  lift(0);
  delay(500);
  vTaskResume(switchGripperTaskHandle);
  servoCloseRight();
  servoCloseLeft();
  servoWrite(chanal_Swing_Left, 36);
  delay(500);
  servoWrite(chanal_Gripper_Left, Open_Left);
  delay(500);
  lift(pick_height + 18);
  delay(950);
  Servo_LRfast('R');
  servoWrite(chanal_Swing_Right, 40);
  servoWrite(chanal_Swing_Left, 110);
  servoWrite(chanal_Gripper_Right, Open_Right - 10);
  delay(350);
  lift(0);
  delay(750);
  servoCloseLeft();
  delay(1000);
  FF(10, 100);
  motorStop();
  delay(100);
  servoCloseRight();
  lift(1);
  delay(250);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Swing_Left, Swing_Left);
  motorStop();
  delay(50);
}
void Servo_LRfast(char select) {
  if (select == 'L') {
    servoCloseLeft();
    delay(100);
    servoWrite(chanal_Swing_Right, 40);
    delay(100);
    servoWrite(chanal_Gripper_Right, Open_Right - 10);
    delay(100);
    servoCloseLeft();
    servoWrite(chanal_Swing_Left, 40);
    delay(75);
    servoCloseRight();
    delay(100);
    servoWrite(chanal_Gripper_Left, Open_Left - 10);
    delay(100);
    servoWrite(chanal_Swing_Right, Swing_Right);
    delay(100);
    servoWrite(chanal_Swing_Left, Swing_Left);
    delay(100);
  }
  if (select == 'R') {
    servoCloseRight();
    delay(100);
    servoWrite(chanal_Swing_Left, 40);
    delay(100);
    servoWrite(chanal_Gripper_Left, Open_Left - 10);
    delay(100);
    servoCloseRight();
    servoWrite(chanal_Swing_Right, 40);
    delay(150);
    servoCloseLeft();
    delay(75);
    servoWrite(chanal_Gripper_Right, Open_Right - 10);
    delay(100);
    servoWrite(chanal_Swing_Left, Swing_Left);
    delay(100);
    servoWrite(chanal_Swing_Right, Swing_Right);
    delay(100);
  }
}
void TempOpen(char select)
{
  if (select == 'L')
  {
    servoWrite(chanal_Gripper_Left, Open_Left);
    lift(0);
    delay(750);
    servoWrite(chanal_Gripper_Left, Close_Left);
    lift(2);
    motorStop();delay(150);
  }
  if (select == 'R')
  {
    servoWrite(chanal_Gripper_Right, Open_Right);
    lift(0);
    delay(750);
    servoWrite(chanal_Gripper_Right, Close_Right);
    lift(2);
    motorStop();delay(150);
  }
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

void moveToCan(int distance) {
  vTaskResume(sonarTaskHandle);
  delay(10);
  unsigned long int timer = millis();
  while (readSonar() > distance || millis() - timer <= 500) FF(10);
  vTaskSuspend(sonarTaskHandle);
}

void moveToCanBack(int distance) {
  vTaskResume(sonarTaskHandle);
  delay(10);
  unsigned long int timer = millis();
  while (readSonar() > distance || millis() - timer <= 500) BB(10);
  vTaskSuspend(sonarTaskHandle);
}

void moveToCan0(int distance) {
  unsigned long int timer = millis();
  while (readCanDistance() > distance || millis() - timer <= 500) FF(10);
  motorStop();
  motorTimeDegree(10, 400);
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
  delay(200);
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

void pickCan(int pick_height, bool switch_lr, char withdraw) {
  Balance_Arm('O');
  lift(pick_height);
  if (pick_height != 0)
  {
    moveToCan(5);
    motorTimeDegree(10, 300); 
    motorStop(); delay(500);
  }
  else moveToCan0(50);
  servoCloseLeft();
  servoCloseRight();
  delay(3 * 250);
  lift(pick_height + 3);
  delay(3 * 250);

  if (withdraw == 'Y') {
    motorTimeDegree(-20, 675);
  }
  else if (withdraw == 'N') {
    motorStop();
  }

  if (switch_lr == 1) {
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
    servoWrite(chanal_Swing_Left, 50);
    delay(100);
    servoWrite(chanal_Gripper_Right, Close_Right);
    delay(100);
    servoWrite(chanal_Gripper_Left, Open_Left);
    delay(100);
    servoWrite(chanal_Swing_Right, 140);
    delay(100);
    lift(0);
    delay(2000);
    servoWrite(chanal_Gripper_Left, Close_Left);
    delay(100);
    servoWrite(chanal_Swing_Left, Swing_Left);
    delay(100);
    servoWrite(chanal_Swing_Right, Swing_Right);
    delay(100);
    motorStop(); delay(100); 
  } else if (switch_lr == 0) {
    motorStop();
  }

  motorTimeDegree(-20, 400);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  lift(0);
  delay(pick_height * 75);
  servoWrite(chanal_Gripper_Left, Close_Left - 5);
  servoWrite(chanal_Gripper_Right, Close_Right - 7);
  delay(1000);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(100);
  lift(3);
  delay(3 * 250);
}








void PLACE_LOCK_SONAR_ALL(int drop_height, char withdraw){
  Balance_Arm('S');
  lift(drop_height + 3);
  delay(drop_height * 75);
  moveToCan(5);
  motorTimeDegree(10, 300); 
  motorStop(); delay(500);

  servoWrite(chanal_Gripper_Left, 85);
  servoWrite(chanal_Gripper_Right, 87);
  delay(1000);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);

  if (withdraw == 'Y') {
    motorTimeDegree(-20, 675);
  }
  else if (withdraw == 'N') {
    motorStop();
  }
  motorTimeDegree(-20, 400);
  motorStop(); delay(100);
  lift(3);
  delay(drop_height * 75);
  Balance_Arm('S');
}

void PLACE_LOCK_SONAR(int drop_height, char from_gripper, char withdraw) {
  Balance_Arm('S');
  lift(drop_height + 3);
  delay(drop_height * 75);
  
  if (from_gripper == 'l') {
    servoWrite(chanal_Swing_Right, 180);
    moveToCan(5);
    motorTimeDegree(10, 300); 
    motorStop(); delay(500);
    servoWrite(chanal_Gripper_Left, 85);
    delay(1000);
    servoWrite(chanal_Gripper_Left, Open_Left);
  }
  else if (from_gripper == 'r') {
    servoWrite(chanal_Swing_Left, 180);
    moveToCan(5);
    motorTimeDegree(10, 300); 
    motorStop(); delay(500);
    servoWrite(chanal_Gripper_Right, 87);
    delay(1000);
    servoWrite(chanal_Gripper_Right, Open_Right);
  }

  if (withdraw == 'Y') {
    motorTimeDegree(-20, 675);
  }
  else if (withdraw == 'N') {
    motorStop();
  }
  motorTimeDegree(-20, 400);
  motorStop(); delay(100);
  lift(3);
  delay(drop_height * 75);
  Balance_Arm('S');
}

void PLACE_SLOPE_SONAR(int drop_height, char from_gripper, char withdraw) {
  Balance_Arm('S');
  lift(drop_height + 3);
  delay(drop_height * 75);
  
  if (from_gripper == 'l') {
    servoWrite(chanal_Swing_Left, 115);
    servoWrite(chanal_Swing_Right, 180);
    moveToCan(5);
    motorTimeDegree(10, 300); 
    motorStop(); delay(500);
    servoWrite(chanal_Gripper_Left, 85);
    delay(1000);
    servoWrite(chanal_Gripper_Left, Open_Left);
  }
  else if (from_gripper == 'r') {
    servoWrite(chanal_Swing_Right, 118);
    servoWrite(chanal_Swing_Left, 180);
    moveToCan(5);
    motorTimeDegree(10, 300); 
    motorStop(); delay(500);
    servoWrite(chanal_Gripper_Right, 87);
    delay(1000);
    servoWrite(chanal_Gripper_Right, Open_Right);
  }
  if (withdraw == 'Y') {
    motorTimeDegree(-20, 675);
  }
  else if (withdraw == 'N') {
    motorStop();
  }
  motorTimeDegree(-20, 400);
  motorStop(); delay(100);
  lift(3);
  delay(drop_height * 75);
  Balance_Arm('S');
}

void PLACE_CENTER_SONAR(int drop_height, char from_gripper, char withdraw) {
  Balance_Arm('S');
  lift(drop_height + 3);
  delay(drop_height * 75);

  if (from_gripper == 'l') {
    servoWrite(chanal_Swing_Left, 65);
    servoWrite(chanal_Swing_Right, 180);
    moveToCan(5);
    motorTimeDegree(10, 300); 
    motorStop(); delay(500);
    servoWrite(chanal_Gripper_Left, 85);
    delay(1000);
    servoWrite(chanal_Gripper_Left, Open_Left);
  }
  else if (from_gripper == 'r') {
    servoWrite(chanal_Swing_Right, 55);
    servoWrite(chanal_Swing_Left, 180);
    moveToCan(5);
    motorTimeDegree(10, 300); 
    motorStop(); delay(500);
    servoWrite(chanal_Gripper_Right, 87);
    delay(1000);
    servoWrite(chanal_Gripper_Right, Open_Right);
  }
  if (withdraw == 'Y') {
    motorTimeDegree(-20, 675);
  }
  else if (withdraw == 'N') {
    motorStop();
  }
  motorTimeDegree(-20, 400);
  motorStop(); delay(100);
  lift(3);
  delay(drop_height * 75);
  Balance_Arm('S');
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
  delay(1000);
  BB(30, 400);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
}

void placeCan1_NoShake(int drop_height, int distance, char from_gripper, char drop_point) {
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  lift(drop_height + 3);
  delay(200);
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
  } else if (from_gripper == 'l' && drop_point == 's') {
    swingGripper('r', Swing_Right + 90);
  } else if (from_gripper == 'r' && drop_point == 's') {
    swingGripper('l', Swing_Left + 90);
  } else {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    switchGripper(from_gripper, drop_point);
  }
  moveToCan(distance);
  lift(drop_height);
  delay(300);
  dropCan_NoShake(from_gripper);
  delay(200);
  motorTimeDegree(-15, 1400);
  motorStop(); delay(100); 
  lift(2);
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

void Balance_Arm(char select){
  if (select == 'C') {
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  servoWrite(chanal_Swing_Left, 40);
  servoWrite(chanal_Swing_Right, 40);
  }
  else if (select == 'O') {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  }
  else if (select == 'L') {
  servoWrite(chanal_Swing_Left, 180);
  servoWrite(chanal_Swing_Right, 30);
  delay(500);
  }
  else if (select == 'R') {
  servoWrite(chanal_Swing_Left, 35);
  servoWrite(chanal_Swing_Right, 180);
  delay(500);
  }
  else if (select == 'S') {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(500);
  }
}