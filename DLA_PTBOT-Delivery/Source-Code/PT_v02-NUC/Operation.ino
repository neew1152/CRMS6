// PickCanNew(8, 60, 350);
// placeCan1_1_Norechack(18, 300,'a','a', 60, 300);
// G = 8
// Y = 13
// R = 15

///////////////////////////////////////////////

// FF(100, 425);   // เดินหน้าตรง 1 ช่อง
// FF(100, 630);   // เดินหน้าตรง 2 ช่อง
// FF(100, 840);   // เดินหน้าตรง 3 ช่อง

///////////////////////////////////////////////

//        IN
// SetFront(25, 235);
// SetBack(25, 150);

void operation() {
  Mission_1();
  Mission_2();
  Mission_3();
}

void Mission_1() {
  SetBack(25, 250, 'R');
  FF(100, 425);
  PickCanNew(0, 60, 350);

  BB(100, 425);
  SetBack(25, 100, 'L');
  SetBack(25, 150);
  placeCan1_1_Norechack(13, 300, 'R', 'R', 60, 300);

  spinDegree(90);
  SetBack(25, 150);
  FF(100, 425, 'L');
  SetBack(25, 100);
  FF(100, 425, 'R');
  placeCan1_1_Norechack(15, 300, 'L', 'C', 60, 300);
}

void Mission_2() {
  spinDegree(-90);
  FF(100, 630);
  SetFront_Wall(25, 235, 'L');
  FF(100, 425);
  SetFront_Wall(25, 235, 'L');
  PickCanNew(5, 60, 350);

  SetBack(25, 150);
  spinDegree(-90);
  SetBack(25, 125);
  FF(100, 425, 'R');
  SetBack(25, 100);
  FF(100, 615, 'L');
  placeCan1_1_Norechack(15, 300, 'L', 'L', 60, 300);

  spinDegree(-90);
  FF(100, 400, 'R');
  placeCan1_1_Norechack(8, 300, 'R', 'C', 60, 300);
}

void Mission_3() {
  spinDegree(-90);
  FF(100, 425);
  SetFront_Wall(25, 235, 'R');
  PickCanNew(5, 60, 350);

  spinDegree(90);
  SetBack(25, 100);
  FF(100, 425, 'L');
  placeCan1_1_Norechack(8, 300, 'R', 'S', 60, 300);

  spinDegree(90);
  FF(100, 630);
  SetFront_Wall(25, 235, 'R');
  FF(100, 425);
  SetFront_Wall(25, 235, 'R');
  placeCan1_1_Norechack(13, 300, 'L', 'L', 60, 300);
}