#include <ATX2.h>  
void	setup(){
OK();
}

void  loop()
{
  while(1)
  {
    if (analog(2) > 600 && analog(4) > 600)
      {
        fd(30);
      }

    else if (analog(2) > 600 && analog(4) < 600)
				{
          sr(30);
        }

    else if (analog(2) < 600 && analog(5) > 600)
				{
          sl(30);
        }

  }
  	ao();
		while(1);
}
