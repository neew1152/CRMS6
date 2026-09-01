#include <ATX2.h>  
void	setup(){
  OK();
  XIO();
}

void	loop(){
  while(analog(3) < 600)
  	{
   		trackline(30);
  	}
  fd(50);
  delay(1000);
  ao();
  delay(1000);

  while(analog(3) < 600)
  	{
   		trackline(30);
  	}
  fd(50);
  delay(1000);
  ao();
  delay(1000);

  while(analog(6) < 600)
  	{
    	sr(30);
  	}
    
    while(analog(3) < 600)
  	{
   		trackline(30);
  	}
  fd(50);
  delay(1000);
  ao();
  delay(1000);

  while(analog(3) < 600)
  	{
   		trackline(30);
  	}
  fd(50);
  delay(1000);
  ao();
  delay(1000);

  while(analog(3) < 600)
  	{
   		trackline(30);
  	}
  fd(50);
  delay(1000);
  ao();
  delay(1000);

  while(analog(3) < 600)
  	{
    		sl(30);
  	}

    while(analog(3) < 600)
  	{
   		trackline(30);
  	}
  fd(50);
  delay(1000);
  ao();
  delay(1000);

  while(analog(3) < 600)
  	{
   		trackline(30);
  	}
  fd(50);
  delay(1000);
  ao();
  delay(1000);

  while(analog(3) < 600)
  	{
   		trackline(30);
  	}
  fd(50);
  delay(1000);
  ao();
  while(1);
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