void Can3() {
  BB(40,300, 'R');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  ///////////////////////////
  FF(60, 600, 'R');  //2 ช่อง
  motorStop();
  delay(50);
  /////////////////////////////////
  FF(60, 550, 'R');  //2 ช่อง
  motorStop();
  delay(50);
  //////////////////////////
  FF(60, 550);
  SetFront(20, 400, 'L');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  ///////////////////////
  FF(35, 2150);  //ข้ามตะเกียบไปหยิบ
  SetFront(20, 430, 'L');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  /////////////////////////////
  pickCan(5, NO_SWITCH_LR);
  //////////////////////
  BB(40, 200);
  SetBack(15, 450, 'L');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  ///////////////////////
  FF(35, 2300);  //ข้ามตะเกียบกลับ
  SetFront(20, 430, 'R');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  ///////////////////////////
  FF(60, 960, 'R');  //3 ช่อง
  motorStop();
  delay(50);
  /////////////////////////////
  FF(60,1750);  // ข้ามสะพาน
  SetFront(20,540,'L');
  motorStop();
  delay(50);
  ///////////////////////
  placeCan2(15,3.5, 'l', 'r');
  //////////////////////////////
  
}
