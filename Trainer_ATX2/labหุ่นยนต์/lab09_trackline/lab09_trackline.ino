#include <ATX2.h>  
void	setup(){
  OK();
  XIO();
}

void	loop() {
if (analog(1) > 600 && analog(3) > 600)
  {fd(100); }
else if (analog(1) > 600 && analog(3) < 600)
	{tr(30); }
else if (analog(1) < 600 && analog(3) > 600)
	{tr(30); }
}
