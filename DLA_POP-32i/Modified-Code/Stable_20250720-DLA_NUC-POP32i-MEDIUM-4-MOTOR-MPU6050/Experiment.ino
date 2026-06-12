void Experiment() {
  // 0:เคลียร์มุมเริ่มต้น, 1:ไม่เคลียร์มุมเริ่มต้น, 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการเหมือน 0
  // TurnLeftDegree(100, 90, 1);
  // TurnRightDegree(100, 90, 2);

  // 0:ไม่หมุนกลับทิศ, 1:หมุนกลับทิศ
  // TracDegreeSpeedTime(60, 0, 1000, 0);

//////////////////////////////////////////////////////////////////////////
  delay(500);
  zeroYaw();
  oled.text(3, 1, "zeroYaw Successfully");
  oled.show();
  waitSW_A();
  oled.clear();
  oled.text(4, 0, "Running Laboratory...");
  beep(100);
  oled.show();

  Lab_1();
  Lab_2();
  Lab_3();
}

void Lab_1() {

}

void Lab_2() {

}

void Lab_3() {

}

