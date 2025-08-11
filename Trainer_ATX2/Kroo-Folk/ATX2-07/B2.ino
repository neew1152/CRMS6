void B2()
{
  TracJC(Speed, 115);
  T8R(250);
  Forward(Speed, 100);
  TracNormalTime(Speed, 850);
  UTurn();
  TracJC(Speed, 150);
  T8L(150);
  TracJC(Speed, 125);
  T8R(250);
  TracJC(Speed, 125);
  T8L(150);
  TracNormalTime(Speed, 450);
  UTurn();
  TracJC(Speed, 125);
  TurnRight();
  TracJC(Speed, 125);
  TurnLeft();
}