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
  box7_community();
  box8_community();
  box9_community();
  // box10_community();
}
void box1_community()
{
  Balance_Arm('C');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 375, 'L');
}

void box2_community()
{
  pickCan(5, NO_SWITCH_LR, 'Y'); // GR
  motorStop(); delay(500);
  spinDegree(90);
  motorStop(); delay(500);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 200, 'L');
}

void box3_community()
{ 
  PLACE_SLOPE_SONAR(5, 'l', 'Y'); // Green left
  motorStop(); delay(500);
  spinDegree(90);
  motorStop(); delay(500);
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 375, 'R');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'R');
}

void box4_community()
{
  Switch_right_to_left(100);
  PLACE_SLOPE_SONAR(38, 'l', 'Y'); // Red left
  motorTimeDegree_Enhanced(-30, -60, 200, 'L');
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20);
  delay(500);
  motorTimeDegree_Enhanced(30, 60, 250, 'L');
  SetBack(20);
}

void box5_community()
{
  pickCan(5, NO_SWITCH_LR, 'Y'); // YY
  motorStop(); delay(500);
  spinDegree(90);
  motorStop(); delay(500);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 200, 'L');
}

void box6_community()
{
  PLACE_LOCK_SONAR_ALL(10, 'Y');
  motorStop(); delay(500);
  spinDegree(90);
  motorStop(); delay(500);
  SetBack(20, 200);
  motorTimeDegree_Enhanced(30, 60, 500, 'R');
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 200, 'L');
}

void box7_community()
{
  pickCan(0, NO_SWITCH_LR, 'Y'); // GR
  motorStop(); delay(500);
  spinDegree(90);
  motorStop(); delay(500);
  SetBack(20, 200);
  motorTimeDegree_Enhanced(30, 60, 500, 'R');
  SetBack(20, 225, 'L');
}

void box8_community()
{
  PLACE_SLOPE_SONAR(38, 'r', 'Y'); // Red right
  motorStop(); delay(500);
  spinDegree(90);
  motorStop(); delay(500);
  SetBack(20);
  motorTimeDegree_Enhanced(30, 60, 275, 'R');
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 200, 'L');
}

void box9_community()
{
  Switch_left_to_right(100);
  PLACE_SLOPE_SONAR(5, 'r', 'Y'); // Green right
}

void box10_community()
{

}