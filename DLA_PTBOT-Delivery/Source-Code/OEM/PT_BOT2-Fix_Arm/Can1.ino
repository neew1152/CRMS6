void Can1() {
  //--Go to Box 1
  FF(80,970, 'R');  //4 ช่อง
  FF(80,720, 'R');  //3 ช่อง
  FF(60, 520, 'R');  //2 ช่อง
  FF(60, 520);  //2 ช่อง

  //--Set tune before continue
  SetFront(25, 280); 
  spinDegree(-90);
  SetBack(25, 280);
  //--
  
  FF(60, 520, 'L');  //2 ช่อง
  SetBack(25, 300);
  // FF(80,1520, 'R');  //6 ช่อง ข้ามสะพานแบบ*ตรง* แล้วเดินอีก 1 ช่อง
  FF(80,1280, 'R');  //5 ช่อง ข้ามสะพานแบบ*ตรง*

  FF(60, 520);  //2 ช่อง
  SetFront(25, 280, 'R');

  //--Go in and get Can 1
  FF(80,720, 'L');  //3 ช่อง
  SetFront(25, 280, 'R');
  pickCan(5, NO_SWITCH_LR);
  BB(40, 510);

  //--Go back
  BB(60, 520);  //2 ช่อง
  SetBack(25, 280, 'R');

  //--Go to Yellow
  FF(60, 520, 'L');  //2 ช่อง
  BB(60, 520);  //2 ช่อง
  SetBack(25, 280, 'L'); //--Facing Yellow Block
  SetBack(25, 280);

  //--Go place yellow Can1
  placeCan1_NoShake(10, 4, 'r', 's');      // วาง 1 กระป๋อง placeCan(ความสูง หน่วยเป็นเซ็นติเมตร, ระยะจอด, เลือกมือจับ, ตำแหน่งวาง)
  SetBack(25, 280, 'L');
  SetFront(25, 280);

  //--Go to Green
  BB(80, 770, 'R');  //3 ช่อง
  BB(60, 520, 'R');  //2 ช่อง
  BB(60, 520, 'R');  //2 ช่อง
  FF(60, 520);  //2 ช่อง
  SetFront(25, 280, 'R'); //--Facing green

  //--Go place green Can 2
  placeCan1_NoShake(5, 4, 'l', 's');      // วาง 1 กระป๋อง placeCan(ความสูง หน่วยเป็นเซ็นติเมตร, ระยะจอด, เลือกมือจับ, ตำแหน่งวาง)
  SetBack(25, 280, 'R');




  
  







  





   



}
