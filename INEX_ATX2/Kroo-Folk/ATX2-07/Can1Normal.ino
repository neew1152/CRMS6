void Can1Normal()
{
  Forward(Speed, 250);
  TracJC(Speed, 125);
  TracJC(Speed, 150);
  TracJC(Speed, 125);
  TurnLeft();
  
  TracNormalTime(Speed, 900);
  Backward(Speed, 250);
  UTurn();
  TracJC(Speed, 125);
  TurnRight();
  TracJC(Speed, 150);
  TracJC(Speed, 125);
  TurnLeft();
  TracJC(Speed, 150);
  TurnRight();
  TracNormalTime(Speed, 450);

  UTurn();
  TracJC(Speed, 125);
  TurnLeft();
  TracJC(Speed, 125);
  TurnRight();
}