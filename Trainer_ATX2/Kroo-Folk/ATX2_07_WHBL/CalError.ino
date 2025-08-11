void Initial7ADC()
{
  RefL3 = 803;
  RefL2 = 809;
  RefL1 = 738;
  RefC = 778;
  RefR1 = 818;
  RefR2 = 779;
  RefR3 = 774;
}

void Read7ADC()
{
  L3 = analog(2);
  L2 = analog(3);
  L1 = analog(4);
  C = analog(5);
  R1 = analog(6);
  R2 = analog(7);
  R3 = analog(8);
}

void Convert7ADC() // 0 = black 1 = white
{
  Read7ADC();
  if(L3 < RefL3) L3 = 0;
    else L3 = 1;

  if(L2 < RefL2) L2 = 0;
    else L2 = 1;

  if(L1 < RefL1) L1 = 0;
    else L1 = 1;

  if(C < RefC) C = 0;
    else C = 1;

  if(R1 < RefR1) R1 = 0;
    else R1 = 1;

  if(R2 < RefR2) R2 = 0;
    else R2 = 1;

  if(R3 < RefR3) R3 = 0;
    else R3 = 1; 
}

void Show7ADC()
{
  Read7ADC();
  glcdClear();
  glcdFillScreen(GLCD_BLUE);
  glcdMode(3);
  setTextColor(GLCD_RED);
  setTextSize(1);
  glcd(0, 0, "L3 = %d", L3);
  glcd(1, 0, "L2 = %d", L2);
  glcd(2, 0, "L1 = %d", L1);
  glcd(3, 0, "C = %d", C);
  glcd(4, 0, "R1 = %d", R1);
  glcd(5, 0, "R2 = %d", R2);
  glcd(6, 0, "R3 = %d", R3);
}

void CalError()
{
  Convert7ADC();
  if((L3 == 1) && (L2 == 1) && (L1 == 1) && (C == 1) && (R1 == 1) && (R2 == 1) && (R3 == 0)) Error = 6;
  else if((L3 == 1) && (L2 == 1) && (L1 == 1) && (C == 1) && (R1 == 1) && (R2 == 0) && (R3 == 0)) Error = 5;
  else if((L3 == 1) && (L2 == 1) && (L1 == 1) && (C == 1) && (R1 == 1) && (R2 == 0) && (R3 == 1)) Error = 4;
  else if((L3 == 1) && (L2 == 1) && (L1 == 1) && (C == 1) && (R1 == 0) && (R2 == 0) && (R3 == 1)) Error = 3;
  else if((L3 == 1) && (L2 == 1) && (L1 == 1) && (C == 1) && (R1 == 0) && (R2 == 1) && (R3 == 1)) Error = 2;
  else if((L3 == 1) && (L2 == 1) && (L1 == 1) && (C == 0) && (R1 == 0) && (R2 == 1) && (R3 == 1)) Error = 1;
  else if((L3 == 1) && (L2 == 1) && (L1 == 1) && (C == 0) && (R1 == 1) && (R2 == 1) && (R3 == 1)) Error = 0;
  else if((L3 == 1) && (L2 == 1) && (L1 == 0) && (C == 0) && (R1 == 1) && (R2 == 1) && (R3 == 1)) Error = -1;
  else if((L3 == 1) && (L2 == 1) && (L1 == 0) && (C == 1) && (R1 == 1) && (R2 == 1) && (R3 == 1)) Error = -2;
  else if((L3 == 1) && (L2 == 0) && (L1 == 0) && (C == 1) && (R1 == 1) && (R2 == 1) && (R3 == 1)) Error = -3;
  else if((L3 == 1) && (L2 == 0) && (L1 == 1) && (C == 1) && (R1 == 1) && (R2 == 1) && (R3 == 1)) Error = -4;
  else if((L3 == 0) && (L2 == 0) && (L1 == 1) && (C == 1) && (R1 == 1) && (R2 == 1) && (R3 == 1)) Error = -5;
  else if((L3 == 0) && (L2 == 1) && (L1 == 1) && (C == 1) && (R1 == 1) && (R2 == 1) && (R3 == 1)) Error = -6;
  else if((L3 == 0) && (L2 == 0) && (L1 == 0) && (C == 0) && (R1 == 0) && (R2 == 0) && (R3 == 0)) Error = 100;
  else if((L3 == 0) && (L2 == 0) && (L1 == 0)) Error = 101;
  else if((R1 == 0) && (R2 == 0) && (R3 == 0)) Error = 102;
}