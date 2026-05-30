/////////////////////////////////////////////////

// PickCan(5, 60, 300);
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
  FF(60, 835, 'L');
  BB(60, 545, 'L');
  FF(60, 535);
  SetFront(25, 300, 'L');
  SetBack(25, 350);
  FF(60, 535);
  PickCan(5, 60, 285);

  SpinDegree(90);
  BalanceArm('W');
  BB(60, 1575 + 535);
  SetBack(25, 300, 'L');
  DropCan(5, 'R', 'C', 60, 250);

  SpinDegree(90);
  FF(60, 535, 'R');
  BB(60, 535);
  FF(60, 535);
  SetFront(25, 350, 'R');
  BB(60, 545, 'L');
  BB(60, 535);
  SetBack(25, 350, 'L');
  SetBack(25, 410);
  BalanceArm('L');
  FF(60, 855);
  DropCan(10, 'L', 'C', 60, 300);
}

void Mission_2() {
  BB(60, 855);
  SetBack(25, 410, 'R');
  BalanceArm('W');
  FF(60, 1175);
  SetFront(25, 300, 'L');
  FF(60, 855);
  SetFront(25, 340, 'L');
  PickCan(5, 60, 300);

  SetBack(25, 200, 'L');
  FF(60, 855);
  SetFront(25, 400, 'R');
  SetBack(25, 375);
  FF(60, 835, 'R');
  BB(60, 855);
  SetBack(25, 200, 'L');
  DropCan(5, 'R', 'R', 60, 250);

  SpinDegree(90);
  SetBack(25, 350);
  FF(60, 830, 'R');
  FF(60, 510, 'R');
  FF(60, 535, 'R');
  BB(60, 535);
  SetBack(25, 250, 'L');
  DropCan(13, 'L', 'L', 60, 300);
}

void Mission_3() {
  SpinDegree(90);
  FF(60, 535);
  SetFront(25, 325, 'L');
  PickCan(0, 60, 350);

  SpinDegree(90);
  BB(60, 535);
  SetBack(25, 250, 'L');
  DropCan(13, 'R', 'R', 60, 300);

  SpinDegree(90);
  FF(60, 535);
  SetFront(25, 340, 'L');
  BB(60, 535);
  SetBack(25, 375, 'L');
  BB(60, 855);
  SetBack(25, 250, 'L');
  SetBack(25, 410);
  FF(60, 855);
  DropCan(10, 'L', 'L', 60, 300);
}

void Mission_4() {
  BalanceArm('C');
  BB(60, 855);
  SetBack(25, 410, 'R');
  FF(60, 515, 'R');
  BB(60, 1575);
  SetBack(25, 350, 'R');
  BB(60, 535);
  SetBack(25, 350, 'R');
  BB(60, 515, 'R');
  FF(60, 515, 'R');
  BB(60, 900, 'R');
  FF(60, 1175);
}