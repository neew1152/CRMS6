void Box2()
{ 
  TracSpeedTimeBack(Speed,700);
  TurnRight();
  BackwardBalance();
  TracJC1();
  TurnLeft();
  BackwardBalance();
  TracJC1();
  KickF(); 
}
void Box2Acc()
{ 
  TracSpeedTimeBack(ACCSpeed,420);
  TurnRight();
  BackwardBalance();
  TracACC(ACCSpeed,300);
  TracJC1();
  TurnLeft();
  BackwardBalance();
  TracACC(ACCSpeed,400);
  TracJC1();
  KickF();  
}
void Box2NoTune()
{ 
  TracSpeedTimeBack(Speed,700);
  TurnRight();
  TracJC1();
  TurnLeft();
  TracJC1();
  KickF(); 
}
void Box2Speed()
{ 
  CurveLeftDegree(100,85,1);
  TracDegreeSpeedTime(ACCSpeed,90,140,0);
  CurveLeftDegree(100,175,1);
  TracDegreeSpeedTime(ACCSpeed,180,250,0);  
  TracJCStop(); 
  KickFBackwardDegree(ACCSpeed,180,230); 
}
void Box2CurveAcc()
{ 
  TracSpeedTimeBack(ACCSpeed,150);
  CurveLeftDegreeBack(100,260,1); 
  TracSpeedTimeBack(ACCSpeed,140);
  CurveLeftDegreeBack(100,352,1); 
  TracSpeedTimeBack(ACCSpeed,250);
  TracJCStopBack(); 
  KickBForward(); 
}
