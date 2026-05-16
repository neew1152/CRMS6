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
  FF(20, 3100);
  FF(40, 700);
  SetFront(25, 210, 'R');
  Balance_Arm('S');
  lift(2);
  FF(40, 1210);
  SetFront(25, 210, 'L');
  Balance_Arm('C');
  BB(40, 675, 'L');
  FF(40, 700, 'L');
  SetBack(25, 220);
  FF(40, 700, 'R');
  SetFront(25, 210);
  Balance_Arm('C');
  BB(40, 2200, 'L');
  BB(40, 1100);
  SetBack(25, 220, 'R');
  SetBack(25, 275);
  FF(40, 1210);
  SetFront(25, 275, 'L');
  PickCanNew(5, 60, 250); // RG

  SetBack(25, 180, 'L');
  FF(40, 1175);
  SetFront(25, 210, 'R');
  SetBack(25, 180);
  FF(40, 675, 'L');
  FF(40, 650, 'R');
  BB(40, 675);
  SetBack(25, 225, 'L');
  placeCan1_1_Norechack(8, 300, 'L', 'C', 60, 250);

  SetBack(25, 220, 'R');
  FF(40, 675);
  SetFront(25, 265, 'L');
  BB(40, 700);
  SetBack(25, 275, 'R');
  FF(40, 700, 'L');
  BB(40, 2200);
  SetBack(25, 250, 'R');
  placeCan1_1_Norechack(15, 300, 'R', 'R', 60, 250);
}

void Mission_2() {
  delay(250); spinDegree(90); delay(250);
  SetFront(25, 210);
  Balance_Arm('C');
  BB(40, 2200, 'R');
  BB(40, 700);
  Balance_Arm('W');
  SetBack(25, 220, 'L');
  FF(40, 1210);
  delay(250); spinDegree(-90); delay(250);
  SetFront(25, 190, 'R');
  Balance_Arm('S');
  lift(2);
  PickCanNew(5, 60, 250);

  BB(40, 1210); // GY
  SetBack(25, 220, 'R');
  SetBack(25, 220);
  FF(40, 1210);
  delay(250); spinDegree(90); delay(250);
  SetBack(25, 220);
  FF(40, 650, 'R');
  BB(40, 675);
  SetBack(25, 200, 'L');
  placeCan1_1_Norechack(8, 300, 'L', 'L', 60, 250);

  SetBack(25, 220, 'R');
  FF(40, 675);
  SetFront(25, 265, 'L');
  BB(40, 700);
  SetBack(25, 275, 'R');
  FF(40, 700, 'L');
  FF(40, 660, 'L');
  BB(40, 700);
  FF(40, 650);
  SetFront(25, 250, 'L');
  BB(40, 700);
  SetBack(25, 200, 'L');
  placeCan1_1_Norechack(13, 300, 'R', 'C', 60, 250);
}

void Mission_3() {
  Balance_Arm('C');
  spinDegree(90);
  SetBack(25, 220);
  FF(40, 1210);
  delay(250); spinDegree(90); delay(250);
  FF(40, 700, 'R');
  SetBack(25, 275);
  FF(40, 700, 'L');
  SetBack(25, 275, 'R');
  PickCanNew(5, 60, 250);
  BB(40, 700);
  SetBack(25, 275, 'R');
  FF(40, 700, 'R');
  BACC3();
  SetBack(25, 170, 'L');
  placeCan1_1_Norechack(13, 300, 'R', 'R', 60, 250);

  Balance_Arm('W');
  spinDegree(-90);
  SetFront(25, 210);
  BACC3();
  BB(40, 2200);
  SetBack(25, 250, 'R');
  placeCan1_1_Norechack(15, 300, 'L', 'L', 60, 250);
}

void Mission_4() {
  Balance_Arm('C');
  BB(40, 700);
  SetBack(25, 210, 'R');
  BB(40, 700, 'R');
  FF(40, 700, 'R');
  Balance_Arm('C');
  BB(60, 880, 'R'); 
  FF(60, 550);
  FF(20, 3100);
}