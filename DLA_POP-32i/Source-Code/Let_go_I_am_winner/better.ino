void better() {
  reload();
  while (true) {
    Checkline();
    if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
      SetRobot();
      if (SW_A()) return false;
      ballPosX = huskylens.blockInfo[1][0].x;
      ballPosY = huskylens.blockInfo[1][0].y;
      if (Checkball) {
        if (ballPosX > 165) {
          Sideball = 1;
          Checkball = 0;
        } else if (Sideball < 155) {
          Sideball = 2;
          Checkball = 0;
        }
      }
      for (int i = 0; i < 8; i++) {
        getIMU();
      }
      Checkline();
      if (discoveState) { /*            วิ่งเข้าลูกบอลเมื่อ slide เสร็จ   */
        /*   คำนวน ค่าความเร็วในแนวแกน x   */
        rot_error = sp_rot - ballPosX;
        rot_i = rot_i + rot_error;
        rot_i = constrain(rot_i, -100, 100);
        rot_d = rot_error - rot_pError;
        rot_pError = rot_error;
        rot_w = (rot_error * rot_Kp_slide) + (rot_i * rot_Ki) + (rot_d * rot_Kd);
        rot_w = constrain(rot_w, -70, 70);


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
        if ((abs(rot_error) < rotErrorGap) && (abs(fli_error) < flingErrorGap)) {
          discoveState = 0;
        } else {
          if (abs(rot_error) < rotErrorGap) {  //ถ้าลูกบอลอยู่ตรงกลางให้ทำการยิง
            heading(fli_spd, 90, 0);

          } else {
            heading(abs(rot_w), side, 0);
          }
          discoveState = 1;
        }

      } else {
        CheckGoalyellow_better();
      }
    } else {
      if (SW_A()) return false;
      SetRobot();
      discoverball();
    }
  }
}
