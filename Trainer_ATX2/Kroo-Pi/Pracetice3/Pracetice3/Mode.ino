void Mode()
{
   switch(RobotMode)
  {
    case Mode0:   //กด SW_OK(เหลือง) น้อยกว่า 3 วินาที 
            ModeNormal();  //วิ่งปกติถอยใช้ BackwardBalance 
            break;

    case Mode1:   //กด SW_A(ส้ม) มากกว่า 0.2 วินาที 
            ModeAcc();      //วิ่งเร่งจูนหลัง       
            break;

    case Mode2:   //กด SW_A(ส้ม) น้อยกว่า 0.2 วินาที
            
            ModeSpeed();  //เร่งทุกอย่างเลี้ยวใช้เข็มทิศแบบไม่รีเซตใหม่จะเร็ว
            break;

    case Mode3:   //กด SW_B(ขาว) มากกว่า 0.2 วินาที
            Menu();   //วิ่งปกติไม่จูนหลัง     
            break;

   case Mode4:    //กด SW_B(ขาว) น้อยกว่า 0.2 วินาที
            ModeNoTuneAcc();  //วิ่งเร่งไม่จูนหลัง          
            break;
   }
}
void ModeNormal() //วิ่งปกติถอยใช้ BackwardBalance 
{
  Box1();
  Box2();
  Box3();
  Box4();
  GoFinish();
}
void ModeSpeed()  //เร่งทุกอย่างเลี้ยวใช้เข็มทิศแบบไม่รีเซตใหม่จะเร็ว
{
  Box1Speed();
  Box2Speed();
  Box3Speed();
  Box4Speed();
  GoFinishSpeed();
}
void ModeAcc()  //วิ่งเร่งจูนหลัง 
{
  Box1Acc();
  Box2Acc();
  Box3Acc();
  Box4Acc();
  GoFinishAcc();
}
void ModeNoTune() //วิ่งปกติไม่จูนหลัง
{
  Box1NoTune();
  Box2NoTune();
  Box3NoTune();
  Box4NoTune();
  GoFinishNoTune();
}
void ModeNoTuneAcc()  //วิ่งเร่งไม่จูนหลัง
{
  Box1NoTuneAcc();
  Box2NoTuneAcc();
  Box3NoTuneAcc();
  Box4NoTuneAcc();
  GoFinishNoTuneAcc();
}
