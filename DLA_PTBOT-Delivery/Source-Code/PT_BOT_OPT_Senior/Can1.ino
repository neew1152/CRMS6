void Can1() {
  FF(80,970, 'R');  //4 ช่อง
  motorStop();
  delay(50);
  /////////////////////
  FF(80,720, 'R');  //3 ช่อง
  motorStop();
  delay(50);
  ////////////////////
  FF(60, 520, 'R');  //2 ช่อง
  motorStop();
  delay(50);
  //////////////////////
  FF(60, 500);  //2 ช่องกรณีมีเซตหน้า
  SetFront(20, 500, 'L');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  ////////////////////////
  FF(60, 635, 'L');  //2 ช่อง
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  /////////////////////////
  FF(60, 1700, 'R');  // ข้ามสะพาน
  motorStop();
  delay(50);
  /////////////////////////
  FF(60, 500);  //2 ช่องกรณีมีเซตหน้า
  SetFront(20, 500, 'R');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  /////////////////////////
  FF(100, 780);
  pickCan(5, NO_SWITCH_LR);
  ///////////////////////////////////
  BB(60,1100);
  SetBack(15, 400, 'R');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  ///////////////////////////////
  FF(60,630,'R');
  motorStop();
  delay(50);
  ///////////////////
  FF(60,980);
  motorStop();
  delay(50);
  SetFront(20, 410 , 'R');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  placeCan2(10, 3.6, 'r', 'c');
}
