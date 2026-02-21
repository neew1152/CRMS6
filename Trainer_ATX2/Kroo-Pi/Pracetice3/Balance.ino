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
void BackwardBalanceF()  //ถอยหลังปรับสมดุลใช้เซ็นเซอร์หน้า
{
  int Status=0;
  ForwardSpeedTime(SlowSpeed,1);
  
  while(Status==0)
  {
    ConvertADC();
    if((L1==0)&&(R1==1)) //เจอดำข้างซ้าย
    {
      Status=1;
      AO(); 
      SL(SlowSpeed);
      StartTimer();
      while(R1==1) {ConvertADC(); if(ReadTimer()>300) {AO();R1=0;}}
      //delay(30);
    }
    else if((L1==1)&&(R1==0))  //เจอดำข้างขวา
    {
      Status=2;
      AO(); 
      SR(SlowSpeed);
      StartTimer();
      while(L1==1) {ConvertADC(); if(ReadTimer()>300) {AO();L1=0;}}
      //delay(30);
    }
    else if((L1==0)&&(R1==0)) Status=3; //เจอดำทั้งสองข้าง
  }
  //MotorStop();
  ForwardSpeedTime(SlowSpeed,1);
  ConvertADC();
  while(C==0) {ConvertADC();}
}
void ForwardBalanceB()  //เดินหน้าปรับสมดุลใช้เซ็นเซอร์หลัง
{
  int Status=0;
  ForwardSpeedTime(SlowSpeed,1);
  
  while(Status==0)
  {
    ConvertADCBack();
    if((BL2==0)&&(BR2==1)) //เจอดำข้างซ้าย
    {
      Status=1;
      AO(); 
      SL(SlowSpeed);
      while(BR2==1) {ConvertADCBack();}
      delay(20);
    }
    else if((BL2==1)&&(BR2==0))  //เจอดำข้างขวา
    {
      Status=2;
      AO(); 
      SR(SlowSpeed);
      while(BL2==1) {ConvertADCBack();}
      delay(20);
    }
    else if((BL2==0)&&(BR2==0)) Status=3; //เจอดำทั้งสองข้าง
  }
}
