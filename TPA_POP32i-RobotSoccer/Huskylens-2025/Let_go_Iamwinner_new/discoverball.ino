void discoverball()  //ค้นหาลูกบอล
{
  if (Mode == 1) {
    SetRobot();
    StartTimer();
    while (!(huskylens.updateBlocks() && huskylens.blockSize[1])) {
      if (millis() - Timer > 2000) {
        A = 0; Count_dissball = 0; Status = 1;  Mode = 2; return false; //ยังคงค้างที่ Mode 1
      }
      else if (B > 2000) {
        A = 0; Count_dissball = 0; Status = 1; Mode = 2; return false;  //ตรงนี้มีการเปลี่ยนโหมดเเล้ว
      }
      else 
      {
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
        }else if(Count_dissball == 2 && A == 1)
        {
          Mode = 1;
          return false;
        }
        else if(Count_dissball == 2 && A == 0)
        {
          Status = 0;
          return false;
        } 
        else if(millis() - Timer > Time)
        {
          if(check == 1)
          {
            Round = 1;
            if(Round == 1)
            {
              Time = 1200;
            }
            else 
            {
              Time = 600;
            }
            Count_dissball ++;
            check = 2;
            return false;
          }
          else 
          {
            Round = 2;
            if(Round == 1)
            {
              Time = 600;
            }
            else
            {
              Time = 1200;
            }
            Count_dissball ++;
            check = 1;
            return false;
          }
          
        } else {
          if(check == 1)
          {
            updateIMU();
            heading(80, 180, 0);
          }
          else
          {
            updateIMU();
            heading(80, 0, 0);
          }
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
          A = 1;
          Count_dissball = 0;
          Status = 1;
          break;
        } else {
          updateIMU();
          heading(70, 90, 0);
        }
      }
    }
  }
  discoveState = 1;
}