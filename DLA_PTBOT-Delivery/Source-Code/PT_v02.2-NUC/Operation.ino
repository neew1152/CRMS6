// PickCanNew(5, 60, 250);
// placeCan1_1_Norechack(8, 300, 'a', 'a', 60, 250);
// G = 8
// Y = 13
// R = 15

///////////////////////////////////////////////

// ความเชื่อย 205
// FF(100, 425);  // เดินหน้าตรง 1 ช่อง
// FF(100, 630);  // เดินหน้าตรง 2 ช่อง
// FF(100, 840);  // เดินหน้าตรง 3 ช่อง

///////////////////////////////////////////////

// ความเชื่อย 330 | ลดจากเดิม 125
// FF(60, 550);  // เดินหน้าตรง 1 ช่อง
// FF(60, 880);  // เดินหน้าตรง 2 ช่อง
// FF(60, 1210); // เดินหน้าตรง 3 ช่อง
// FF(60, 1500); // High Way

///////////////////////////////////////////////

// ความเชื่อย 510
// FF(40, 700);   // เดินหน้าตรง 1 ช่อง
// FF(40, 1210);  // เดินหน้าตรง 2 ช่อง
// FF(40, 1720);  // เดินหน้าตรง 3 ช่อง
// FF(40, 2200);  // High Way

///////////////////////////////////////////////

//        IN                 OUT
// SetFront(25, 210); 200  SetFront(25, 240);
// SetBack(25, 220);  200  SetBack(25, 275);

void Operation() {
  // Mission_1();
  // Mission_2();
  Mission_3();
  // Mission_4();
}

void Mission_1() {
  SetFront_Wall(25, 210);
  Balance_Arm('C');
  BB(40, 1160, 'L');
  FF(40, 700, 'R');
  FF(40, 700, 'L');
  SetBack(25, 220);
  FF(40, 2200);
  SetFront(25, 210, 'L');
  FF(40, 700, 'L');
  FF(40, 650);
  SetFront(25, 210);
  BB(40, 1210);
  SetBack(25, 220);
  FF(40, 1210, 'R');
  FF(40, 700);
  SetFront(25, 150, 'L');
  FF(40, 700);
  PickCanNew(5, 60, 275);

  BB(40, 1210, 'L');
  SetBack(25, 220);
  SetBack(25, 150, 'L');
  placeCan1_1_Norechack(8, 300, 'L', 'C', 60, 250);

  BB(40, 650, 'L');
  SetFront_Wall(25, 210);
  Balance_Arm('C');
  BB(40, 1150, 'L');
  SetBack(25, 220);
  FF(40, 2200);
  SetFront(25, 210, 'R');
  Balance_Arm('W');
  FF(40, 1190);
  SetFront_Wall(25, 150, 'L');
  placeCan1_1_Norechack(15, 300, 'R', 'C', 60, 250);
}

void Mission_2() {
  Balance_Arm('C');
  spinDegree(-90);
  SetBack(25, 220);
  FF(40, 1210, 'L');
  SetBack(25, 220);
  FF(40, 2200);
  SetFront(25, 210, 'L');
  FF(40, 700, 'R');
  FF(40, 700, 'R');
  SetBack(25, 220);
  FF(40, 700, 'L');
  SetBack(25, 220, 'R');
  PickCanNew(5, 60, 275);

  BB(40, 700);
  SetBack(25, 220, 'R');
  FF(40, 700, 'R');
  Balance_Arm('W');
  FF(40, 700);
  SetFront_Wall(25, 175, 'R');
  FF(40, 700);
  placeCan1_1_Norechack(8, 300, 'L', 'L', 60, 250);

  STOP();
  BB(40, 700, 'L');
  SetFront_Wall(25, 210);
  Balance_Arm('C');
  BB(40, 1150, 'L');
  SetBack(25, 220);
  FF(40, 2200);
  SetFront(25, 210, 'L');
  STOP();
  Balance_Arm('W');
  FF(40, 700);
  SetFront(25, 210, 'L');
  FF(40, 1210);
  placeCan1_1_Norechack(13, 300, 'R', 'R', 60, 250);
}

void Mission_3() {
  BB(40, 1210);


}

void Mission_4() {
}