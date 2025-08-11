void better() {
  while (1) {
    if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
      if (SW_A()) break;
      Checkline();
      ballPosX = huskylens.blockInfo[1][0].x;
      ballPosY = huskylens.blockInfo[1][0].y;
      for (int i = 0; i < 8; i++) {
        getIMU();
      }
      if (discoveState) {  //วิ่งปรับหุ่นยนต์ให้ใกล้ลูกบอลมากที่สุด discoveState=1
        rot_error = sp_rot - ballPosX;
        rot_d = rot_d + rot_error;
        rot_d = constrain(rot_d, -100, 100);
        rot_d = rot_error - rot_pError;
        rot_pError = rot_error;
        rot_w = (rot_error * rot_Kp) + (rot_i * rot_Ki) + (rot_d * rot_Kd);
        rot_w = constrain(rot_w, -100, 100);

        fli_error = spFli - ballPosY;
        fli_i = fli_i + fli_error;
        fli_i = constrain(fli_i, -100, 100);
        fli_d = fli_error - fli_pError;
        fli_pError = fli_error;
        fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
        fli_spd = constrain(fli_spd, -100, 100);

        holonomic(fli_spd, 90, rot_w);

        if ((abs(rot_error) < rotErrorGap) && (abs(fli_error) < flingErrorGap)) {  //เจอลูกบอล
          //wheel(0, 0, 0);
          lastYaw = pvYaw;  //บันทึกทิศล่า
          discoveState = 0;
        }
      } else {  //จะทำงานเมื่อเจอลูกบอลแต่ทิศไม่ตรงที่จะยิ่ง
        // หุ่นเลือกทิศทางที่ใกล้ที่สุด ที่จะปรับท้ายหุ่นหาลูกบอล
        if (lastYaw < 0) {
          vecCurve = 0;
          radCurve = 15;
        } else {
          vecCurve = 180;
          radCurve = -15;
        }
        holonomic(50, vecCurve, radCurve);
        if (abs(pvYaw) < alignErrorGap) {  //เมื่อทิศอยู่ในค่าที่รับได้
          wheel(0, 0, 0);
          discoveState = 1;
          rot_error = sp_rot - ballPosX;       //คำนวนหาค่า Error ว่าลูกบอลอยู่ตรงกลางหรือไม่
          if (abs(rot_error) < rotErrorGap) {  //ถ้าลูกบอลอยู่ตรงกลางให้ทำการยิง
            holonomic(0,0,0); // ช้าเเล้วเร็วจะดันได้ดี
            delay(1000);
            sound(3000,100);
            holonomic(100, 90, 0);              //เดินหน้าตรงความเร็ว 50%
            delay(3000);
          }
          discoveState = 1;
        }
      }
    } else {  //ไม่เจอลูกบอล ให้หมุน 1 วิ เสร็จเเล้วทำตัวให้ตรง
      if (SW_A()) break;
      Checkline();
      int sideRot = sp_rot - ballPosX;  //คำนวนทิศการหมุนหาลูกบอลเมื่อเจอล่าสุด
      if (discoveState)                 // เจอลูกบอลมาก่อน
      {
        StartTimer();
        while (1) {
          if (SW_A()) break;
          else if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
            discoveState = 1;
            break;
          } else if (millis() - Timer > 2000)  // ให้ถอยไปตำเเหน่งถัดไป
          {
            discoveState = 0;
            break;
          } else {  // หมุนหาจากทิศที่เคยเจอ
            holonomic(0, 0, sideRot / abs(sideRot) * idleSpd);
          }
        }
      } else  // ไม่เจอลูกบอลมาก่อน
      {
        StartTimer();
        while (1) {
          if (SW_A()) break;
          else if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
            discoveState = 1;
            break;
          } else if (millis() - Timer > Time)  // ให้ไปหมุนหาตำเเหน่ง ถัดไป
          {
            Count++;
            discoveState = 1;
            break;
          } else if (Count % 2 == 0)  // เดินหน้าบ้าง ถ้าหาร 2 เเล้วได้เศษ 0
          {
            Time = 2000;
            holonomic(50, 90, 0);
          } else {
            Time = 1000;
            holonomic(50, 270, 0);
          }
        }
      }
    }
  }
}
