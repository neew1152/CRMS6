/////////////////////////////////////////////////

// PickCan(5, 60, 325);
// placeCan(5, 'A', 'A', 60, 200);

/////////////////////////////////////////////////

//  Chunks  |
//    1     | FF(100, 425);
//    2     | FF(100, 630);
//    3     | FF(100, 840);

/////////////////////////////////////////////////

//  Chunks  |
//    1     | FF(60, 535);
//    2     | FF(60, 855);
//    3     | FF(60, 1175);
// High Way | FF(60, 1575);

/////////////////////////////////////////////////

//   Chunks   |
//     1      | FF(40, 700);
//     2      | FF(40, 1210);
//     3      | FF(40, 1720);
//  High Way  | FF(40, 2200); | 1250 & 1200
// Chopsticks | FF(20, 3100);

/////////////////////////////////////////////////

//        IN          |   OUT
// SetFront(25, 325); | SetFront(25, 365);
// SetBack(25, 375);  | SetBack(25, 410);

/////////////////////////////////////////////////

void Operation() {
  Mission_1();
  // Mission_2();
  // Mission_3();
  // Mission_4();
}

void Mission_1() {
  BalanceArm('C');
  BB(60, 1175);
  SetBack(25, 375, 'L');
  FF(60, 855, 'L');
  BB(60, 535, 'L');
  FF(60, 535);
  SetFront(25, 325, 'L');
  FF(60, 535);

  PickCan(5, 60, 325);
  spinDegree(90);
  BalanceArm('W');
  BB(60, 1575, 'R');
  BB(60, 535);
  SetBack(25, 375, 'L');
  FF(60, 855);
  PlaceCan(13, 'L', 'C', 60, 325);

  BB(60, 855, 'R');
  SetBack(25, 375);
  FF(60, 855, 'R');
  SetBack(25, 410);
  FF(60, 535);
  PlaceCan(5, 'R', 'R', 60, 325);
}

void Mission_2() {
  spinDegree(90);
  BB(60, 535);
  SetBack(25, 350, 'L');

  PickCan(0, 60, 325);
  SetBack(25, 435, 'R');
  FF(60, 535, 'L');
  BB(60, 535);
  SetBack(25, 410, 'L');
  BB(60, 885);
  SetBack(25, 375, 'L');
  FF(60, 855);
  PlaceCan(13, 'L', 'L', 60, 325);

  BB(60, 855, 'R');
  SetBack(25, 375);
  FF(60, 1175);
  BalanceArm('W');
  SetFront(25, 325, 'L');
  FF(60, 855);
  SetFront(25, 365, 'L');
  PlaceCan(10, 'R', 'C', 60, 325);
}

void Mission_3() {
  BalanceArm('C');
  SetBack(25, 375, 'L');
  FF(60, 855);
  SetFront(25, 325, 'R');
  FF(60, 855, 'L');
  FF(60, 535, 'R');
  SetBack(25, 375);

  PickCan(5, 60, 325);
  SetBack(25, 375, 'L');
  BB(60, 535, 'R');
  BB(60, 855);
  SetBack(25, 325, 'R');
  FF(60, 855);
  SetFront(25, 365, 'L');
  PlaceCan(10, 'R', 'R', 60, 325);

  spinDegree(-90);
  FF(60, 855, 'R');
  SetBack(25, 325);
  FF(60, 535, 'L');
  SetBack(25, 325);
  FF(60, 535);
  PlaceCan(5, 'L', 'L', 60, 325);
}

void Mission_4() {
  BalanceArm('C');
  BB(60, 535);
  SetBack(25, 410, 'R');
  FF(60, 535, 'L');
  //
  BB(60, 535);
  SetBack(25, 375, 'R');
  BB(60, 535, 'R');
  FF(60, 535, 'R');
  BB(60, 855, 'R');
  FF(60, 1175);
}