void EndMission() {
  BB(40,650);
  SetBack(15, 450, 'R');
  motorStop();
  delay(50);
  SetFront(20);
  motorStop();
  delay(50);
  //////////////////////
  BB(60, 620, 'R');  //3 ช่อง
  motorStop();
  delay(50);
  /////////////////
  FF(60, 550, 'L');  //3 ช่อง
  motorStop();
  delay(50);
  ///////////////////
  FF(80,700, 'L');  //3 ช่อง
  motorStop();
  delay(50);
  SetBack(15);
  motorStop();
  delay(50);
  //////////////////////////
  FF(80,1050 );  

  
}
