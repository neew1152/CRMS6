void operation_community()
{
  // SetBack = 250, SetFront = 400
  // 1 = 200, 1.5 = 275, 3 = 500, Hight Way = 1200 1350
  // ShowValue_Sensor();
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
  home_community();
}
void box1_community()
{
  Balance_Arm('C');
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 250, 'L'); // Face to GY
  motorStop();delay(50);
}

void box2_community()
{
  pickCan(0, NO_SWITCH_LR);
  motorTimeDegree_Enhanced(-30, -60, 25, 'R');
  SetBack(20, 250);
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 500, 'L');
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20, 250, 'R');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 400, 'L'); // Face to green base
  motorStop();delay(50);
}

void box3_community()
{
  placeCan1_NoShake(6, 3.5, 'l', 'l');
  motorStop();delay(250);
  SetBack(20, 250, 'L');
  motorStop(); delay(50);
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 400, 'R');
  motorStop();delay(50);
  SetBack(20);
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 275, 'L');
  motorTimeDegree_Enhanced(30, 60, 200, 'R');
  SetFront(20, 350, 'L'); // Face to yellow base
  motorStop();delay(50);
}

void box4_community()
{
  placeCan1_NoShake(12, 3.5, 'r', 's');
  motorStop();delay(750);
  Balance_Arm('C');
  motorTimeDegree_Enhanced(-30, -60, 50, 'R');
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 250, 'L');
  motorStop();delay(50);
  SetBack(20); // Face to GR
  motorStop();delay(50);
}

void box5_community()
{
  pickCan(5, NO_SWITCH_LR);
  SetBack(20, 250, 'R');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'R');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 250, 'R');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 400, 'L');
  motorStop();delay(50);
  SetBack(20); // Face to green base
  motorStop();delay(50);
}
void box6_community()
{
  placeCan1_NoShake(6, 3.5, 'l');
  motorStop();delay(250);
  SetBack(20, 250, 'L');
  motorStop(); delay(50);
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 400, 'L');
  motorStop();delay(50);
  SetFront(20, 400);
  motorStop();delay(50);
  motorTimeDegree_Enhanced(-30, -60, 900);
  SetBack(20, 250, 'L');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 500);
  lift(10); delay(1000);
  spinDegree(90);
  SetBack(20, 250, 'L');
  motorStop();delay(50); // Face to red base
}

void box7_community()
{
  placeCan1_NoShake(37, 3.5, 'r', 's');
  motorStop();delay(2000);
  Balance_Arm('C');
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20, 250, 'R');
  motorStop();delay(50);
  SetBack(20);
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 250, 'R'); // Behide the Hight way
  motorTimeDegree_Enhanced(-30, -60, 1200);
  SetBack(20, 250, 'L');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20, 400, 'L');
  motorStop();delay(50);
  SetFront(20);
  motorStop();delay(50);
  motorTimeDegree_Enhanced(-30, -60, 275, 'R');
  motorTimeDegree_Enhanced(30, 60, 200, 'R');
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20, 250, 'R');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 550, 'L');
  SetBack(20, 250, 'R'); // Face to RY
  motorStop();delay(50);
}

void box8_community()
{
  pickCan(5, NO_SWITCH_LR);
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20, 250, 'L');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20, 400, 'L');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(-30, -60, 200, 'L');
  motorTimeDegree_Enhanced(30, 60, 200, 'L');
  SetBack(20);
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 250, 'R');
  SetFront(20); // Behide the Hight way 
  motorStop();delay(50);
  motorTimeDegree_Enhanced(-30, -60, 1350, 'R');
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 250, 'L');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 500); // Face to red base
}

void box9_community()
{
  placeCan1_NoShake(37, 3.5, 'l', 's');
  motorStop();delay(2000);
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20, 250, 'R');
  motorStop();delay(50);
  SetBack(20, 250);
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 500, 'R');
  motorTimeDegree_Enhanced(30, 60, 200, 'R');
  SetFront(20, 400, 'L'); // Face to yellow base
  motorStop();delay(50);
}

void home_community()
{
  Switch_right_to_left(100);
  placeCan1_NoShake(12, 3.5, 'l', 's');
  motorStop();delay(750);
  Balance_Arm('C');
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20, 250, 'R');
  motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 200, 'L');
  motorTimeDegree_Enhanced(30, 60, 200, 'L');
  SetFront(20);
  motorStop();delay(50);
  motorTimeDegree_Enhanced(-30, -60, 275);
}
