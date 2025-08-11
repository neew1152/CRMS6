void Grab_left_1()
{
  TracJCSonar(15);
  S5_up_1();
  S4_down_1();
  MotorStop();

  SL(50);delay(100);
  ForwardSpeedTime(20, 800);
  MotorStop();

  S6_grab_gobal();
  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Put_left_2()
{
  TracJCSonar(4);
  MotorStop();

  SL(50);
  delay(200);
  MotorStop();

  S5_up_2();
  S4_down_2();
  MotorStop();

  S6_put_gobal();
  BackwardSpeedTime(40, 250);
  MotorStop();

  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Put_right_2()
{
  TracJCSonar(4);
  MotorStop();

  SR(50);
  delay(150);
  MotorStop();


  S5_up_2();
  S4_down_2();
  MotorStop();

  S6_put_gobal();
  BackwardSpeedTime(40, 250);
  MotorStop();

  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Grab_right_1()
{
  TracJCSonar(15);
  S5_up_1();
  S4_down_1();
  MotorStop();

  SR(50);delay(150);
  ForwardSpeedTime(20, 800);
  MotorStop();

  S6_grab_gobal();
  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Put_left_1()
{
  TracJCSonar(7);
  MotorStop();

  SL(50);
  delay(150);
  MotorStop();

  S5_up_1();
  S4_down_1();
  MotorStop();

  S6_put_gobal();
  BackwardSpeedTime(40, 250);
  MotorStop();

  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}


void Put_right_1()
{
  TracJCSonar(7);
  MotorStop();

  SR(50);
  delay(150);
  MotorStop();

  S5_up_1();
  S4_down_1();
  MotorStop();

  S6_put_gobal();
  BackwardSpeedTime(40, 250);
  MotorStop();

  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Grab_gobal_0()
{ 
  TracJCSonar(15);
  MotorStop();

  S5_up_0();
  S4_down_0();
  ForwardSpeedTime(20, 800);
  MotorStop();

  S6_grab_gobal();
  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Pre_put_3()
{
  Pre_S5_up_3();
  Pre_S4_down_3();
  Pre_S6_put();

  S4_down_3();
  S5_up_3();
  MotorStop();
}

void Put_gobal_3()
{
  Pre_put_3();

  TracJCSonar(2);
  MotorStop();

  S6_put_gobal();
  BackwardSpeedTime(40, 250);
  MotorStop();

  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}




void S6_grab_gobal() 
{
  servo(6, 120);
  delay(500);
}

void S6_put_gobal()
{
  servo(6, 20);
  delay(500);
}

void Pre_S6_put()
{
  servo(6, 100);
  delay(1000);
  S6_grab_gobal();
}

void S4_up_gobal()
{
  servo(4, 110);
  delay(500);
}

void S5_down_gobal() 
{
  servo(5, 15);
  delay(500);
}



void S5_up_0()
{
  servo(5, 200);
  delay(500);
}

void S5_up_1()
{
  servo(5, 150);
  delay(500);
}

void S5_up_2()
{
  servo(5, 80);
  delay(500);
}

void S5_up_3()
{
  servo(5, 40);
  delay(500);
}

void Pre_S5_up_3()
{
  servo(5, 150);
  delay(500);
}

void Pre_S4_down_3()
{
  servo(4, 0);
  delay(500);
}



void S4_down_0()
{
  servo(4, 0);
  delay(500);
}

void S4_down_1()
{
  servo(4, 20);
  delay(500);
}

void S4_down_2()
{
  servo(4, 55);
  delay(500);
}

void S4_down_3()
{
  servo(4, 95);
  delay(500);
}







void Startprogramservo() {
  servo(6, 35);
  delay(200);
  servo(5, 0);
  delay(200);
  servo(4, 116);
  delay(200);
}
void LadyGrip() {
  servo(5, 150);
  delay(200);
  servo(4, 19);
  sound(300, 2000);
}
void LedyPut() {
  servo(4, 116);
  delay(200);
  servo(5, 0);
  delay(200);
}
void Grip() {
  servo(6, 110);
  delay(200);
}


// void Box1gripL()
// {
//   S5();
//   s4();
//   ao();
//   SL(60);
//   delay(200);
//   MotorStop();
//   FD2(40, 40);
//   delay(275);
//   ao();
//   s6();
//   S4();
//   s5();
//   ao();
//   SR(60);
//   delay(135);
//   MotorStop();
// }
// void Box1gripR()
// {
//   S5();
//   s4();
//   ao();
//   SR(60);
//   delay(135);
//   MotorStop();
//   FD2(40, 40);
//   delay(275);
//   ao();
//   s6();
//   S4();
//   s5();
//   ao();
//   SL(60);
//   delay(135);
//   MotorStop();
// }