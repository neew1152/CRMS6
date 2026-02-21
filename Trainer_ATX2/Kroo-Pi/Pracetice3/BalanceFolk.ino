void Balance()
{
  int Value=0;
  AO();delay(5);
  BackwardDelay(50,10);AO();
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

void BB()
{

  int Value=0;
  // AO();delay(50);
  int MotorSpeed=50;
  while(Value==0)
  {
   InitialSpeed();
   BaseSpeed=MotorSpeed;
   ConvertADC();
   BackwardDelay(50,1);
   float k = 1;
   int SP_M3 = constrain(val_BL2 * k, 0, BackLeftBaseSpeed);
   int SP_M4 = constrain(val_BR2 * k, 0, BackRightBaseSpeed);
   if(val_BL2>=70 && val_BR2>=70) {BK2(SP_M3,SP_M4);}

   else if((val_BL2>=60&&val_BL2<70)) {BK2(SP_M3*0.8,SP_M4);}
   else if((val_BR2>=60&&val_BR2<70)) {BK2(SP_M3,SP_M4*0.8);}
   else if((val_BL2>=50&&val_BL2<60)) {BK2(SP_M3*0.7,SP_M4);}
   else if((val_BR2>=50&&val_BR2<60)) {BK2(SP_M3,SP_M4*0.7);}
   else if((val_BL2>=40&&val_BL2<50)) {BK2(SP_M3*0.6,SP_M4);}
   else if((val_BR2>=40&&val_BR2<50)) {BK2(SP_M3,SP_M4*0.6);}
   else if((val_BL2>=30&&val_BL2<40)) {BK2(SP_M3*0.5,SP_M4);}
   else if((val_BR2>=30&&val_BR2<40)) {BK2(SP_M3,SP_M4*0.5);}
   else if((val_BL2<30&&val_BR2<30)) {BK2(SP_M3*0.4,SP_M4*0.4);}

   if((analog(6)<RefL1)&&(analog(7)<RefBR1)) Value=1; 
  //  else(if)
   else if((analog(6)<RefL1)&&(analog(7)>RefBR1)) //หลัง; ซ้ายดำ ขวาขาว
   {
     AO();delay(5);
     while(analog(7)>RefBR1)//จนกว่าซ้ายหลังจะไม่เจอขาว
     {
       
       motor(1,40);
       motor(2,40);
       motor(3,-80);
       motor(4,-80);
      //  delay(15);
       if(analog(7)<RefBR1) break;
       Value=1;
     }
   }
   else if((analog(6)>RefL1)&&(analog(7)<RefBR1)) //หลัง; ซ้ายขาว ขวาดำ
   {
     AO();delay(5);
     while(analog(6)>RefL1)//จนกว่าซ้ายหลังจะไม่เจอขาว
     {
      
      motor(3,40);
      motor(4,40);
      motor(1,-80);
      motor(2,-80);
      // delay(15);
      if(analog(6)<RefL1)break;
      Value=1;
     }
   }
  }
  AO();delay(50);
}
void BBR(double Degree)
{
  BB();
  AO();delay(100);
  ForwardDelay(Speed,190);MotorStop();delay(50);
  TurnRightDegree(100,Degree,2);
}
void BBL(double Degree)
{
  BB();
  AO();delay(100);
  ForwardDelay(Speed,190);MotorStop();delay(50);
  TurnLeftDegree(100,Degree,2);
}