void Box4()
{
  TracJC1Back();
  TurnRight();
  BackwardBalance();
  TracJC1();
  TurnLeft();
  BackwardBalance();
  ForwardSpeedTime(Speed,800); 
  TracJC1();
  KickF();
}
void Box4Acc()
{
  TracACCBack(ACCSpeed,450);
  TracJC1Back();
  TurnRight();
  BackwardBalance();
  TracACC(ACCSpeed,300);
  TracJC1();
  TurnLeft();
  BackwardBalance();
  ForwardSpeedTime(ACCSpeed,350); 
  ForwardSpeedTime(60,200);
  TracJC1();
  KickF();
}
void Box4NoTune()
{
  TracJC1Back();
  TurnRight();
  TracJC1();
  TurnLeft();
  ForwardSpeedTime(Speed,700); 
  TracJC1();
  KickF();
}
void Box4Speed()
{
  CurveLeftDegree(100,85,1);
  TracDegreeSpeedTime(ACCSpeed,90,160,0);
  CurveLeftDegree(100,175,1);
  TracDegreeSpeedTime(ACCSpeed,180,250,0); 
  TracJCStop(); 
  KickFBackwardDegree(ACCSpeed,180,430); 
}
void Box4CurveAcc()
{
  TracSpeedTimeBack(ACCSpeed,150);
  CurveLeftDegreeBack(100,260,1); 
  TracSpeedTimeBack(ACCSpeed,130);
  CurveLeftDegreeBack(100,348,1); 
  BackwardSpeedTime(ACCSpeed,300); 
  BackwardSpeedTime(60,200);
  TracJCStopBack(); 
  KickBForward(); 
}
