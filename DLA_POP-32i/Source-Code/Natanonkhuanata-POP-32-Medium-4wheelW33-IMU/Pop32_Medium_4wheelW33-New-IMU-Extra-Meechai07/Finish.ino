void Finish() {
  long int RunningTime;
  RunningTime = ReadTimer2(); 
  AO();
  beep(200);
  oled.clear();
  oled.textSize(1);
  oled.text(0,0,"   Finish.   ");
  oled.text(2,0,"Running Time.");
  oled.text(4,0,"%l.%l seconds", RunningTime/1000, RunningTime%1000);
  oled.show();
  while(1){};
}
void FinishWaitOK() {
  long int RunningTime;
  RunningTime = ReadTimer2(); 
  AO();
  beep(1);
  oled.clear();
  oled.textSize(1);
  oled.text(0,0,"   Finish.   ");
  oled.text(2,0,"Running Time.");
  oled.text(4,0,"%l.%l seconds ", RunningTime/1000, RunningTime%1000);
  oled.text(6,0,"  Press SW OK ");
  oled.show();
  Wait_sw_ok_press(); //รอจนกว่าจะกด SW OK
  beep(0);
  oled.text(0,0,"   Running   ");
  oled.show();
}
