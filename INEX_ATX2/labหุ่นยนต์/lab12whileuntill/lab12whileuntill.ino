#include <ATX2.h>  
void	setup(){
  OK();
  XIO();
}

void  loop()
{
  while(true){
    if(analog(1)<600&&analog(3)<600)
      {
        break;
      }
    else
      {trackline(100);}
}
  ao();
}

void trackline(int speed)
{
    if(analog(1)>600&&analog(3)>600)
    {fd(speed); }
    else if(analog(1)>600&&analog(3)<600)
    { tr(speed);}
    else if(analog(1)<600&&analog(3)>600)
    { tl(speed);}
}