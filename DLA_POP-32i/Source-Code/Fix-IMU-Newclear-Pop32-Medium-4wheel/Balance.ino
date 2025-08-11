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
  delay(250);
}
void BackwardBalanceF()  //ถอยหลังปรับสมดุลใช้เซ็นเซอร์หน้า
{
  int Status=0;
  BackwardSpeedTime(SlowSpeed,1);
  
  while(Status==0)
  {
    ConvertADC();
    if((L1==0)&&(R1==1)) //เจอดำข้างซ้าย
    {
      Status=1;
      AO(); 
      SR(SlowSpeed);
      StartTimer();
      while(R1==1) {ConvertADC(); if(ReadTimer()>300) {AO();R1=0;}}
      //delay(30);
    }
    else if((L1==1)&&(R1==0))  //เจอดำข้างขวา
    {
      Status=2;
      AO(); 
      SL(SlowSpeed);
      StartTimer();
      while(L1==1) {ConvertADC(); if(ReadTimer()>300) {AO();L1=0;}}
      //delay(30);
    }
    else if((L1==0)&&(R1==0)) Status=3; //เจอดำทั้งสองข้าง
  }
  //MotorStop();
  BackwardSpeedTime(SlowSpeed,1);
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

void Balance()
{
  int Value=0;
  AO();delay(5);
  BackwardSpeedTime(50,10);AO();
  while(Value==0)
  {
    // Forward(Speed);
   if((analog(1)<RefL1)&&(analog(3)<RefR1)) Value=1; 
   else if((analog(1)<RefL1)&&(analog(3)>RefR1)) //ซ้ายดำ ขวาขาว
   {
     AO();delay(5);
     while(analog(3)>RefR1)
     {
       
       motor(3,80);
       motor(4,80);
       motor(1,-40);
       motor(2,-40);
       delay(12);
       if(analog(3)<RefR1) break;
       Value=1;
     }
   }
   else if((analog(1)>RefL1)&&(analog(3)<RefR1)) //ซ้ายขาว ขวาดำ
   { 
     AO();delay(5);
     while(analog(1)>RefL1)
     {
      
      motor(1,80);
      motor(2,80);
      motor(3,-40);
      motor(4,-40);
      delay(12);
      if(analog(1)<RefL1)break;
      Value=1;
     }
   }
  }
  AO();delay(5);
}

void June() {
  //MotorStop();
  // delay(50);
  InitialSpeed();
  ConvertADC();
  if ((L1 == 0) && (R1 == 1)) {

    while (1) {
      motor(1, -60);
      motor(2, -60);
      motor(3, 60);
      motor(4, 60);
      ConvertADC();
      if ((L1 == 0) && (R1 == 0)) break;
    }
  } else if ((L1 == 1) && (R1 == 0)) {

    while (1) {


      motor(1, 60);
      motor(2, 60);
      motor(3, -60);
      motor(4, -60);
      ConvertADC();
      if ((L1 == 0) && (R1 == 0)) break;
    }
  }
  // delay(50);
}



// void ForwardBalance()
// {
//   int Status=0;
//   delay(100);
//   ForwardSpeedTime(40,50);
  
//   while(Status==0)
//   {
//     ConvertADC();
//     if((L1==0)&&(R1==1)) //เจอดำข้างซ้าย
//     {
//       Status=1;
//       AO(); 
//       SR(SlowSpeed);
//       StartTimer();
//       while(R1==1) {ConvertADC(); if(ReadTimer()>300) {AO();R1=0;}}
//       //delay(30);
//     }
//     else if((L1==1)&&(R1==0))  //เจอดำข้างขวา
//     {
//       Status=2;
//       AO(); 
//       SL(SlowSpeed);
//       StartTimer();
//       while(L1==1) {ConvertADC(); if(ReadTimer()>300) {AO();L1=0;}}
//       //delay(30);
//     }
//     else if((L1==0)&&(R1==0)) Status=3; //เจอดำทั้งสองข้าง
//   }
//   MotorStop();
//   delay(250);
//   BackwardSpeedTime(40, 250);
// }

void ForwardBalance()
{
  int Status=0;
  delay(100);
  ForwardSpeedTime(40,50);
  
  while(Status==0)
  {
    ConvertADC();
    if((L1==0)&&(R1==1)) //เจอดำข้างซ้าย
    {
      delay(1);
      ConvertADC();
      if((L1==0)&&(R1==1))
      {
        Status=1;
        AO(); 
        SR(SlowSpeed);
        StartTimer();
        motor(1,-SlowSpeed); motor(2,-SlowSpeed);
        motor(3,SlowSpeed); motor(4,SlowSpeed);
        while(R1==1) {ConvertADC();}
        //delay(30);
      }
    }
    else if((L1==1)&&(R1==0))  //เจอดำข้างขวา
    {
      delay(1);
      ConvertADC();
      if((L1==1)&&(R1==0))
      { Status=2;
        AO(); 
        motor(1,SlowSpeed); motor(2,SlowSpeed);
        motor(3,-SlowSpeed); motor(4,-SlowSpeed);
        while(L1==1) {ConvertADC();}
        //delay(30);
      }
    }
    else if((L1==0)&&(R1==0)) Status=3; //เจอดำทั้งสองข้าง
    else if(L2==0) SR(40);               //ซ้ายสุดเจอดำ
    else if(R2==0) SL(40);               //ขวาสุดเจอดำ
    else ForwardSpeedTime(40,1);
  }
  MotorStop();
  delay(250);
  BackwardSpeedTime(40, 250);
}

void ForwardBalance_zeroYaw()
{
  int Status=0;
  delay(100);
  ForwardSpeedTime(40,50);
  
  while(Status==0)
  {
    ConvertADC();
    if((L1==0)&&(R1==1)) //เจอดำข้างซ้าย
    {
      delay(1);
      ConvertADC();
      if((L1==0)&&(R1==1))
      {
        Status=1;
        AO(); 
        SR(SlowSpeed);
        StartTimer();
        motor(1,-SlowSpeed); motor(2,-SlowSpeed);
        motor(3,SlowSpeed); motor(4,SlowSpeed);
        while(R1==1) {ConvertADC();}
        //delay(30);
      }
    }
    else if((L1==1)&&(R1==0))  //เจอดำข้างขวา
    {
      delay(1);
      ConvertADC();
      if((L1==1)&&(R1==0))
      { Status=2;
        AO(); 
        motor(1,SlowSpeed); motor(2,SlowSpeed);
        motor(3,-SlowSpeed); motor(4,-SlowSpeed);
        while(L1==1) {ConvertADC();}
        //delay(30);
      }
    }
    else if((L1==0)&&(R1==0)) Status=3; //เจอดำทั้งสองข้าง
    else if(L2==0) SR(40);               //ซ้ายสุดเจอดำ
    else if(R2==0) SL(40);               //ขวาสุดเจอดำ
    else ForwardSpeedTime(40,1);
  }

  MotorStop();
  delay(250);
  zeroYaw();
  MotorStop();
  delay(250);
  BackwardSpeedTime(40, 250);
}