void CheckGoalyellow_offend()  //โหมด เปิดเกม
{
  Checkline();
  SetRobot();
  if(SW_A()) return false;
  else if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
    if (SW_A()) return false;
    SetRobot();
    Checkline();
    StartTimer();
    while (huskylens.updateBlocks() && huskylens.blockSize[1]) {
      if (millis() - Timer > 300) {

        shoot();
        holonomic(0, 0, 0);
        reload();
        Mode = 1;
        return false;
      } else {
        Checkline();
        holonomic(60, 90, 0);
      }
    }
  } else {
    if (SW_A()) return false;
    Mode = 1;
    discoveState = 1;
  }
}
void CheckGoalyellow_better() { /* โหมดถ่วงเวลาเมื่อนำ  */

  Checkline();
  SetRobot();
  if(SW_A()) return false;
  else if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
    if (SW_A()) return false;
    while (huskylens.updateBlocks() && huskylens.blockSize[1]) {
      Checkline();
      updateIMU();
      heading(100, 90, 0);
      if (SW_A()) return false;
    }
  } else if (huskylens.updateBlocks() && huskylens.blockSize[2] || huskylens.updateBlocks() && huskylens.blockSize[3]) {
    // shoot();
    // holonomic(0,0,0);
    // reload();
    CheckGoalyellowandblue();
  } else {
    if (SW_A()) return false;
    Mode = 1;
    discoveState = 1;
  }
  Mode = 1;
}
void Goal_Outline() {
  StartTimer();
  Checkline();
  //SetRobot();
  if (SW_A()) return false;
  else if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
    if (SW_A()) return false;
    while (huskylens.updateBlocks() && huskylens.blockSize[1]) {
      if (millis() - Timer > 300) {

        shoot();
        holonomic(0, 0, 0);
        reload();
        Mode = 1;
        Check_outline = 0;
        return false;
      } else {
        Checkline();
        holonomic(60, 90, 0);
      }
    }
  } else {
    if (SW_A()) return false;
    Mode = 1;
    discoveState = 1;
  }
}
void CheckGoal_Penality() { /*   ยิงจุดโทษ */

  SetRobot();
  if (huskylens.updateBlocks() && huskylens.blockSize[1] && abs(rot_error) < rotErrorGap) {
    if (SW_A()) return false;
    else if (step == 1) {
      StartTimer();
      while (1) {
        updateIMU();
        heading(30, 90, 0);
        if (SW_A()) return false;
        if (millis() - Timer > 500) break;
      }
      StartTimer();
      while (1) {
        updateIMU();
        heading(50, 50, 0);
        if (SW_A()) return false;
        if (millis() - Timer > 1000) break;
      }
      // holonomic(30,90,0);
      // delay(200);
      // holonomic(70,0,30);
      // delay(160);
      // holonomic(50,90,0);
      // delay(150);
      // shoot();
      // holonomic(0,0,0);
      // reload();
      StartTimer();
      while (1) {
        updateIMU();
        heading(90, 90, 0);
        if (SW_A()) return false;
        if (millis() - Timer > 300) {
          reload();
          shoot();
          holonomic(0,0,0);
          reload();
          break;
        }
      }
    } else {
      if (SW_A()) return false;
      SetRobot();
      updateIMU();
      heading(100, 90, 0);
    }
  } else if (huskylens.updateBlocks() && huskylens.blockSize[2]) {
    if (SW_A()) return false;
    reload();
    shoot();
  } else {
    Mode = 1;
    discoveState = 1;
  }
}
void CheckGoalyellowandblue() {
  if (huskylens.updateBlocks() && huskylens.blockSize[2] ||huskylens.updateBlocks() && huskylens.blockSize[3]) {
    GoalPosX = huskylens.blockInfo[2][0].x;
    if (GoalPosX > 160) {
      beep(100);
      holonomic(40, 180, -25);
      delay(300);
    } else {
      beep(100);
      holonomic(40, 0, 25);
      delay(300);
    }
    holonomic(50, 90, 0);
    delay(100);
    shoot();
    holonomic(0,0,0);
    reload();
  } else {
    holonomic(50, 90, 0);
    delay(100);
    shoot();
    holonomic(0,0,0);
    reload();
  }
  Mode = 1;
}