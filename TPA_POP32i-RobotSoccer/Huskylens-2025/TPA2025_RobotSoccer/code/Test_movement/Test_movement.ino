#include <POP32.h>
void setup() {
}
void loop() {
 waitSW_A_bmp();
 wheel(-18,68,-50); 
 delay(3000);
 ao();
}
void wheel(int s1, int s2, int s3){
  motor(1, s1);
  motor(2, s2);
  motor(3, s3);
}
