void ReadME() {
  // S 40 D 700 = 1Box
  // S 60 D 535 = 1Box
  // S 60 D 840 = 2Box
  // S 60 D 1220 = 3Box
  ///////--> motorTimeDegree_Enhanced( 30, 60, 840, 'L');
  // 1 Box = 250
  // 2 Box = 600
  // 3 Box = 900
  // 4 Box = 1250
  ///////--> motorTimeDegree_Enhanced( 30, 80, 840, 'L');
  // 1 Box = 200
  // 2 Box = 475
  // 3 Box = 725
  // 4 Box = 975
  ///////--> motorTimeBackDegree_Enhanced( 30, 60, 840, 'L');
  // --> เซ็ตหน้า/หลัง
  // --> 330
  // --> ตอนคีบแล้วจะถอยหลังมากลางบล็อก
  // --> -150
/////////////////////////////////////////
  // FF(40, 700);
  // FF(60, 550);
  // FF(40, 700, 'L');
  // FF(60, 550, 'L');
  // motorTimeDegree(30, 550);
  // turnDegreeFront(90);

  // BB(40, 700);
  // BB(60, 550);
  // BB(40, 700, 'L');
  // BB(60, 550, 'L');

  // spinDegree(90);  //ใช้ไม่ได้
  // spinDegree(-90);

  // spinDegree(90);
  // spinDegree(-90);
/////////////////////////////////////////
  // SetFront(20, 330);
  // SetFront(20, 330, 'R');
  // SetBack(20, 330);
  // SetBack(20, 330, 'L');

  // SetFront_Wall(20, 330);
  //-->> จูนแบบเลี้ยว
  //-->> 275
  //-->> จูนแบบไม่เลี้ยว
  //-->> 330
/////////////////////////////////////////
  //ถ้าตั้งยกเป็น 0 จะใชตัวจับตรงมือจับ
  // pickCan(5, NO_SWITCH_LR);
  // placeCan1_NoShake(5, 4, 'l', 'c');
/////////////////////////////////////////
  // lift(5);

  // servoWrite(chanal_Swing_Right, 40);
  // servoWrite(chanal_Swing_Left, 40);
  // servoWrite(chanal_Gripper_Left, Open_Left);
  // servoWrite(chanal_Gripper_Right, Open_Right);

  // servoCloseLeft();
  // servoCloseRight();

  // ServoTest_LR(5); //-->สลับกระป๋อง
  // Balance_Arm('C');
///////////////////////เปิดอ่าค่า เซนเซอร์ ////////////////////
  // ShowValue_Sensor(); // โชว์ค่าเซ็นเซอร์ตรวจจับเส้น
  // ShowDistanceSensor(); // โชว์ค่าเซ็นเซอร์วัดระยะทาง
}
void Test_Function()
{
  
  // Servo_LRfast('L');
  // pickCan(5, SWITCH_LR);
  // ServoTest_LR(5);
  // SetFront_Wall(20, 330);
  // SetBack(20, 315);
  // motorTimeDegree_Enhanced( 30, 80, 975);
  // turnDegreeFront(-90);
  SetFront(20);
  motorStop(); delay(50);
}