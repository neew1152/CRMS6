void Experiment() {
  //   1 Chunk        2 Chunks       3 Chunks
  // FF(60, 555); | FF(60, 890); | FF(60, 1225);
  // BB(60, 555); | BB(60, 915); | BB(60, 1255);

  // placeCan1_NoShake_Enhanced - 255
  //         IN                  OUT
  //  SetBack(20, 270); | SetBack(20, 290);
  // SetFront(20, 370); | SetFront(20, 490);

  Lab_1();
  // Lab_2();
  // Lab_3();
  // Lab_4();
}
void Lab_1() {
  FF(60, 555);
  SetFront(20, 370, 'L');
  FF(60, 555);
  SetFront_Wall(20, 370, 'L');
  // pickCan_Test(5, NO_SWITCH_LR, 'Y');

  spinDegree_Enhanced(-90);
  SetBack(20, 270);
  FF(60, 890);
  placeCan1_NoShake_Enhanced('R', 'R', 'C', 60, 1000);

  SetBack(20, 270, 'R');
  BB(60, 540, 'L');
  FF(60, 555, 'L');
  FF(60, 555);
  SetFront_Wall(20, 370, 'L');
  placeCan1_NoShake_Enhanced('G', 'L', 'L', 60, 555);
}

void Lab_2() {
  spinDegree_Enhanced(-180);
  // pickCan_Test(5, NO_SWITCH_LR, 'Y');

  spinDegree_Enhanced(90);
  FF(60, 555);
  SetFront(20, 370, 'L');
  placeCan1_NoShake_Enhanced('Y', 'L', 'C', 60, 915);

  SetBack(20, 270, 'R');
  FF(60, 555, 'L');
  SetBack(20, 270);
  FF(60, 555);
  placeCan1_NoShake_Enhanced('R', 'R', 'R', 60, 555);
}

void Lab_3() {
  spinDegree_Enhanced(90);
  FF(60, 555);
  SetFront_Wall(20, 370, 'L');
  SetBack(20, 270);
  // pickCan_Test(0, NO_SWITCH_LR, 'Y');

  SetBack(20, 270, 'R');
  SetFront_Wall(20, 370);
  BB(60, 555, 'R');
  FF(60, 890);
  SetFront_Wall(20, 370, 'R');
  FF(60, 555, 'R');
  SetBack(20, 270);
  FF(60, 555);
  placeCan1_NoShake_Enhanced('Y', 'L', 'L', 60, 555);

  spinDegree_Enhanced(-90);
  FF(60, 555);
  SetFront_Wall(20, 370, 'L');
  placeCan1_NoShake_Enhanced('G', 'R', 'R', 60, 555);
}

void Lab_4() {
  spinDegree_Enhanced(-90);
  FF(20, 555);
  SetFront_Wall(20, 370, 'L');
  BB(60, 555);
  SetBack(20, 270, 'R');
  FF(60, 555, 'L');
  SetBack(20, 270);
  FF(60, 555, 'R');
  FF(60, 555);
}