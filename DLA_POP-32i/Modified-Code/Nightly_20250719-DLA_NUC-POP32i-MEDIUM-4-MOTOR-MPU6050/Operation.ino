void Operation()
{
  // 0:เคลียร์มุมเริ่มต้น, 1:ไม่เคลียร์มุมเริ่มต้น, 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการเหมือน 0
  // TurnLeftDegree(100, 90, 1);
  // TurnRightDegree(100, 90, 2);

  // 0:ไม่หมุนกลับทิศ, 1:หมุนกลับทิศ
  // TracDegreeSpeedTime(60, 0, 1000, 0);

//////////////////////////////////////////////////////////////////////////
  Wait_sw_ok_press();
  beep(0);
  zeroYaw();
  delay(500);
  
  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
  Mission_5();
}

void Mission_1()
{

}

void Mission_2()
{

}

void Mission_3()
{

}

void Mission_4()
{

}

void Mission_5()
{

}