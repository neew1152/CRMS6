/////////////////////////////////////////////////

// PickCanNew(5, 60, 275); SF240 SB230
// placeCan1_1_Norechack(8, 300, 'a', 'a', 60, 250); SB200

/////////////////////////////////////////////////

// Block
// G = 8
// Y = 13
// R = 15

/////////////////////////////////////////////////

//  Chunks  |
//    1     | FF(100, 425);
//    2     | FF(100, 630);
//    3     | FF(100, 840);

/////////////////////////////////////////////////

//  Chunks  |
//    1     | FF(60, 550);
//    2     | FF(60, 880);
//    3     | FF(60, 1210);
// High Way | FF(60, 1500);

/////////////////////////////////////////////////

//   Chunks   |
//     1      | FF(40, 700);
//     2      | FF(40, 1210);
//     3      | FF(40, 1720);
//  High Way  | FF(40, 2200); | 1250 & 1150 | SF230
// Chopsticks | FF(20, 3100);

/////////////////////////////////////////////////

//        IN              |   OUT
// SetFront(25, 210); 200 | SetFront(25, 265);
// SetBack(25, 220);  200 | SetBack(25, 275);

/////////////////////////////////////////////////

void Operation() {
  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
}

void Mission_1() {
  Balance_Arm('C');
  FACC4();
  SetFront_Wall(25, 210, 'R');
  Balance_Arm('C');
  FF(40, 700);
  SetFront(25, 275, 'R');
  SetBack(25, 220);
  FACC3();
  spinDegree(90);
  SetFront(25, 275, 'L');
  PickCanNew(5, 60, 240);

  spinDegree(90);
  SetFront(25, 265);
  BB(40, 2275, 'R');
  Balance_Arm('W');
  BB(40, 700);
  SetBack(25, 220, 'L');
  FF(40, 1210, 'L');
  SetFront(25, 135, 'R');
  placeCan1_1_Norechack(13, 300, 'R', 'C', 60, 250);

  BB(40, 1210);
  SetBack(25, 220, 'R');
  SetBack(25, 220);
  FF(40, 650, 'L');
  BB(40, 1210);
  SetBack(25, 235, 'L');
  placeCan1_1_Norechack(8, 300, 'L', 'C', 60, 200);
}

void Mission_2() {
  spinDegree(90);
  SetBack(25, 300);
  FACC3();
  spinDegree(90);
  FF(40, 675, 'R');
  SetBack(25, 275);
  FF(40, 700, 'L');
  FF(40, 625);
  SetFront_Wall(25, 210, 'R');
  PickCanNew(0, 60, 275);

  spinDegree(90);
  FF(40, 700);
  SetFront(25, 275, 'L');
  BB(40, 700);
  SetBack(25, 250, 'L');
  BB(40, 1210);
  SetBack(25, 220, 'L');
  Balance_Arm('W');
  FF(40, 1210, 'L');
  SetFront(25, 175, 'R');
  placeCan1_1_Norechack(13, 300, 'R', 'R', 60, 250);

  BB(40, 1210);
  SetBack(25, 220, 'R');
  SetBack(25, 220);
  FF(40, 650, 'L');
  BB(40, 1210);
  SetBack(25, 175, 'L');
  placeCan1_1_Norechack(8, 300, 'L', 'L', 60, 200);
}

void Mission_3() {
  spinDegree(90);
  SetBack(25, 300);
  FACC3();
  spinDegree(-90);
  BACC3();
  SetBack(25, 220, 'R');
  Balance_Arm('W');
  FF(20, 3100);
  FF(40, 700);
  SetFront(25, 210, 'L');
  PickCanNew(5, 60, 275);

  SetBack(25, 220, 'L');
  Balance_Arm('W');
  FF(40, 700);
  FF(20, 3100);
  SetFront(25, 265, 'R');
  SetBack(25, 220);
  FF(40, 700, 'L');
  FF(40, 700, 'L');
  SetBack(25, 220, 'R');
  placeCan1_1_Norechack(15, 300, 'A', 'A', 60, 250);
}

void Mission_4() {
  Balance_Arm('C');
  BB(40, 700);
  SetBack(25, 220, 'R');
  FF(40, 690, 'L');
  BB(40, 2200);
  SetBack(25, 275, 'R');
  BACC3();
  SetBack(25, 200, 'L');
  BB(40, 700);
  SetBack(25, 220, 'L');
  BACC4();
}