void Grab_left_1(int Aaa, int S_Speed, int S_Delay, int Time)
{
  TracJCSonar(Aaa);
  S5_up_1();
  S4_down_1();
  MotorStop();

  SL(S_Speed);delay(S_Delay);
  ForwardSpeedTime(SlowSpeed, Time);
  MotorStop();

  S6_grab_gobal();
  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Grab_right_1(int Aaa, int S_Speed, int S_Delay, int Time)
{
  TracJCSonar(Aaa);
  S5_up_1();
  S4_down_1();
  MotorStop();

  SR(S_Speed);delay(S_Delay);
  ForwardSpeedTime(SlowSpeed, Time);
  MotorStop();

  S6_grab_gobal();
  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Grab_gobal_0(int Aaa, int Time)
{ 
  TracJCSonar(Aaa);
  MotorStop();

  S5_up_0();
  S4_down_0();
  ForwardSpeedTime(SlowSpeed, Time);
  MotorStop();

  S6_grab_gobal();
  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Put_left_1(int Aaa, int S_Speed, int S_Delay, int Time)
{
  TracJCSonar(Aaa);
  MotorStop();

  SL(S_Speed);
  delay(S_Delay);
  MotorStop();

  S5_up_1();
  S4_down_1();
  MotorStop();

  S6_put_gobal();
  BackwardSpeedTime(SlowSpeed, Time);
  MotorStop();

  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Put_right_1(int Aaa, int S_Speed, int S_Delay, int Time)
{
  TracJCSonar(Aaa);
  MotorStop();

  SR(S_Speed);
  delay(S_Delay);
  MotorStop();

  S5_up_1();
  S4_down_1();
  MotorStop();

  S6_put_gobal();
  BackwardSpeedTime(SlowSpeed, Time);
  MotorStop();

  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Put_left_2(int Aaa, int S_Speed, int S_Delay, int Time)
{
  TracJCSonar(Aaa);
  MotorStop();

  SL(S_Speed);
  delay(S_Delay);
  MotorStop();

  S5_up_2();
  S4_down_2();
  MotorStop();

  S6_put_gobal();
  BackwardSpeedTime(SlowSpeed, Time);
  MotorStop();

  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Put_right_2(int Aaa, int S_Speed, int S_Delay, int Time)
{
  TracJCSonar(Aaa);
  MotorStop();

  SR(50);
  delay(S_Delay);
  MotorStop();


  S5_up_2();
  S4_down_2();
  MotorStop();

  S6_put_gobal();
  BackwardSpeedTime(SlowSpeed, Time);
  MotorStop();

  S4_up_gobal();
  S5_down_gobal();
  MotorStop();
}

void Put_gobal_3(int Aaa, int Time)
{
  Pre_put_3();

  TracJCSonar(Aaa);
  MotorStop();

  S6_put_gobal();
  BackwardSpeedTime(SlowSpeed, Time);
  MotorStop();

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