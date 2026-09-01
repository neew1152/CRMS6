#include <ATX2.h>  
void	setup(){
OK();
}

void    loop()
{
  while(1)
  {
    if(analog(2)<900)
      {
        break;
      }
      else
          {
            fd(30);
          }
  }
	  ao();
}