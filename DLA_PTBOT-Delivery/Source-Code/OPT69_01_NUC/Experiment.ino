void Experiment() {
  //   1 Chunk        2 Chunks       3 Chunks
  // FF(60, 555); | FF(60, 890); | FF(60, 1225);
  // BB(60, 555); | BB(60, 915); | BB(60, 1255);

  // placeCan1_NoShake_Enhanced - 255
  //         IN                  OUT
  //  SetBack(20, 270); | SetBack(20, 290);
  // SetFront(20, 370); | SetFront(20, 490);

  Lab_1();
  Lab_2();
  // Lab_3();
  // Lab_4();
}
void Lab_1() {
  FF(60, 555);
  SetFront(20, 370, 'L');
  FF(60, 555);
  SetFront_Wall(20, 370, 'L');
  pickCan_Test(5, NO_SWITCH_LR, 'Y');

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
  pickCan_Test(5, NO_SWITCH_LR, 'Y');

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
  pickCan_Test(0, NO_SWITCH_LR, 'Y');

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

void Lab_5() {

}

void Lab_6() {

}

void Lab_7() {

}

void Lab_8() {

}

void Lab_9() {
}

void Lab_10() {
}




void community() {
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

  commu1();
  commu2();
  commu3();
  commu4();
  commu5();
  commu6();
  commu7();
  commu8();
  commu9();
  commu10();
}

void commu1() {
  FF(60, 840, 'L');
  SetFront_Wall(20, 300, 'L');
  pickCan_Test(5, NO_SWITCH_LR, 'Y'); // Y G
}

void commu2() {
  spinDegree_Enhanced(-90);
  FF(60, 500, 'L');
  BB(60, 865);
  SetBack(20, 275, 'L');
  placeCan1_NoShake_Enhanced('G', 'R', 'C', 30, 825);
}

void commu3() {
  spinDegree_Enhanced(90);
  FF(60, 520, 'R');
  FF(60, 500);
  SetFront(20, 400, 'R');
  placeCan1_NoShake_Enhanced('Y', 'L', 'C', 30, 800);
}

void commu4() {
  spinDegree_Enhanced(90);
  SetBack(20, 275, 'R');
  pickCan_Test(5, NO_SWITCH_LR, 'Y'); // R G
}

void commu5() {
  spinDegree_Enhanced(-90);
  SetBack(20, 300);
  FF(60, 490, 'R');
  BB(60, 520);
  SetBack(20, 300, 'L');
  placeCan1_NoShake_Enhanced('G', 'R', 'R', 30, 800);
}

void commu6() {
  spinDegree_Enhanced(90);
  FF(60, 1210);
  SetFront_Wall(20, 300, 'L');
  placeCan1_NoShake_Enhanced('R', 'L', 'C', 30, 1500);
}

void commu7() {
  spinDegree_Enhanced(90);
  SetFront_Wall(20, 300, 'R');
  pickCan_Test(0, NO_SWITCH_LR, 'Y'); // G R
}

void commu8() {
  BB(60, 500, 'L');
  SetFront_Wall(20, 300, 'L');
  placeCan1_NoShake_Enhanced('R', 'R', 'R', 30, 800);
}

void commu9() {
  spinDegree_Enhanced(-90);
  SetBack(20, 300);
  FF(60, 865, 'L');
  FF(60, 520, 'R');
  placeCan1_NoShake_Enhanced('Y', 'L', 'L', 30, 800);
}

void commu10() {
  
}
