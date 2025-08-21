void Goalkeepper() {
  while (1) {
    SetRobot();
    if (huskylens.updateBlocks() && huskylens.blockSize[1]) {  //เมื่อเจอลูกบอล ID 1
      if (SW_A()) break;
      updateIMU();
      /* คำนวน ค่าความเร็วในแนวแกน x */
      ballPosX = huskylens.blockInfo[1][0].x;
      rot_error = 160 - ballPosX;
      rot_i = rot_i + rot_error;
      rot_i = constrain(rot_i, -100, 100);
      rot_d = rot_error - rot_pError;
      rot_pError = rot_error;
      rot_w = (rot_error * 2.0) + (rot_i * rot_Ki) + (rot_d * 0.35);
      rot_w = constrain(rot_w, -90, 90);

      /* คำนวน ค่าความเร็วในแนวแกน y */
      ballPosY = huskylens.blockInfo[1][0].y;
      fli_error = spFli - ballPosY;
      fli_i = fli_i + fli_error;
      fli_i = constrain(fli_i, -100, 100);
      fli_d = fli_error - fli_pError;
      fli_pError = fli_error;
      fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
      fli_spd = constrain(fli_spd, -100, 100);
      side = (rot_w > 0 ? 180 : 0);  // ให้เลือกว่าจะ slide ฝั่งไหน
      heading(abs(rot_w), side, 0);
      Checkline_Goalkeeper();
    } else {
      if (SW_A()) break;
      SetRobot();
      Checkline_Goalkeeper();
      if(sensor == 1)
      {
        updateIMU();
        heading(20,0,0);
      }
      else if(sensor == 2)
      {
        updateIMU();
        heading(20,180,0);
      }
      else
      {
        updateIMU();
        heading(20,side,0);
      }
    }
  }
}