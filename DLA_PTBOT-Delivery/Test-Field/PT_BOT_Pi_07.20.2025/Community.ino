void operation_community()
{
  // 2 = 200, 2.5 = 250, 3 = 500, 4 = 850, Hight Way = 1300 1400
  //      IN             OUT
  // SetFront = 375, SetFront = 400
  // SetBack = 200, SetBack = 225
  // motorStop(); delay(8000);
  box1_community();
  box2_community();
  box3_community();
  box4_community();
  box5_community();
  box6_community();
  // box7_community();
  // box8_community();
  // box9_community();
  // box10_community();
}
void box1_community()
{
  Balance_Arm('C');
  motorTimeDegree_Enhanced(-30, -60, 850);
  SetBack(20, 200, 'L');
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 400, 'L');
  SetFront_Wall(20);
  motorTimeDegree_Enhanced(-30, -60, 250, 'L');
  motorTimeDegree_Enhanced(30, 60, 200, 'L');
  SetBack(20);
  motorTimeDegree_Enhanced(30, 60, 250, 'R');
  SetFront(20);
  motorTimeDegree_Enhanced(-30, -60, 1400, 'L');
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20, 200, 'R');
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 225, 'L');
}

void box2_community()
{
  pickCan(5, NO_SWITCH_LR, 'Y'); // YR
  SetBack(20, 225, 'L');
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 375, 'R');
  SetBack(20, 200);
  motorTimeDegree_Enhanced(30, 60, 500, 'L');
  motorTimeDegree_Enhanced(30, 60, 200, 'L');
  motorTimeDegree_Enhanced(-30, -60, 200);
  delay(500);
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 375, 'L');
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 200, 'L');
}

void box3_community()
{
  PLACE_SLOPE_SONAR(12, 'r', 'Y'); // Yellow right
  spinDegree(90);
  SetBack(20, 200);
  motorTimeDegree_Enhanced(30, 60, 500, 'R');
  motorTimeDegree_Enhanced(30, 60, 200, 'R');
  motorTimeDegree_Enhanced(30, 60, 200, 'R');
  motorTimeDegree_Enhanced(30, 60, -200);
  SetBack(20, 200, 'L');
  SetBack(20);
}

void box4_community()
{
  PLACE_SLOPE_SONAR(37, 'r', 'Y'); // Red right
  SetBack(20, 225, 'R');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 375, 'L');
}

void box5_community()
{
  pickCan(0, NO_SWITCH_LR, 'Y'); // RY
  spinDegree(90);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 200, 'L');
}

void box6_community()
{
  PLACE_SLOPE_SONAR(37, 'l', 'Y'); // Red left
  // SetBack(20, 225, 'R');
  // motorTimeDegree_Enhanced(30, 60, 200);
  // SetFront(20, 375, 'L');
}

void box7_community()
{

}

void box8_community()
{

}

void box9_community()
{

}

void box10_community()
{

}

  // motorTimeDegree_Enhanced(-30, -60, 200);
  // SetBack(20, 200, 'L');
  // motorTimeDegree_Enhanced(30, 60, 500, 'L');
  // SetFront_Wall(20, 375, 'R');

  // pickCan(5, NO_SWITCH_LR, 'Y'); // GG
  // motorTimeDegree_Enhanced(-30, -60, 500);
  // SetBack(20, 225, 'R');
  // SetBack(20);
  // motorTimeDegree_Enhanced(30, 60, 250, 'R');
  // motorTimeDegree_Enhanced(-30, -60, 1300);
  // SetBack(20, 225, 'R');

  // PLACE_LOCK_SONAR_ALL(5, 'Y'); // Green
  // Balance_Arm('C');
  // motorStop(); delay(250);
  // spinDegree(90);
  // motorStop(); delay(250);
  // SetFront(20);