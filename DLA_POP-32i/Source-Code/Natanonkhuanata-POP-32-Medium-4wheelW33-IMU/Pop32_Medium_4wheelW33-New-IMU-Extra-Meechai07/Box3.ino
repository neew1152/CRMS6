void Box3()
{
  TracSpeedTimeBack(Speed,250);
  TurnRight();
  BackwardBalance();
  TracSpeedTime(Speed,580);
  TurnLeft();
  TracJC1();
  KickF(); 
}
void Box3Acc()
{
  TracSpeedTimeBack(ACCSpeed,180);
  TurnRight();
  BackwardBalance();
  TracSpeedTime(ACCSpeed,340);
  TurnLeft();
  TracJC1();
  KickF();  
}
void Box3NoTune()
{
  TracSpeedTimeBack(Speed,250);
  TurnRight();
  TracSpeedTime(Speed,420);
  TurnLeft();
  TracJC1();
  KickF(); 
}
void Box3Speed()
{
  CurveLeftDegreeBack(100,265,1);
  TracDegreeSpeedTimeBack(ACCSpeed,270,160,0);
  CurveLeftDegreeBack(100,355,1);  
  TracJCStopBack(); 
  KickBForwardDegree(ACCSpeed,0,420); 
}
void Box3CurveAcc()
{
  CurveLeftDegree(100,80,1); 
  TracSpeedTime(ACCSpeed,130);
  CurveLeftDegree(100,170,1); 
  TracJCStop(); 
  KickFBackward(); 
}
