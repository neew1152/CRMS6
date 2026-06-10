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
// High Way | FF(60, 1550 / 1575);

/////////////////////////////////////////////////

//   Chunks   |
//     1      | FF(40, 700);
//     2      | FF(40, 1210);
//     3      | FF(40, 1720);
//  High Way  | FF(40, 2200); | 1250 & 1175
// Chopsticks | FF(20, 3100);

/////////////////////////////////////////////////

//        IN          |   OUT
// SetFront(25, 250); | SetFront(25, 325);
// SetBack(25, 300);  | SetBack(25, 425);

//        IN         
// SetFront(25, 375 / 350);

// SetBack(25, 300);
// FF(60, 855, 'R');

/////////////////////////////////////////////////

void Operation() {
  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
}

void Mission_1() {
  FF(60, 1175);
  SetFront(25, 375, 'L');
  SetBack(25, 300);
  FF(60, 855, 'R');
  FF(60, 855);
  SetFront(25, 250);
  BB(60, 525, 'R');
  BB(60, 535);
  SetBack(25, 300, 'L');

  PickCan(5, 60, 250);
  SetBack(25, 300, 'R');
  BalanceArm('C');
  FF(60, 535);
  SetFront(25, 375, 'L');
  BB(60, 535, 'R');
  FF(60, 535, 'R');
  BB(60, 855);
  SetBack(25, 300, 'L');
  DropCan(5, 'L', 'C', 60, 200);

  BalanceArm('C');
  SetBack(25, 425, 'R');
  SetBack(25, 300);
  FF(60, 535 + 1550);
  SetFront(25, 375, 'R');
  
  FF(60, 535);
  SetFront(25, 350, 'L');
  BB(60, 535, 'R');
  FF(60, 535, 'R');
  BB(60, 855);
  SetBack(25, 300, 'R');
  FF(60, 855);
  DropCan(10, 'R', 'A', 60, 200);
}

void Mission_2() {
  BalanceArm('C');
  BB(60, 855);
  SetBack(25, 300, 'L');
  FF(60, 855);
  SetFront(25, 350, 'L');
  BB(60, 535, 'L');
  FF(60, 535);
  SetFront(25, 375, 'L');
  FF(60, 535);
  PickCan(5, 60, 225);

  SpinDegree(90);
  SetFront(25, 250);
  BalanceArm('C');
  BB(60, 1575, 'L');
  BB(60, 855);
  SetBack(25, 300, 'L');
  BB(60, 855);
  SetBack(25, 300);
  FF(60, 535, 'R');
  DropCan(13, 'R', 'C', 60, 200);

  BalanceArm('C');
  SpinDegree(-90);
  FF(60, 535);
  SetFront(25, 375, 'R');
  SetBack(25, 300);
  FF(60, 855, 'R');
  BB(60, 855);
  SetBack(25, 300, 'L');
  DropCan(5, 'L', 'A', 60, 200);
}

void Mission_3() {
  SpinDegree(90);
  SetBack(25, 300);
  FF(60, 535, 'L');
  PickCan(0, 60, 250);

  BalanceArm('C');
  SpinDegree(-90);
  BB(60, 535, 'R');
  BB(60, 855);
  SetBack(25, 300, 'L');
  BB(60, 535, 'R');
  DropCan(13, 'R', 'A', 60, 200);

  BalanceArm('C');
  SpinDegree(-90);
  FF(60, 535);
  SetFront(25, 375, 'R');
  SetBack(25, 300);
  FF(60, 855, 'R');
  FF(60, 1550);
  SetFront(25, 375, 'R');
  
  FF(60, 535);
  SetFront(25, 350, 'L');
  BB(60, 535, 'R');
  FF(60, 535, 'R');
  BB(60, 855);
  SetBack(25, 300, 'R');
  FF(60, 855);
  DropCan(10, 'R', 'A', 60, 200);
}

void Mission_4() {
  BalanceArm('C');
  BB(60, 855);
  SetBack(25, 300, 'L');
  FF(60, 855);
  SetFront(25, 350, 'L');
  BB(60, 535, 'L');
  FF(60, 535, 'L');
  FF(60, 535, 'R');
  SetFront(25, 250);
  BB(60, 1575, 'R');
  BB(60, 535);
  SetBack(25, 300, 'R');
  BB(60, 1175);
}