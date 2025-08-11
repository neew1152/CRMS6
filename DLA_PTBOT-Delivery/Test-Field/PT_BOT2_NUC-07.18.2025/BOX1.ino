void operation_community()
{
  // 2 = 200, 2.5 = 250, 3 = 500, 4 = 850, Hight Way = 1300 1400
  //      IN             OUT
  // SetFront = 400, SetFront = 425
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
  box10_community();
}
void box1_community()
{
  SetBack(20, 200, 'L');
}

void box2_community()
{
  pickCan(5, NO_SWITCH_LR, 'Y'); // RY
  spinDegree(90);
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'R');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'R');
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20, 200, 'L');
}

void box3_community()
{ 
  PLACE_SLOPE_SONAR(12, 'r', 'Y'); // Yellow right base
  spinDegree(90);
  SetBack(20);
  motorTimeDegree_Enhanced(30, 60, 225, 'L');
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20, 250, 'L');
}

void box4_community()
{
  PLACE_SLOPE_SONAR(37, 'l', 'Y'); // Red left base
  spinDegree(90);
  SetBack(20);
  motorTimeDegree_Enhanced(30, 60, 250, 'L');
  SetBack(20);
}

void box5_community()
{
  pickCan(0, NO_SWITCH_LR, 'Y'); // GR
  SetBack(20, 200, 'R');
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 200, 'L');
}

void box6_community()
{
  PLACE_SLOPE_SONAR(37, 'r', 'Y'); // Red right base
  spinDegree(90);
  SetBack(20, 200);
  motorTimeDegree_Enhanced(30, 60, 500, 'R');
  motorTimeDegree_Enhanced(30, 60, 200, 'R');
  SetBack(20);
  motorTimeDegree_Enhanced(30, 60, 275, 'L');
  SetBack(20, 200, 'R');
}

void box7_community()
{
  PLACE_SLOPE_SONAR(5, 'l', 'Y');  // Green Left base
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 200, 'L');
}

void box8_community()
{
  pickCan(5, NO_SWITCH_LR, 'Y'); // GY
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20, 200, 'L');
}

void box9_community()
{
  PLACE_CENTER_SONAR(12, 'r', 'Y');  // Yellow left base
  SetBack(20, 200, 'R');
  SetBack(20, 200);
  motorTimeDegree_Enhanced(30, 60, 500, 'R');
  SetBack(20);
  motorTimeDegree_Enhanced(30, 60, 250, 'L');
  SetBack(20, 200, 'R');
}

void box10_community()
{
  Switch_left_to_right(100);
  PLACE_SLOPE_SONAR(5, 'r', 'Y'); // Green right base
  spinDegree(90);
  motorTimeDegree_Enhanced(-30, -60, 200);
}

void operation_311()
{
  // SetBack = 250, SetFront = 400
  // 1 = 200, 1.5 = 275, 3 = 500, Hight Way = 1300 1400
  // ShowValue_Sensor();
  // motorStop(); delay(8000);
  box1_311();
  box2_311();
  box3_311();
  box4_311();
  box5_311();
  home_311();
}

void box1_311()
{

}

void box2_311()
{
  
}

void box3_311()
{
  
}

void box4_311()
{
  
}

void box5_311()
{
  
}

void home_311()
{
  
}

