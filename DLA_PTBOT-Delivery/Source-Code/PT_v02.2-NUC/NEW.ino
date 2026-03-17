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

void Balance_Arm(char select){
  if (select == 'C') {
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  servoWrite(chanal_Swing_Left, Swing_Left - 15);
  servoWrite(chanal_Swing_Right, Swing_Right - 15);
  }
  else if (select == 'O') {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  }
  else if (select == 'L') {
  servoWrite(chanal_Swing_Left, Swing_Left + 90);
  servoWrite(chanal_Swing_Right, Swing_Right - 15);
  delay(500);
  }
  else if (select == 'R') {
  servoWrite(chanal_Swing_Right, Swing_Right + 90);
  servoWrite(chanal_Swing_Left, Swing_Left - 15);
  delay(500);
  }
  else if (select == 'S') {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(500);
  }
  else if (select == 'W') {
  servoWrite(chanal_Swing_Left, Swing_Left + 90);
  servoWrite(chanal_Swing_Right, Swing_Right + 90);
  delay(500);
  }
}



void PickCanNew(int pick_height, int B_Speed, int B_delay) {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) moveToCan(pick_can_distance);
  else moveToCan0(can_distance);
  delay(200);
  lift(pick_height - 1);
  delay(500);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(300);
  lift(pick_height + 4);
  delay(750);
  BB(30, 400);
  Stable_CAN();
  BB(B_Speed, B_delay);
}

void Stable_CAN() {
  lift(0);
  BB(10, 300);
  delay(500);
  servoWrite(chanal_Gripper_Left, Close_Left - 15);
  servoWrite(chanal_Gripper_Right, Close_Right - 15);
  delay(500);
  FF(10, 300);
  delay(500);
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(500);
  lift(3);
}

void PlaceCanNew(int drop_height, char from_gripper, char drop_point, int B_speed, int B_delay) {
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(300);
  lift(1);
  servoCloseLeft();
  servoCloseRight();
  delay(250);
  servoWrite(chanal_Gripper_Left, Open_Left + 30);
  servoWrite(chanal_Gripper_Right, Open_Right + 30);
  delay(100);
  lift(0);
  delay(300);
  FF(30, 100);
  delay(500);
  servoCloseLeft();
  servoCloseRight();
  lift(3);
  delay(200);
  lift(4);
  delay(300);
  lift(drop_height + 5);
  delay(750);
  // delay(500);
  // lift(4);
  // delay(500);
  // lift(drop_height + 3);
  // delay(750);



  // if (from_gripper == 'R') from_gripper = 'r';
  // else if (from_gripper == 'L') from_gripper = 'l';
  // else if (from_gripper == 'C') from_gripper = 'c';

  // if (drop_point == 'R') drop_point = 'r';
  // else if (drop_point == 'L') drop_point = 'l';
  // else if (drop_point == 'C') drop_point = 'c';
  // else if (drop_point == 'S') drop_point = 's';

  // if (from_gripper == 'l' && drop_point == 'l') {
  //   swingGripper('l', Swing_Left + switch_degree);
  //   swingGripper('r', Swing_Right + 52);
  // } else if (from_gripper == 'l' && drop_point == 'c') {
  //   swingGripper('l', Swing_Left - (switch_degree));
  //   swingGripper('r', Swing_Right + 52);
  // } else if (from_gripper == 'r' && drop_point == 'r') {
  //   swingGripper('l', Swing_Left + 52);
  //   swingGripper('r', Swing_Right + switch_degree);
  // } else if (from_gripper == 'r' && drop_point == 'c') {
  //   swingGripper('l', Swing_Left + 52);
  //   swingGripper('r', Swing_Right - (switch_degree));
  // } else if (from_gripper == 'l' && drop_point == 's') {
  //   swingGripper('l', Swing_Left);
  //   swingGripper('r', Swing_Right + 52);
  // } else if (from_gripper == 'r' && drop_point == 's') {
  //   swingGripper('l', Swing_Left + 52);
  //   swingGripper('r', Swing_Right);
  // } else {
  //   vTaskResume(switchGripperTaskHandle);
  //   delay(10);
  //   switchGripper(from_gripper, drop_point);
  // }
  // delay(750);
  // if (drop_height != 0) moveToCan(Place_can_distance);
  // else moveToCan0(can_distance);
  // lift(drop_height);
  // delay(400);
  // dropCan_NoShake(from_gripper);
  // delay(200);
  // BB(B_speed, B_delay);
  // lift(2);
  // servoWrite(chanal_Swing_Left, Swing_Left);
  // servoWrite(chanal_Swing_Right, Swing_Right);
  // delay(650);
  // vTaskSuspend(switchGripperTaskHandle);
}
void PlaceCanNew_Norechack(int drop_height, char from_gripper, char drop_point, int B_speed, int B_delay) {
  int R_D = 0;
  lift(3);
  delay(200);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(300);
  servoCloseLeft();
  servoCloseRight();
  lift(4);
  delay(650);
  lift(drop_height + 3);
  delay(1000);



  if (from_gripper == 'R') from_gripper = 'r';
  else if (from_gripper == 'L') from_gripper = 'l';
  else if (from_gripper == 'C') from_gripper = 'c';

  if (drop_point == 'R') drop_point = 'r';
  else if (drop_point == 'L') drop_point = 'l';
  else if (drop_point == 'C') drop_point = 'c';
  else if (drop_point == 'S') drop_point = 's';

  if (from_gripper == 'l' && drop_point == 'l') {
    swingGripper('l', Swing_Left + switch_degree);
    swingGripper('r', Swing_Right + 52);
  } else if (from_gripper == 'l' && drop_point == 'c') {
    swingGripper('l', Swing_Left - (switch_degree));
    swingGripper('r', Swing_Right + 52);
  } else if (from_gripper == 'r' && drop_point == 'r') {
    swingGripper('l', Swing_Left + 52);
    swingGripper('r', Swing_Right + switch_degree);
  } else if (from_gripper == 'r' && drop_point == 'c') {
    swingGripper('l', Swing_Left + 52);
    swingGripper('r', Swing_Right - (switch_degree));
  } else if (from_gripper == 'l' && drop_point == 's') {
    swingGripper('l', Swing_Left);
    swingGripper('r', Swing_Right + 52);
  } else if (from_gripper == 'r' && drop_point == 's') {
    swingGripper('l', Swing_Left + 52);
    swingGripper('r', Swing_Right);
  } else {
    vTaskResume(switchGripperTaskHandle);
    delay(10);
    switchGripper(from_gripper, drop_point);
  }
  delay(750);
  if (drop_height != 0) moveToCan(Place_can_distance);
  else moveToCan0(can_distance);
  lift(drop_height);
  delay(400);
  dropCan_NoShake(from_gripper);
  delay(200);
  delay(R_D);
  BB(B_speed, B_delay);
  lift(3);
  servoWrite(chanal_Swing_Left, Swing_Left);
  servoWrite(chanal_Swing_Right, Swing_Right);
  delay(650);
  vTaskSuspend(switchGripperTaskHandle);
}

////////////////////////////////////////////////////////////////////////////////////

void SetFront_Wall(int speed) {
  lift(2);
  delay(100);
  Balance_Arm('W');
  SetFront(speed);
  Balance_Arm('S');
}
void SetFront_Wall(int speed, float timer) {
  lift(2);
  delay(100);
  Balance_Arm('W');
  SetFront(speed, timer);
  Balance_Arm('S');
}
void SetFront_Wall(int speed, float timer, char select) {
  lift(2);
  delay(100);
  Balance_Arm('W');
  delay(300);
  SetFront(speed, timer, select);
  delay(300);
  Balance_Arm('S');
}