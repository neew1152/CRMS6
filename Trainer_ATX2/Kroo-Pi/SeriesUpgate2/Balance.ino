void BackwardBalance()  //ถอยหลังปรับสมดุล
{
  int Status=0;
  delay(100);
  BackwardSpeedTime(SlowSpeed,50);
  
  while(Status==0)
  {
    ConvertADCBack();
    if((BL1==0)&&(BR1==1)) //เจอดำข้างซ้าย
    {
      delay(1);
      ConvertADCBack();
      if((BL1==0)&&(BR1==1)) //เจอดำข้างซ้าย
      {
        Status=1;
        AO(); 
        motor(1,SlowSpeed); motor(2,SlowSpeed);
        motor(3,-SlowSpeed); motor(4,-SlowSpeed);
        while(BR1==1) {ConvertADCBack();}
        //delay(30);
      }
    }
    else if((BL1==1)&&(BR1==0))  //เจอดำข้างขวา
    {
      delay(1);
      ConvertADCBack();
      if((BL1==1)&&(BR1==0))  //เจอดำข้างขวา
      {
        Status=2;
        AO(); 
        motor(1,-SlowSpeed); motor(2,-SlowSpeed);
        motor(3,SlowSpeed); motor(4,SlowSpeed);
        while(BL1==1) {ConvertADCBack();}
        //delay(30);
        
      }
    }
    else if((BL1==0)&&(BR1==0)) Status=3; //เจอดำทั้งสองข้าง
    else if(BL2==0) SL(40);               //ซ้ายสุดเจอดำ
    else if(BR2==0) SR(40);               //ขวาสุดเจอดำ
    else BackwardSpeedTime(SlowSpeed,1);
  }
  MotorStop();
  delay(100);
}