void operation_311()
{
  //   1 Chunk        2 Chunks       3 Chunks
  // FF(60, 555); | FF(60, 890); | FF(60, 1225);
  // BB(60, 560); | BB(60, 915); | BB(60, 1255);

  //         IN                  OUT
  //  SetBack(20, 270); | SetBack(20, 290);
  // SetFront(20, 370); | SetFront(20, 490);

  //จะเก็บกระป๋อง SetBack = 275 , SetFront = 300
  //จะวางกระป๋อง SetBack = 250 , SetFront = 300
  // SetFront_Wall(20, 375, 'L');
  // SetFront(20, 375, 'L');
  // SetBack(20, 250, 'R');

  //ด้านหลัง 400คือวาง2ครั้ง 800คือถอยครึ่งบล็อก
  // pickCan(5, NO_SWITCH_LR); delay(500);
  // placeCan1_NoShake(10, 3, 'r', 's');
  // placeCan2_NoShake(10, 3, 's', 's');
  // placeCan1_NoShake_Enhanced('R', 'l', 'c', 30, 800);
  // placeCan2_NoShake_Enhanced('R', 's', 's', 30, 800);

  // spinDegree_Enhanced(90);

  box1_311();
  box2_311();
  box3_311();
  box4_311();
  box5_311();
  home_311();
}

void box1_311()
{
  // SetBack(20, 275, 'R');
  // pickCan_Test(5, NO_SWITCH_LR, 'Y'); // Y G

  SetFront_Wall(20, 300, 'R');
  pickCan_Test(5, NO_SWITCH_LR, 'Y');
  SetBack(20, 200, 'R');
  // spinDegree_Enhanced(90);
  placeCan2_NoShake_Enhanced('G', 'S', 'S', 30, 850);
  // placeCan1_NoShake_Enhanced('G', 'R', 'R', 30, 850);
  SetBack(20, 200, 'L');
  pickCan_Test(5, NO_SWITCH_LR, 'Y');
  SetBack(20, 200, 'R');
  // spinDegree_Enhanced(90);
  placeCan2_NoShake_Enhanced('Y', 'S', 'S', 30, 850);
  // placeCan1_NoShake_Enhanced('Y', 'L', 's', 30, 875);
  SetBack(20, 200, 'L');
  pickCan_Test(5, NO_SWITCH_LR, 'Y');
  SetBack(20, 200, 'R');
  // spinDegree_Enhanced(90);
  placeCan2_NoShake_Enhanced('R', 'S', 'S', 30, 850);
  // placeCan1_NoShake_Enhanced('R', 'R', 'S', 30, 850);
  
  // spinDegree_Enhanced(90);
  // delay(2000);
  // spinDegree_Enhanced(-90);

  // SetFront(20, 375);
  // SetBack(20, 275);

  // FF(60, 1555);
  // BB(60, 1210);

  // pickCan(5, SWITCH_LR); //เขียว เหลือง
  // delay(500);
  // SetBack(20, 250, 'R');
  // placeCan1_NoShake(15, 3, 'l', 's');

  // moveToCan0(30);
  // ShowValue_Distance();
}

void box2_311()
{
  // pickCan(5, NO_SWITCH_LR);
  // delay(500);
  // SetBack(20, 250, 'R');
  // placeCan1_NoShake_Enhanced('R', 'L', 'R');
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