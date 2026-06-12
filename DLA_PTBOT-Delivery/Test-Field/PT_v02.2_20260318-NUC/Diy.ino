void PickCan(int pick_height) {  // ระยะแท่น 5 10 15
  servoWrite(chanal_Swing_Left, Swing_Left - 3);
  servoWrite(chanal_Swing_Right, Swing_Right - 3);
  servoWrite(chanal_Gripper_Left, Open_Left);
  servoWrite(chanal_Gripper_Right, Open_Right);
  lift(pick_height);
  if (pick_height != 0) moveToCan(pick_can_distance);  //float pick_can_distance = 7.5;  // ค่าระยะจอดหน้าแท่นหยิบ
  else moveToCan0(can_distance);
  delay(100);
  servoCloseLeft();
  servoCloseRight();
  delay(200);
  lift(pick_height + 3);  // ยกเผื่อไว้อีก 1 cm
  delay(300);
}
void set_clos_open() {
  STOP();
  servoCloseLeft();
  STOP();
  servoCloseRight();
  STOP();
  servoOpenLeft();
  STOP();
  servoOpenRight();
}
void get_b(int lif) {  // จับกระป๋อง (ยก lif)
  servoCloseLeft();
  servoCloseRight();
  lift(lif);
}
void drop_b(int open) {                                // กางแขน คู่
  servoWrite(chanal_Gripper_Left, Close_Left - open);  //S2 หุบมือ ชุดมือจับมือซ้ายค่าน้อยยิ่งอ้า เลย -
  servoWrite(chanal_Gripper_Right, Close_Right - open);
  delay(1000);
  servoOpenLeft();
  servoOpenRight();
}
void setCan1(int open) {
  lift(0);
  delay(150);
  // servoWrite(chanal_Gripper_Left, Open_Left);
  // servoWrite(chanal_Gripper_Right, Open_Right);
  servoWrite(chanal_Gripper_Left, Close_Left - open);  //S2 หุบมือ ชุดมือจับมือซ้ายค่าน้อยยิ่งอ้า เลย -
  servoWrite(chanal_Gripper_Right, Close_Right - open);
  delay(1000);
  FF(10);
  delay(200);
  motorStop();
  servoWrite(chanal_Gripper_Left, Close_Left);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(150);
  lift(3);
  delay(150);
}