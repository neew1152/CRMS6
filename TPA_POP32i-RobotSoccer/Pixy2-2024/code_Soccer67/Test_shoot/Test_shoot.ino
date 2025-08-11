#include <POP32.h>
#define limPin PA0
#define reloadSpd 60
void shoot(){
  motor(4,reloadSpd);delay(150);
  motor(4,0);delay(50);
}
void reload(){
  motor(4,reloadSpd);
  for(int i=0;i<2000;i++){
    if(in(limPin))break;
    delay(1);
  }
  motor(4,0);
}
void setup() {}
void loop() {
  if(SW_A()){reload();}
  if(SW_B()){shoot();}
  if(SW_OK()){shoot();reload();}
}
