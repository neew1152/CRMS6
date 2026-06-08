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
// High Way | FF(60, 1550);

/////////////////////////////////////////////////

//   Chunks   |
//     1      | FF(40, 700);
//     2      | FF(40, 1210);
//     3      | FF(40, 1720);
//  High Way  | FF(40, 2200); | 1250 & 1175
// Chopsticks | FF(20, 3100);

/////////////////////////////////////////////////

//        IN          |   OUT
// SetFront(25, 300); | SetFront(25, 350);
// SetBack(25, 300);  | SetBack(25, 350);

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
  SetBack(25, 300, 'L');
  FF(60, 855);
  SetFront(25, 350, 'L');
  BB(60, 500, 'L');
  FF(60, 525, 'L');
  FF(60, 535, 'L');
  SetBack(25, 275, 'R');

  PickCan(0, 60, 300);
  SpinDegree(90);
  BalanceArm('C');
  BB(60, 1550, 'R');
  BB(60, 535);
  SetBack(25, 275, 'L');
  FF(60, 855);
  DropCan(5, 'R', 'C', 60, 275);

  BalanceArm('C');
  BB(60, 855, 'R');
  FF(60, 840, 'R');
  FF(60, 535, 'L');
  SetBack(25, 175, 'R');
  DropCan(10, 'L', 'C', 60, 275);
}

void Mission_2() {
  SpinDegree(90);
  BB(60, 535);
  SetBack(25, 275, 'L');
  PickCan(5, 60, 275);

  SpinDegree(90);
  BalanceArm('C');
  FF(60, 535, 'R');
  FF(60, 535, 'L');
  BB(60, 535);
  SetBack(25, 300, 'L');
  BB(60, 855);
  SetBack(25, 350, 'R');
  DropCan(13, 'A', 'A', 60, 275);
}

void Mission_3() {
  BalanceArm('C');
  SpinDegree(-90);
  FF(60, 855);
  SetFront(25, 300, 'R');
  SetBack(25, 300);
  FF(60, 855, 'R');
  BB(60, 855, 'L');
  FF(60, 500);
  BB(60, 500, 'R');
  SetBack(25, 300);
  FF(60, 535, 'L');
  SetBack(25, 300);
  PickCan(5, 60, 275);

  SpinDegree(-90);
  BalanceArm('C');
  BB(60, 535, 'L');
  BB(60, 535);
  SetBack(25, 275, 'L');
  FF(60, 855);
  DropCan(5, 'R', 'R', 60, 275);

  BalanceArm('C');
  BB(60, 855, 'R');
  FF(60, 855, 'R');
  FF(60, 535, 'L');
  SetBack(25, 175, 'R');
  DropCan(10, 'L', 'L', 60, 275);
}

void Mission_4() {
  BalanceArm('C');
  BB(60, 535);
  SetBack(25, 410, 'R');
  FF(60, 1550 + 260);
  SetFront(25, 350, 'R');

  BB(60, 535);
  SetBack(25, 300, 'R');
  BB(60, 525, 'R');
  FF(60, 515, 'R');
  BB(60, 855, 'R');
  FF(60, 1100);
}