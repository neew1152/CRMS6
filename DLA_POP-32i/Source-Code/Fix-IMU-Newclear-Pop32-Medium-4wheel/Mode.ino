void Mode()
{
   switch(RobotMode)
  {
    case Mode0:   //กด SW_OK(เหลือง) น้อยกว่า 3 วินาที 
            ModeNormal();  //วิ่งปกติถอยใช้ BackwardBalance 
            break;

  //   case Mode1:   //กด SW_A(ส้ม) มากกว่า 0.2 วินาที 
  //           ModeAcc();      //วิ่งเร่งจูนหลัง       
  //           break;

  //   case Mode2:   //กด SW_A(ส้ม) น้อยกว่า 0.2 วินาที
            
  //           ModeSpeed();  //เร่งทุกอย่างเลี้ยวใช้เข็มทิศควบคุมการเคลื่อนที่แทนการเลี้ยวและเดิน
  //           break;

  //   case Mode3:   //กด SW_B(ขาว) มากกว่า 0.2 วินาที
  //           ModeNoTune();   //วิ่งปกติไม่จูนหลัง     
  //           break;

  //  case Mode4:    //กด SW_B(ขาว) น้อยกว่า 0.2 วินาที
  //           ModeCurveAcc();  //เร่งทุกอย่างเลี้ยวแบบ Curve ล้อด้านเดียวใช้เข็มทิศแบบไม่รีเซตใหม่จะเร็ว         
  //           break;
   }
}
void ModeNormal() //วิ่งปกติถอยใช้ BackwardBalance 
{
  Box1();
}
