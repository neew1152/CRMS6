/////////////////////////////////////////////////

// PickCan(5, 60, 275);
// DropCan(5, 'A', 'A', 60, 275);

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
//  High Way  | FF(40, 2200); | 1250 & 1175
// Chopsticks | FF(20, 3100);

/////////////////////////////////////////////////

//        IN          |   OUT
// SetFront(25, 300); | SetFront(25, 340);
// SetBack(25, 350);  | SetBack(25, 410);

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
  SetBack(25, 350, 'L');
  FF(60, 825, 'L');
  BB(60, 545, 'L');
  FF(60, 535);
  SetFront(25, 300, 'L');
  SetBack(25, 350);
  FF(60, 535);
  PickCan(5, 60, 275);

  SpinDegree(90);
  BalanceArm('C');
  BB(60, 1575 + 535);
  SetBack(25, 100, 'L');
  DropCan(10, 'R', 'C', 60, 300);

  SpinDegree(90);
  FF(60, 535, 'R');
  BB(60, 535);
  FF(60, 535);
  SetFront(25, 350, 'R');
  BalanceArm('W');
  BB(60, 530, 'R');
  BB(60, 855);
  SetBack(25, 410, 'L');
  BB(60, 855);
  SetBack(25, 410, 'R');
  DropCan(13, 'L', 'C', 60, 300);
}

void Mission_2() {
  SetBack(25, 350, 'L');
  BalanceArm('C');
  FF(60, 855);
  SetFront(25, 300, 'L');
  BB(60, 1175);
  SetBack(25, 200, 'L');
  FF(60, 855);
  PickCan(5, 60, 300);

  BB(60, 855);
  SetBack(25, 390, 'R');
  BalanceArm('W');
  FF(60, 1175);
  SetFront(25, 300, 'R');
  BB(60, 855);
  SetBack(25, 390, 'R');
  DropCan(13, 'L', 'L', 60, 300);

  SetBack(25, 350, 'L');
  BalanceArm('W');
  FF(60, 855);
  SetFront(25, 300, 'L');
  BB(60, 500, 'R');
  FF(60, 535);
  DropCan(5, 'R', 'R', 60, 300);
}

void Mission_3() {
  SpinDegree(90);
  BB(60, 535);
  SetBack(25, 350, 'L');
  PickCan(0, 60, 350);

  SpinDegree(90);
  FF(60, 535);
  SetFront(25, 300, 'L');
  DropCan(5, 'L', 'L', 60, 300);

  BalanceArm('C');
  BB(60, 535);
  SetBack(25, 410, 'R');
  FF(60, 535, 'R');
  BB(60, 855);
  SetBack(25, 300, 'L');
  DropCan(10, 'R', 'A', 60, 275);
}

void Mission_4() {
  BalanceArm('C');
  SpinDegree(90);
  SetBack(25, 300);
  FF(60, 1575 + 535);
  SetFront(25, 300, 'L');
  BB(60, 535);
  SetBack(25, 350, 'R');
  BB(60, 515, 'R');
  FF(60, 515, 'R');
  BB(60, 855, 'R');
  FF(60, 1100);
}