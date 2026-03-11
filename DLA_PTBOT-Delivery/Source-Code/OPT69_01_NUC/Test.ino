void pickCan_Test(int pick_height, bool switch_lr, char select) {
  Balance_Arm('O');
  lift(pick_height);
  delay(150);
  if (pick_height != 0) moveToCan(5);
  else moveToCan0(40);
  delay(300);
  servoCloseLeft();
  servoCloseRight();
  delay(200);
  lift(pick_height + 4);
  delay(500);
  lift(0);
  if (switch_lr == 1) {
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
    lift(0);  //ตอนลงมาจับเดิม
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
    motorStop();
  }

  if (select == 'Y') {
    BB(30, 800);
    motorStop();
  }
  if (select == 'N') {
    motorStop();
  }
  Stable_CAN();
}

void Stable_CAN() {
  lift(0);
  BB(60, 125);
  delay(600);
  servoWrite(chanal_Gripper_Left, Close_Left - 15);
  delay(100);
  servoWrite(chanal_Gripper_Right, Close_Right - 15);
  delay(100);
  FF(10, 300);
  delay(100);
  servoWrite(chanal_Gripper_Left, Close_Left);
  delay(100);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(100);
  lift(2);
}