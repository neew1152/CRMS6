void Operation() {
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

  Mission_1();
}

void Mission_1() {
  // SetBack(20, 275, 'R');
  // pickCan_Test(5, NO_SWITCH_LR, 'Y'); // Y G

  SetFront_Wall(20, 300, 'L');
  pickCan_Test(5, NO_SWITCH_LR, 20, 500);
  SetBack(20, 200, 'L');
  // spinDegree_Enhanced(90);
  // placeCan2_NoShake_Enhanced('G', 'S', 'S', 30, 850);
  // placeCan1_NoShake_Enhanced('G', 'R', 'R', 30, 850);
  // SetBack(20, 200, 'L');
  // pickCan_Test(5, NO_SWITCH_LR, 20, 500);
  // SetBack(20, 200, 'R');
  // spinDegree_Enhanced(90);
  // placeCan2_NoShake_Enhanced('Y', 'S', 'S', 30, 850);
  // placeCan1_NoShake_Enhanced('Y', 'L', 's', 30, 875);
  // SetBack(20, 200, 'L');
  // pickCan_Test(5, NO_SWITCH_LR, 20, 500);
  // SetBack(20, 200, 'R');
  // spinDegree_Enhanced(90);
  // placeCan2_NoShake_Enhanced('R', 'S', 'S', 30, 850);
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