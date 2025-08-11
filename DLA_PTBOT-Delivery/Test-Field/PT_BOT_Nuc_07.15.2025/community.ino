void operation_community()
{
  // SetBack = 250, SetFront = 400
  // 1 = 200, 1.5 = 275, 3 = 500, Hight Way = 1300 1400
  // ShowValue_Sensor();
  // motorStop(); delay(8000);
  // box1_community();
  // box2_community();
  // box3_community();
  // box4_community();
  box5_community();
  box6_community();
  // home_community();
}
void box1_community()
{
  Balance_Arm('C');
  motorTimeDegree_Enhanced(30, 60, 200);SetFront(20,400,'R');motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 200,'L');SetBack(20,250);motorStop();delay(50);
  motorTimeDegree_Enhanced(30, 60, 200,'R');
  motorTimeDegree_Enhanced(-30, -60, 150);SetBack(20,225,'L');motorStop();delay(50);SetBack(20,250);
  motorStop();delay(50);
}

void box2_community()
{
  pickCan(0, NO_SWITCH_LR);
  motorTimeDegree_Enhanced(-30, -60, 50);
  SetBack(20,250,'R');
  motorStop(); delay(50);
  motorTimeDegree_Enhanced(30, 60, 200);
  SetFront(20,400,'L');
  motorStop();delay(50);
  
}

void box3_community()
{
  placeCan1_NoShake(5, 5, 'r');
  motorStop();delay(250);
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20,250,'R');
  motorStop(); delay(50);
}

void box4_community()
{
  motorTimeDegree_Enhanced(30, 60, 200,'R');
  motorTimeDegree_Enhanced(-30, -60, 500);
  SetBack(20,250,'L');
  motorStop(); delay(50);
  placeCan1_NoShake(37, 5, 'l','s');

}

void box5_community()
{
  motorTimeDegree_Enhanced(-30, -60, 50, 'R');
  SetBack(20);
  motorStop(); delay(50);
  motorTimeDegree_Enhanced(30, 60, 275,'L');
  SetBack(20);
  motorStop(); delay(50);
  pickCan(5, NO_SWITCH_LR);
  SetBack(20,250,'R');
  motorStop(); delay(50);
}
void box6_community()
{
  motorTimeDegree_Enhanced(-30, -60, 200);
  SetBack(20,250,'L');
  motorStop(); delay(50);
  placeCan1_NoShake(37, 5, 'l');
  motorStop(); delay(2000);
  motorTimeDegree_Enhanced(-30, -60, 50, 'R');
  SetBack(20,250);
  motorStop(); delay(50);
  motorTimeDegree_Enhanced(30, 60, 500,'L');

  motorTimeDegree_Enhanced(-30, -60, 500,'R');
  SetBack(20,250);
  motorStop(); delay(50);
  motorTimeDegree_Enhanced(30, 60, 500);
  SetFront(20,400,'L');motorStop();delay(50);
  SetBack(20,250);
  motorStop(); delay(50);
  placeCan1_NoShake(37, 5, 'r','s');
  
}
void home_community()
{
  
}
