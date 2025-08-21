void discoverball()  //ค้นหาลูกบอล
{
  if (Mode == 1) {
    Checkline();
    SetRobot();
    StartTimer();
    while (!(huskylens.updateBlocks() && huskylens.blockSize[1])) {
      Checkline();
      if(SW_A()) break;
      else if (B > 2000) {
        check = 1;
        Status = 1;
        Mode = 2;
        break;  //ตรงนี้มีการเปลี่ยนโหมดเเล้ว
      } else if(Sideball == 1){
        while(!(huskylens.updateBlocks() && huskylens.blockSize[1]))
        {
          Checkline();
          if(SW_A()) break;
          else if(millis() -Timer > 400)
          {
            Mode = 1;
            Sideball = 0;
            break;
          }
          else
          {
            updateIMU();
            heading(90, 260, 0);
          }
        }
      } else if(Sideball == 2)
      {
        while(!(huskylens.updateBlocks() && huskylens.blockSize[1]))
        {
          Checkline();
          if(SW_A()) break;
          else if(millis() -Timer > 400)
          {
            Mode = 1;
            Sideball = 0;
            break;
          }
          else
          {
            updateIMU();
            heading(90, 290, 0);
          }
        }
      } else
      {
        updateIMU();
        heading(90, 270, 0);
      }
    }
  } else /* Mode = 2 */
  {
    Checkline();
    SetRobot();
    while (!(huskylens.updateBlocks() && huskylens.blockSize[1])) {
      Checkline();
      if(SW_A()) break;
      else if (check) {
        SetRobot();
        StartTimer();
        while (!(huskylens.updateBlocks() && huskylens.blockSize[1])) {
          Checkline();
          if(SW_A()) break;
          else if (millis() - Timer > 1000) {
            check = 0;
            Status = 0;
            Queue = 0;
            return false;
          } else {
            updateIMU();
            heading(70,0,0);
          }
        }
        break;
      } else {
        SetRobot();
        holonomic(0,0,0);
        StartTimer();
        while (!(huskylens.updateBlocks() && huskylens.blockSize[1])) {
          Checkline();
          if(SW_A()) break;
          else if (millis() - Timer > 2000) {
            check = 0;
            Queue = 1;
            return false;
          } else if(Queue)
          {
            SetRobot();
            holonomic(0,0,0);
            StartTimer();
            while (!(huskylens.updateBlocks() && huskylens.blockSize[1]))
            {
              Checkline();
              if(SW_A()) break;
              else if(millis() - Timer > 1000)
              {
                Mode = 1;
                return false;
              }
              else
              {
                updateIMU();
                heading(70,0,0);
              }
            }
          } 
          else {
            updateIMU();
            heading(70,180,0);
          }
        }
      }
    }
  }
  Mode = 1;
  discoveState = 1;
}
void New_discoverball() {
  if (Mode == 1) {
    SetRobot();
    StartTimer();
    while (!(huskylens.updateBlocks() && huskylens.blockSize[1])) {
      if (millis() - Timer > 2000) {
        A = 0;
        Count_dissball = 0;
        Status = 1;
        Mode = 2;
        return false;  //ยังคงค้างที่ Mode 1
      } else if (B > 2000) {
        A = 0;
        Count_dissball = 0;
        Status = 1;
        Mode = 2;
        return false;  //ตรงนี้มีการเปลี่ยนโหมดเเล้ว
      } else {
        Checkline();
        updateIMU();
        heading(90, 270, 0);
      }
    }
  } else /*  Mode = 2*/
  {

    if (Status) {
      Checkline();
      StartTimer();
      while (true) {
        Checkline();
        if (SW_A()) return false;
        else if (huskylens.updateBlocks() && huskylens.blockSize[1]) {
          discoveState = 1;
          return false;
        } else if (Count_dissball == 2) {
          Status = 0;
          return false;
        }
      }
    } else /*  Status = 0 */
    {
      SetRobot();
      Checkline();
      StartTimer();
      while (!(huskylens.updateBlocks() && huskylens.blockSize[1])) {
        Checkline();
        if (millis() - Timer > 400) {
          Count_dissball = 0;
          Status = 1;
          break;
        } else {
          updateIMU();
          heading(60, 270, 0);
        }
      }
    }
  }
  discoveState = 1;
}