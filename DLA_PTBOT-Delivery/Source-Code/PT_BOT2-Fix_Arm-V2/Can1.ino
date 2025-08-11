void Can1() {
  SetFront(30, 200, 'L'); motorStop(); delay(50);
  FF(60, 550, 'R'); motorStop(); delay(50); //2 ช่อง go 1 block
  FF(60, 520, 'R'); motorStop(); delay(50); //2 ช่อง go 1 block
  SetBack(25, 250, 'L');
  pickCan(5, SWITCH_LR); motorStop(); delay(50);
  BB(40, 510, 'R'); motorStop(); delay(50);
  SetBack(25, 200, 'R'); motorStop(); delay(50);
  FF(60, 520); motorStop(); delay(50); //2 ช่อง go 1 block
  placeCan2(5, 3, 'l', 'r'); 

  // BB(40, 510, 'R'); motorStop(); delay(50);
  // BB(60, 520, 'R'); motorStop(); delay(50); //2 ช่อง go 1 block
  // SetBack(30, 200, 'R'); motorStop(); delay(50);
  // FF(80, 720, 'R'); motorStop(); delay(50);  //4 ช่อง go 3 block
  // SetFront(30, 200); motorStop(); delay(50);
  // BB(80, 720, 'R'); motorStop(); delay(50);  //3 ช่อง go 2 block
  // SetBack(30, 100, 'R'); motorStop(); delay(50);
  // placeCan1(14.8, 3, 'l', 'l');
}




  
  







  





   



