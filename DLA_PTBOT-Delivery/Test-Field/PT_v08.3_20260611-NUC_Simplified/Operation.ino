/////////////////////////////////////////////////

// PickCan(5, 60, 225);
// DropCan(5, 'A', 'A', 60, 200);

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
// SetFront(25, 225); | SetFront(25, 300);
// SetBack(25, 275);  | SetBack(25, 350);

// SetBack(25, 275);
// FF(60, 855, 'R');

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
  SetBack(25, 275, 'L');
  FF(60, 855);
  SetFront(25, 325, 'L');
  BB(60, 535, 'L');
  FF(60, 535);
  SetFront(25, 325, 'L');
  FF(60, 535);
  PickCan(5, 60, 225);  // GR

  SpinDegree(90);
  BalanceArm('C');
  SetFront(25, 250);
  BB(60, 1550, 'R');
  BB(60, 535);
  SetBack(25, 175, 'L');
  FF(60, 855);
  DropCan(13, 'R', 'C', 60, 200);  // RC

  BalanceArm('C');
  BB(60, 855);
  SetBack(25, 275, 'R');
  SetBack(25, 275);
  FF(60, 855, 'R');
  FF(60, 535, 'R');
  BB(60, 535);
  SetBack(25, 275, 'L');
  DropCan(5, 'L', 'A', 60, 200);  // GL
}

void Mission_2() {
  SpinDegree(90);
  FF(60, 535);
  SetFront(25, 325, 'L');
  PickCan(0, 60, 225);  // YR

  BalanceArm('C');
  BB(60, 535);
  SetBack(25, 275, 'L');
  BB(60, 855);
  SetBack(25, 275, 'L');
  FF(60, 855);
  DropCan(13, 'R', 'A', 60, 200);  // RR

  BalanceArm('C');
  BB(60, 855);
  SetBack(25, 275, 'R');
  SetBack(25, 275);
  FF(60, 535, 'L');
  BB(60, 855);
  SetBack(25, 350, 'L');
  DropCan(10, 'L', 'C', 60, 200);  // YC
}

void Mission_3() {
  BalanceArm('C');
  SpinDegree(90);
  FF(60, 535, 'R');
  BB(60, 500);
  FF(60, 500);
  SetFront(25, 325, 'L');
  FF(60, 535, 'L');
  BB(60, 855);
  SetBack(25, 275, 'L');
  BB(60, 855);
  SetBack(25, 350, 'R');
  PickCan(5, 60, 225);  // YG

  BalanceArm('C');
  SpinDegree(-90);
  FF(60, 855);
  SetFront(25, 325, 'R');
  SetBack(25, 275);
  FF(60, 535, 'L');
  FF(60, 535, 'R');
  BB(60, 535);
  SetBack(25, 275, 'L');
  DropCan(5, 'R', 'A', 60, 200);  // GR

  BalanceArm('C');
  SpinDegree(90);
  FF(60, 535);
  SetFront(25, 325, 'L');
  BB(60, 535);
  SetBack(25, 275, 'L');
  BB(60, 535, 'L');
  BB(60, 855);
  SetBack(25, 275, 'L');
  DropCan(10, 'L', 'A', 60, 200);
}

void Mission_4() {
  BalanceArm('C');
  SpinDegree(-90);
  BB(60, 535 + 1550);
  SetBack(25, 275, 'L');
  FF(60, 500);
  SetFront(25, 325, 'L');
  BB(60, 535, 'R');
  FF(60, 535, 'R');
  BB(60, 855, 'R');
  FF(60, 1150);
}