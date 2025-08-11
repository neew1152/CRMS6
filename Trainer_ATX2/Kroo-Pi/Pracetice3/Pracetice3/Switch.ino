char Read_sw_OK()  {
  if (SW_OK()) return(1);     //press sw OK
  //else if(digitalRead(18)==0) {digital_sw = 1; return(1);}  //press digital sw 
  else 
  {
    delay(10);
    if (SW_OK()) return(1);     //press sw OK
    else return(0);
  }
}
void sw_ok_unpress()  {
  while(Read_sw_OK()) {delay(10);}
}
void Wait_sw_ok_press()  {
  while(Read_sw_OK()==0) {delay(10);}
}
