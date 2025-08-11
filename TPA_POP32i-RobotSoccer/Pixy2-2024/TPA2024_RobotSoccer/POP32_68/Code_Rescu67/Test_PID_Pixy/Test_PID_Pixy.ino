#include <POP32.h>
#include <POP32_Pixy2.h>
POP32_Pixy2 pixy;
#define MAX_Spd 70
#define head_Kp 0.5
#define head_Ki 0.0
#define head_Kd 0.0
float head_sp = 150;
float head_error, hI, hD, hPrevError, head_spd;

#define MAX_Spd 70
#define dis_Kp 0.5
#define dis_Ki 0.0
#define dis_Kd 0.0
float dis_sp = 140; // distance setpoint y
float dis_error, dI, dD , dPrevError, dis_spd;

void setup() {
  pixy.init();
  waitAnykey_bmp();
}
void loop() {
  if (pixy.updateBlocks() && pixy.sigSize[1]) {
    int x = pixy.sigInfo[1][0].x;
    head_error = head_sp - x;
    hI = hI + head_error;
    hI = constrain(hI, -MAX_Spd, MAX_Spd);
    hD = head_error - hPrevError;
    head_spd = (head_Kp * head_error) + (hI * head_Ki) + (hD * head_Kd) ;

    int y = pixy.sigInfo[1][0].y;
    dis_error = dis_sp - y;
    dI = dI + dis_error;
    dI = constrain(dI, -MAX_Spd, MAX_Spd);
    dD = dis_error - dPrevError;
    dis_spd = (dis_Kp * dis_error) + (dI * dis_Ki) + (dD * dis_Kd);

    const int h_gap = 15;
    const int d_gap = 15;
    if ((abs(head_error) < h_gap) && (abs(dis_error) < d_gap)) {
      motor(1, 0);
      motor(2, 0);
      beep();
    } else {
      int leftSpeed = constrain(dis_spd - head_spd, -MAX_Spd, MAX_Spd);
      int rightSpeed = constrain(dis_spd + head_spd, -MAX_Spd, MAX_Spd);
      motor(1, leftSpeed); motor(2, rightSpeed);
    }
    
    hPrevError = head_error;
    dPrevError = dis_error;
  }
}
