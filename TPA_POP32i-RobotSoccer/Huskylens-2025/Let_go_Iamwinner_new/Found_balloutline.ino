void Out_line() {
  while (!SW_A()) {
    if (Check_outline) {
      secsion_01();
    } else {
      secsion_02();
    }
  }
}
void secsion_01() {
  while (1) {
    Checkline();
    if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
      ballPosX = huskylens.blockInfo[1][0].x;
      ballPosY = huskylens.blockInfo[1][0].y;
      if (SW_A()) break;
      for (int i = 0; i < 8; i++) {
        getIMU();
      }
      Checkline();
      if (discoveState) {  //วิ่งปรับหุ่นยนต์ให้ใกล้ลูกบอลมากที่สุด discoveState=1
        rot_error = sp_rot - ballPosX;
        rot_d = rot_d + rot_error;
        rot_d = constrain(rot_d, -100, 100);
        rot_d = rot_error - rot_pError;
        rot_pError = rot_error;
        rot_w = (rot_error * 0.35) + (rot_i * rot_Ki) + (rot_d * rot_Kd);
        rot_w = constrain(rot_w, -100, 100);

        fli_error = 160 - ballPosY;
        fli_i = fli_i + fli_error;
        fli_i = constrain(fli_i, -100, 100);
        fli_d = fli_error - fli_pError;
        fli_pError = fli_error;
        fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
        fli_spd = constrain(fli_spd, -100, 100);

        holonomic(fli_spd, 90, rot_w);

        if ((abs(rot_error) < rotErrorGap) && (abs(fli_error) < flingErrorGap)) {
          wheel(0, 0, 0);
          lastYaw = pvYaw;  //บันทึกทิศล่า
          discoveState = 0;
        }
      } else {  //จะทำงานเมื่อเจอลูกบอลแต่ทิศไม่ตรงที่จะยิ่ง
        // หุ่นเลือกทิศทางที่ใกล้ที่สุด ที่จะปรับท้ายหุ่นหาลูกบอล
        if (lastYaw < 0) {
          vecCurve = 0;
          radCurve = 21;
        } else {
          vecCurve = 180;
          radCurve = -21;
        }
        holonomic(40, vecCurve, radCurve);
        if (abs(pvYaw) < alignErrorGap) {      //เมื่อทิศอยู่ในค่าที่รับได้
          rot_error = sp_rot - ballPosX;       //คำนวนหาค่า Error ว่าลูกบอลอยู่ตรงกลางหรือไม่
          if (abs(rot_error) < rotErrorGap) {  //ถ้าลูกบอลอยู่ตรงกลางให้ทำการยิง
            Goal_Outline();
            break;
          }
          discoveState = 1;
        }
      }
    } else {  //หมุนตัวหาลูกบอล
      if (SW_A()) break;
      int sideRot = sp_rot - ballPosX;  //คำนวนทิศการหมุนหาลูกบอลเมื่อเจอล่าสุด
      holonomic(0, 0, sideRot / abs(sideRot) * idleSpd);
      discoveState = 1;  //เตรียมพร้อมไปหาลูกบอลเมื่อเจอบอลอีกครั้ง
    }
  }
}
void secsion_02() {
  better();
}