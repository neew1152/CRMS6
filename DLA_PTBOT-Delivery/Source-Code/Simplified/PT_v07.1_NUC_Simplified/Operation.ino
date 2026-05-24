/////////////////////////////////////////////////

// PickCan(5, 60, 325);
// DropCan(5, 'A', 'A', 60, 300);

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
// SetFront(25, 300); | SetFront(25, 340);
// SetBack(25, 375);  | SetBack(25, 410);

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
  SetBack(25, 375, 'L');
  FF(60, 855);
  SetFront(25, 340, 'L');
  BB(60, 535, 'L');
  FF(60, 535, 'L');
  FF(60, 535, 'R');

  BB(40, 1250, 'L');
  BB(40, 1200);
  SetBack(25, 375, 'L');
  FF(60, 855, 'R');
  FF(60, 535, 'L');
  SetBack(25, 410);
  FF(60, 535, 'L');
  SetBack(25, 350, 'R');
  PickCan(0, 60, 325);

  SpinDegree(90);
  BB(60, 535);
  SetBack(25, 275, 'L');
  DropCan(13, 'R', 'C', 60, 300);

  BalanceArm('W');
  SpinDegree(90);
  FF(60, 535);
  SetFront(25, 325, 'R');
  FF(60, 535, 'L');
  FF(60, 535, 'R');
  BB(60, 855);
  SetBack(25, 325, 'L');
  DropCan(10, 'L', 'A', 60, 300);
}

void Mission_2() {
  SetBack(25, 410, 'R');
  SetBack(25, 375);
  FF(60, 855);
  PickCan(5, 60, 325);

  BB(60, 855);
  SetBack(25, 325, 'L');
  DropCan(10, 'R', 'A', 60, 300);

  BalanceArm('W');
  SetBack(25, 410, 'R');
  FF(60, 855, 'L');
  BB(60, 855);
  SetBack(25, 375, 'L');
  BB(60, 855);
  SetBack(25, 410, 'R');
  FF(40, 1250, 'L');
  BB(40, 1200);
  SetBack(25, 375, 'R');
  DropCan(5, 'L', 'C', 60, 300);
}

void Mission_3() {
  BalanceArm('C');
  SpinDegree(90);
  SetFront(25, 300);
  BB(40, 1250, 'L');
  BB(40, 1200);
  SetBack(25, 375, 'L');
  FF(60, 855);
  SetFront(25, 325, 'L');
  BB(60, 1175);
  SetBack(25, 375, 'L');
  FF(60, 855);
  PickCan(5, 60, 325);

  BB(60, 855);
  SetBack(25, 410, 'R');
  SetBack(25, 325);
  FF(60, 855, 'R');
  FF(60, 535, 'R');
  BB(60, 535);
  SetBack(25, 275, 'L');
  DropCan(13, 'R', 'R', 60, 300);

  BalanceArm('W');
  SpinDegree(90);
  FF(60, 535);
  SetFront(25, 325, 'R');
  FF(60, 535, 'L');
  BB(60, 535);
  SetBack(25, 375, 'L');
  BB(60, 855);
  SetBack(25, 375, 'R');
  FF(40, 1250, 'L');
  BB(40, 1200);
  SetBack(25, 375, 'R');
  DropCan(5, 'L', 'L', 60, 300);
}

void Mission_4() {
  BalanceArm('C');
  BB(60, 535);
  SetBack(25, 375, 'R');
  BB(60, 535, 'R');
  FF(60, 535, 'R');
  BB(60, 855, 'R');
  FF(60, 1175);
}