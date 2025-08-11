#include <ATX2.h>  
void	setup(){
  OK();
  XIO();
}

void	loop(){
  if(analog(1)>600)
  {
   fd(100);
	}
  
  else
  {
   ao();
  }
}
