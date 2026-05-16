void Can2() {
  //--Go to Box 2
  FF(60, 520);  //2 ช่อง
  SetFront(25, 280, 'R'); 
  FF(60, 520);  //2 ช่อง
  SetFront(25, 280, 'R'); 
  FF(60, 520, 'L');  //2 ช่อง
  FF(80, 720);  //3 ช่อง
  SetFront(25, 280, 'L'); //--Facing Box 2 

  //--Get Cans at Box 2
  SetBack(25, 280); 
  pickCan(5, SWITCH_LR);
  SetBack(25, 280, 'R'); 

  //--Go place Green
  BB(80, 720);  //3 ช่อง
  SetBack(25, 280, 'R'); 
  BB(60, 520, 'L');  //2 ช่อง
  // SetFront(25, 280); 
  BB(60, 600, 'L');  //2 ช่อง
  BB(60, 520, 'L');  //2 ช่อง
  SetBack(25, 280); //--Face green block

  //--Place Can 1 green
  placeCan1_NoShake(5, 4, 'r', 's');      // วาง 1 กระป๋อง placeCan(ความสูง หน่วยเป็นเซ็นติเมตร, ระยะจอด, เลือกมือจับ, ตำแหน่งวาง)
  SetBack(25, 280, 'R');

  //--Go to Red
  FF(60, 520);  //2 ช่อง
  SetFront(25, 280, 'R'); 
  FF(60, 520);  //2 ช่อง
  SetFront(25, 280, 'L'); 
  FF(60, 520, 'L');  //2 ช่อง
  BB(80, 1280);  //5 ช่อง ข้ามสะพานแบบ*ตรง*
  SetBack(25, 280, 'R');  //--Face Red

  //--Place Red Can 2
  lift(30); delay(300);
  placeCan1_NoShake(15, 4, 'l', 's');      // วาง 1 กระป๋อง placeCan(ความสูง หน่วยเป็นเซ็นติเมตร, ระยะจอด, เลือกมือจับ, ตำแหน่งวาง)
  BB(40, 510, 'L');
  SetBack(25, 280); 


  


















}
