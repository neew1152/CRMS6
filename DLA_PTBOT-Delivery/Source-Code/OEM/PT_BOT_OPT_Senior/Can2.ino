void Can2() {
  BB(40,250);
  SetBack(15, 450, 'R');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  ////////////////////////
  FF(60,950, 'R');  //3 ช่อง
  motorStop();
  delay(50);
  //////////////////////////
  FF(60, 550, 'R');  //2 ช่อง
  motorStop();
  delay(50);
  /////////////////////////////
   FF(40,600);  //2 ช่อง
  pickCan(0, NO_SWITCH_LR);
  ////////////////////////////////
  BB(40,400, 'L');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  /////////////////////
  FF(60,500);
  SetFront(20, 420 , 'R');
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  placeCan2(5,3.6, 'l', 'c');
}
