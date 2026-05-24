/////////////////////////////////////////////////

// PickCan(5, 60, 200);
// placeCan(5, 300, 'A', 'A', 60, 200);

/////////////////////////////////////////////////

// Block
// G = 5
// Y = 10
// R = 13

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
// SetBack(25, 400);  | SetBack(25, 435);

/////////////////////////////////////////////////

void Operation() {
  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
}

void Mission_1() {
  BalanceArm('C');
  BB(60, 1175);
  SetBack(25, 400, 'L');
  FF(60, 855, 'L');
  BB(60, 535, 'L');
  FF(60, 535, 'L');
  SetBack(25, 400);
  FF(60, 515, 'R');
  SetFront(25, 365);

  BB(60, 1575, 'R');
  BB(60, 535);
  SetBack(25, 350, 'L');
  FF(60, 855);

  PickCan(5, 60, 200);
  BB(60, 855);
  SetBack(25, 350, 'R');
  SetBack(25, 400);
  FF(60, 500, 'L');
  BB(60, 535, 'R');
  BB(60, 450);
  FF(60, 400, 'L');
  BB(60, 535);
  SetBack(25, 200, 'L');
  PlaceCan(5, 300, 'R', 'C', 60, 200);

  spinDegree(90);
  SetBack(25, 400);
  BalanceArm('W');
  FF(60, 855 + 1300);
  SetFront(25, 325, 'L');
  PlaceCan(13, 300, 'L', 'C', 60, 200);
}

void Mission_2() {
  BalanceArm('C');
  spinDegree(90);
  SetFront(25, 325);
  BB(60, 1575, 'R');
  FF(60, 535, 'R');
  FF(60, 535);
  PickCan(5, 60, 200);

  spinDegree(90);
  BB(60, 535);
  SetBack(25, 200, 'L');
  PlaceCan(10, 300, 'L', 'L', 60, 200);

  spinDegree(90);
  FF(60, 535);
  SetFront(25, 325, 'R');
  FF(60, 535, 'L');
  FF(60, 535, 'R');
  BB(60, 855);
  SetBack(25, 200, 'L');
  PlaceCan(5, 300, 'R', 'R', 60, 200);
}

void Mission_3() {
  spinDegree(90);
  SetBack(25, 400);
  BalanceArm('C');
  FF(60, 840, 'L');
  BB(60, 855);
  SetBack(25, 400, 'R');
  FF(60, 855);
  SetFront(25, 365, 'L');
  PickCan(5, 60, 200);

  SetBack(25, 300, 'L');
  FF(60, 855, 'R');
  FF(60, 500, 'L');
  FF(60, 535, 'R');
  BB(60, 535);
  SetBack(25, 200, 'L');
  PlaceCan(10, 300, 'R', 'R', 60, 200);

  spinDegree(90);
  BalanceArm('W');
  FF(60, 535);
  SetFront(25, 325, 'R');
  FF(60, 535);
  SetFront(25, 325, 'L');
  FF(60, 535, 'R');
  FF(60, 1575);
  SetFront(25, 325, 'L');
  PlaceCan(13, 300, 'L', 'L', 60, 200);
}

void Mission_4() {
  BalanceArm('W');
  BB(60, 535);
  SetBack(25, 400, 'R');
  BB(60, 535, 'R');
  FF(60, 535, 'R');
  BB(60, 855, 'R');
  FF(60, 1175);
}