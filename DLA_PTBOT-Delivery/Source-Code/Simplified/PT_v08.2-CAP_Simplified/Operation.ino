/////////////////////////////////////////////////

// PickCan(5, 60, 275);
// DropCan(5, 'A', 'A', 60, 275);
// SetBack(25, 300); SetFront(25, 350);

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
// High Way | FF(60, 1475);

/////////////////////////////////////////////////

//   Chunks   |
//     1      | FF(40, 700);
//     2      | FF(40, 1210);
//     3      | FF(40, 1720);
//  High Way  | FF(40, 2200); | 1250 & 1175
// Chopsticks | FF(20, 3100);

/////////////////////////////////////////////////

//        IN          |   OUT
// SetFront(25, 350); | SetFront(25, 275);
// SetBack(25, 375);  | SetBack(25, 400);

/////////////////////////////////////////////////

void Operation() {
  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
}

void Mission_1() {
  BB(60, 1175);
  SetBack(25, 350, 'L');
  BalanceArm('C');
  FF(60, 855);
  SetFront(25, 350, 'L');
  BB(60, 535, 'L');
  FF(60, 525, 'L');
  SetBack(25, 350);
  FF(60, 525, 'L');
  SetBack(25, 375);

  FF(60, 1475, 'R');
  BB(60, 855);
  SetBack(25, 375, 'L');
  BB(60, 855);
  SetBack(25, 400, 'R');
  PickCan(5, 60, 275);

  SpinDegree(-90);
  BalanceArm('C');
  FF(60, 855);
  SetFront(25, 400, 'R');
  SetBack(25, 375);
  FF(60, 510, 'L');
  FF(60, 535);
  DropCan(13, 'R', 'A', 60, 275);

  BalanceArm('C');
  BB(60, 535);
  SetBack(25, 400, 'L');
  BB(60, 535, 'L');
  BB(60, 535, 'R');
  BB(60, 500);
  FF(60, 500);
  SetFront(25, 350, 'L');
  BB(60, 535);
  SetBack(25, 325, 'L');
  DropCan(5, 'L', 'A', 60, 275);
}

void Mission_2() {
  SpinDegree(90);
  BalanceArm('C');
  FF(60, 855, 'R');
  FF(60, 515, 'R');
  FF(60, 535, 'R');
  BB(60, 535);
  SetBack(25, 325, 'L');

  PickCan(5, 60, 275);
  SpinDegree(90);
  BalanceArm('C');
  FF(60, 535);
  SetFront(25, 350, 'L');
  BB(60, 535);
  SetBack(25, 400, 'L');
  BB(60, 535, 'L');
  BB(60, 855);
  SetBack(25, 325, 'L');
  DropCan(5, 'R', 'A', 60, 275);

  SpinDegree(90);
  BalanceArm('C');
  SetBack(25, 325);
  FF(60, 1475 + 535);
  SetFront(25, 350, 'L');
  DropCan(10, 'L', 'A', 60, 275);
}

void Mission_3() {
  SpinDegree(90);
  BalanceArm('C');
  BB(60, 1475, 'R');
  BB(60, 535);
  SetBack(25, 300, 'L');
  Lift(6);
  FF(60, 855, 'R');
  SetBack(25, 300, 'L');
  PickCan(0, 60, 300);

  BalanceArm('C');
  BB(60, 855);
  SetBack(25, 400, 'R');
  SetBack(25, 375);
  FF(60, 855, 'R');
  FF(60, 535, 'L');
  SetBack(25, 375, 'R');
  DropCan(13, 'L', 'A', 60, 275);

  BalanceArm('C');
  BB(60, 535);
  SetBack(25, 400, 'L');
  BB(60, 535, 'R');
  BB(60, 1475);
  SetBack(25, 375, 'R');
  DropCan(10, 'R', 'A', 60, 275);
}

void Mission_4() {
  BalanceArm('C');
  BB(60, 535);
  SetBack(25, 300, 'R');
  BB(60, 525, 'R');
  FF(60, 515, 'R');
  BB(60, 855, 'R');
  FF(60, 1100);
}
