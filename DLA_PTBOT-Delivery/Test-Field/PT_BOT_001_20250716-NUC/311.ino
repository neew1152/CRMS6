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






























void cans() {
  // Back = 250, Front = 400
  // 1 = 200, 1.5 = 275, 3 = 500, Hight Way = 1300 1400
  // ShowValue_Sensor();

  // BOX1 Red - Yellow
  Balance_Arm('C');
  motorTimeDegree_Enhanced(30, 60, 500, 'L');
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 400, 'L');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 250, 'R');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 200, 'L');
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 200);

  pickCan(5, NO_SWITCH_LR);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 250, 'R');
  motorStop(); delay(100);
  placeCan1_NoShake(14, 5, 'l'); // yellow cen
  motorStop(); delay(500);

  // BOX2
  motorTimeDegree_Enhanced(-30, -60, 350, 'L');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop(); delay(100);
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 400, 'R');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 250, 'L');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 200, 'R');
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 275);
  SetFront(20, 400, 'L');
  motorStop(); delay(100);
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 275, 'R');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop(); delay(100);
  placeCan1_NoShake(37, 5, 'r');
  motorStop(); delay(2000);

  // BOX3 Yellow - Red
  Balance_Arm('C');
  motorTimeDegree_Enhanced(-30, -60, 250);
  SetBack(20, 250, 'R');
  motorStop(); delay(100);
  SetBack(20);
  motorStop(); delay(100);

  pickCan(0, NO_SWITCH_LR);
  motorTimeDegree_Enhanced(-30, -60, 50);
  SetBack(20, 250, 'L');
  motorStop(); delay(100);
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 275, 'L');
  motorTimeDegree_Enhanced(30, 60, 200, 'L');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop(); delay(100);
  SetFront(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(-30, -60, 275);
  SetBack(20, 250, 'L');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(-30, -60, 200, 'R');
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 275, 'R');
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 275, 'R');
  SetBack(20);
  motorStop(); delay(100);
  placeCan1_NoShake(5, 5, 'r');
  motorStop(); delay(500);

  // BOX4
  motorTimeDegree_Enhanced(-30, -60, 50);
  SetBack(20, 250, 'L');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 250, 'R');
  motorTimeDegree_Enhanced(30, 60, 200);
  placeCan1_NoShake(14, 5, 'l', 'l');
  motorStop(); delay(1000);

  // BOX5
  Balance_Arm('C');
  motorTimeDegree_Enhanced(-30, -60, 350, 'L');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop(); delay(100);
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 400, 'R');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 250, 'L');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 400);

  pickCan(5, NO_SWITCH_LR);
  motorTimeDegree_Enhanced(-30, -60, 325, 'R');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop(); delay(100);
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 275, 'R');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop(); delay(100);
  placeCan1_NoShake(37, 5, 'r', 'r');
  motorStop(); delay(2000);

  // BOX6
  motorTimeDegree_Enhanced(-30, -60, 50, 'L');
  motorTimeDegree_Enhanced(30, 60, 200, 'L');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop(); delay(100);
  SetFront(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(-30, -60, 275);
  SetBack(20, 250, 'L');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(-30, -60, 200, 'R');
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 275, 'R');
  SetBack(20);
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 275, 'R');
  SetBack(20);
  motorStop(); delay(100);
  placeCan1_NoShake(14, 5, 'l', 'l');
  motorStop(); delay(500);

  // HOME
  Balance_Arm('C');
  motorTimeDegree_Enhanced(-30, -60, 50, 'R');
  SetFront(20, 400, 'R');
  motorStop(); delay(100);
  motorTimeDegree_Enhanced(30, 60, 500);
}