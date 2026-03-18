/////////////////////////////////////////////////

// PickCanNew(5, 60, 250); SF240 SB230
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

//  Chunks  |
//    1     | FF(40, 700);
//    2     | FF(40, 1210);
//    3     | FF(40, 1720);
// High Way | FF(40, 2200); SF230

/////////////////////////////////////////////////

//        IN                 OUT
// SetFront(25, 210); 200  SetFront(25, 240);
// SetBack(25, 220);  200  SetBack(25, 275);

/////////////////////////////////////////////////

void Operation() {
  Mission_1();
  Mission_2();
  Mission_3();
  Mission_4();
}

void Mission_1() {
  Balance_Arm('C');
  SetBack(25, 220, 'L');
  FF(40, 1210, 'R');
  SetBack(25, 220);
  FF(40, 700, 'L');
  FF(40, 700, 'R');
  SetBack(25, 240, 'L');

  PickCanNew(5, 60, 250);
  BB(40, 700, 'R');
  BB(40, 700);
  SetBack(25, 160, 'L');
  FF(40, 700);
  placeCan1_1_Norechack(8, 300, 'L', 'L', 60, 250);

  BB(40, 720, 'R');
  SetBack(25, 220);
  FF(40, 1180, 'R');
  SetBack(25, 220);
  FF(40, 2200);
  SetFront(25, 230, 'L');
  BB(40, 1180);
  SetBack(25, 220, 'R');
  placeCan1_1_Norechack(15, 300, 'R', 'C', 60, 250);
}

void Mission_2() {
  Balance_Arm('C');
  spinDegree(-90);
  SetBack(25, 240, 'L');
  PickCanNew(5, 60, 250);

  spinDegree(90);
  SetBack(25, 220);
  FF(40, 1180, 'L');
  SetBack(25, 220);
  FF(40, 2200);
  SetFront(25, 230, 'R');
  BB(40, 1180);
  SetBack(25, 175, 'L');
  placeCan1_1_Norechack(8, 300, 'R', 'R', 60, 250);

  BB(40, 720, 'R');
  SetBack(25, 220);
  FF(40, 700, 'L');
  FF(40, 700, 'R');
  FF(40, 700, 'L');
  SetBack(25, 175, 'R');
  placeCan1_1_Norechack(13, 300, 'L', 'C', 60, 250);
}

void Mission_3() {
  Balance_Arm('C');
  spinDegree(-90);
  SetBack(25, 220);
  FF(40, 680, 'R');
  PickCanNew(0, 60, 275);

  spinDegree(90);
  FF(40, 680);
  SetFront(25, 300, 'L');
  placeCan1_1_Norechack(13, 300, 'L', 'L', 60, 250);

  BB(40, 700);
  SetBack(25, 220, 'R');
  FF(40, 700, 'L');
  FF(40, 690, 'R');
  SetBack(25, 220);
  FF(40, 2200);
  SetFront(25, 230, 'L');
  BB(40, 1180);
  SetBack(25, 220, 'R');
  placeCan1_1_Norechack(15, 300, 'R', 'R', 60, 250);
}

void Mission_4() {
  Balance_Arm('C');
  spinDegree(-90);
  SetBack(25, 220);
  FF(40, 1180, 'L');
  SetBack(25, 220);
  FF(40, 2200);
  SetFront(25, 230, 'R');
  BB(40, 1180);
  SetBack(25, 220, 'L');
  BB(40, 1180);
}