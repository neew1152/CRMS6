void Black()
{
  T8R(150);
  TracJC(Speed, 125);
  TurnLeft();
  TracTime(Speed, 450);
  Compled_Put();
  Backward(Speed, 150);
  UTurn();
  TracJC(Speed, 125);
  TurnRight();
  TracJC(Speed, 125);
  T8L(150);
}

void White()
{
  T8L(150);
  TracJC(Speed, 150);
  T8R(150);
  TracTime(Speed, 450);
  Compled_Put();
  Backward(Speed, 100);
  UTurn();
  TracJC(Speed, 100);
  T8L(175);
  TracJC(Speed, 125);
  T8R(150);
}