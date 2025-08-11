#include <POP32.h>

  int Speed, SlowSpeed, ACCSpeed, BaseSpeed, LeftBaseSpeed, RightBaseSpeed, TurnSpeed, MaxSpeed, SonarSpeed, DistanceRef;
  int Error, PreError, Kp, Kd, Ki, Kt, KpB, KdB, KiB, KtB, BackLeftBaseSpeed, BackRightBaseSpeed, KpChange; 
  int RefL2, RefL1, RefC, RefR1, RefR2,  SumError,  RefBL2,  RefBL1, RefBR1, RefBR2;
  int L2, L1, C, R1, R2, BL2, BL1, BR1, BR2;
  long Timer, Timer2, Timer3;
  int SW_OK_Status,digital_sw=0;
  
  #define SW_pin 18
  #define No 0
  #define Yes 1

  #define Mode0 0
  #define Mode1 1
  #define Mode2 2
  #define Mode3 3
  #define Mode4 4
  
 #define WheelDrive  1   //0:ขับเคลื่อน 2 ล้อ , 1:ขับเคลื่อน 4 ล้อ
 int PidStatus=0;         //0:ใช้ล้อข้างเดียว 1:ใช้ล้อ 2 ข้าง
 
float pvYaw;
uint8_t rxCnt = 0, rxBuf[8];
int RobotMode=Mode0;
int KnobBase;
int TurnStatus=1;   //0:เลี้ยวหน่วงเวลา 1:เลี้ยวใช้เข็มทิศ

void setup() {
  Speed = 60;
  ACCSpeed =100;
  SlowSpeed = 50;
  BaseSpeed = Speed; 
  TurnSpeed = 100;
  InitialSpeed();
  InitialRef();
  //ServoCloseF();
  //ServoCloseB();
  beep(0);
  oled.clear();                 //เคลียร์หน้าจอ
  oled.mode(0);                 //หมุนหน้าจอ 0 องศา
  oled.dim(true);               //ปรับความสว่างปกติ
  oled.textSize(1);             //กำหนดขนาดตัวอักษร
  oled.text(0,0,"  Ubon TP Robotics"); //กำหนดข้อความที่จะแสดง
  oled.text(1,0,"Medium POP32i-IMU-500");
  oled.text(2,0,"      MEECHAI    ");
  oled.text(3,0,"     Speed = %d   ",Speed);
  oled.text(4,0,"     ACCSpeed=%d",ACCSpeed);
  oled.text(5,0,"       Mode = %d   ",RobotMode);
  ShowTurnStatus();
  oled.show();                  //แสดงบนหน้าจอ
  SW_OK_Status = No;
  KnobBase=knob();
  while(SW_OK_Status == No)  {  // waiting "OK" button
      if(Read_sw_OK()) {
        InitSerial1();
        StartTimer();
        beep(1);
        SW_OK_Status = Yes;
        while(Read_sw_OK())  {  //wait unpress OK button
        if(ReadTimer() >= 2000) {
          beep(2);
          KickF();                  //ทดสอบชุดปล่อย
          KickB();
          Show7Analog();
          SW_OK_Status = No;
          }
        }
       }
       else CheckKnobMode();  //เช็คดูว่ามีการปรับค่า knob เพื่อเปลี่ยนการเลี้ยว
       if(SW_A()) 
       {
          InitSerial1();
          StartTimer();
          beep(1);
          while(SW_A())  {}  //wait unpress SW A button
          if(ReadTimer() >= 200) RobotMode=Mode1; 
          else  RobotMode=Mode2;  
          SW_OK_Status = Yes;
       }
       if(SW_B()) 
       {
          InitSerial1();
          StartTimer();
          beep(1);
          while(SW_B())  {}  //wait unpress SW A button
          if(ReadTimer() >= 200) RobotMode=Mode3; 
          else  RobotMode=Mode4;  
          SW_OK_Status = Yes;
       }
  }
  zeroYaw();
  BaseSpeed = Speed;
  oled.clear();
  oled.textSize(2);
  oled.text(0,0,"  Starting   ");
  oled.text(1,0,"   Mode=%d   ",RobotMode);
  oled.show();
  StartTimer2();
  
  //ForwardSpeedTime(60,1500);    //เดินหน้าด้วยความเร็ว 70% นาน 1500 ms(1.5 วินาที)
  //BackwardSpeedTime(60,1500);   //ถอยหลังด้วยความเร็ว 70% นาน 1500 ms(1.5 วินาที)
  //TurnLeft();                   //เลี้ยวซ้ายหน่วงเวลา
  //TurnRight();                  //เลี้ยวขวาหน่วงเวลา
  //UTurnLeft();                  //กลับตัวด้านซ้ายหน่วงเวลา
  //UTurnRight();                 //กลับตัวด้านขวาหน่วงเวลา
  //Left(70,200);                         //เลี้ยวซ้ายแบบหน่วงเวลา
  //Right(70,200);                        //เลี้ยวขวาแบบหน่วงเวลา
  //TracSpeedTime(Speed,950);     //เคลื่อนที่ตามช่องหน่วงเวลา
  //TracJCStop();                 //เคลื่อนที่ตามช่องเจอเส้นหยุดทันที
  //TracJCBlack();                //เคลื่อนที่ตามช่องเจอเส้นหยุดจูนก่อนหยุด
  //TracJC0();                    //เคลื่อนที่ตามช่องเจอเส้นหยุดแล้วถอยก่อนหยุด
  //TracJC1();                    //เคลื่อนที่ตามช่องเจอเส้นจูนแล้วถอยก่อนหยุด
  //TracJC();                     //เคลื่อนที่ตามช่องเจอเส้นจูนแล้วถอยจูนก่อนหยุด
  //TracJC0ACCTime(ACCSpeed,500); //เคลื่อนที่ตามช่องเร่งความเร็ว ACCSpeed เวลา 500 ms แล้วชะลอ เจอเส้นหยุดแล้วถอยก่อนหยุด
  //TracJC1ACCTime(ACCSpeed,500); //เคลื่อนที่ตามช่องเร่งความเร็ว ACCSpeed เวลา 500 ms แล้วชะลอ เจอเส้นจูนแล้วถอยก่อนหยุด
  //TracJCACCTime(ACCSpeed,500); //เคลื่อนที่ตามช่องเร่งความเร็ว ACCSpeed เวลา 500 ms แล้วชะลอ เจอเส้นจูนแล้วถอยจูนก่อนหยุด
  //BackwardBalance();            //ถอยจูนด้านหลัง
  //TracJCStopBack();              //ถอยหลังเคลื่อนที่ตามช่องเจอเส้นหยุดทันที
  //TracJCBlackBack();               //ถอยหลังเข้าหลุมดำหรือพื้นที่วางสีเขียว
  //TracJC0Back();                //ถอยหลังถึงเส้นและเดินหน้าแบบไม่จูน
  //TracJC1Back();                //ถอยถึงเส้นจูนและถอยแบบไม่จูน
  //TracJC0ACCBackTime(ACCSpeed,500); //ถอยหลังตามช่องเร่งความเร็ว ACCSpeed เวลา 500 ms แล้วชะลอ ถอยหลังถึงเส้นและเดินหน้าแบบไม่จูน
  //TracJC1ACCBackTime(ACCSpeed,500); //ถอยหลังตามช่องเร่งความเร็ว ACCSpeed เวลา 500 ms แล้วชะลอ ถอยถึงเส้นจูนและถอยแบบไม่จูน
  //TracACC(ACCSpeed,300);        //Trac เร่งแบบหน่วงเวลา แต่เริ่มออกตัวช้าๆ
  //TracACCBack(ACCSpeed,300);    //Trac หลัง เร่งแบบหน่วงเวลา แต่เริ่มออกตัวช้าๆ
  //KickF();                      //เตะลูกบาศก์ด้านหน้า
  //KickB();                      //เตะลูกบาศก์ด้านหลัง
  //KickFBackward();              //ถอยหลังพร้อมเตะลูกบาศก์ด้านหน้า
  //KickBForward();               //เดินหน้าพร้อมเตะลูกบาศก์ด้านหลัง
  //KickFBackwardDegree(100,0,200);   //ถอยหลังตามองศาพร้อมเตะลูกบาศก์ด้านหน้า
  //KickBForwardDegree(100,0,200);   //เดินหน้าตามองศาพร้อมเตะลูกบาศก์ด้านหลัง
  //ShowYaw();
  //TurnLeftDegree(100,90,1); //เลี้ยวซ้ายใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการเหมือน 0
  //TurnRightDegree(100,90,2); //เลี้ยวขวาใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  //CurveLeftDegree(100,90,1); //โค้งซ้ายใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการเหมือน 0
  //CurveRightDegree(100,270,1); //โค้งขวาใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  //CurveLeftDegreeBack(100,90,1); //ถอยโค้งซ้ายใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการเหมือน 0
  //CurveRightDegreeBack(100,270,1); //ถอยโค้งขวาใช้เข็มทิศ 0-359
      //0:เคลียร์มุมเริ่มต้น 1:ไม่เคลียร์มุมเริ่มต้น 2:เคลียร์มุมเริ่มต้นแต่มุมเลี้ยวที่ต้องการ
  //FinishWaitOK();                 //หยุดและแสดงเวลา รอกดปุ่ม OK
  //TracDegreeSpeedTime(60,0,1000,0);       //เดินหน้า ความเร็ว 60 ทิศทาง 0 องศา เวลา 1000 ms 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ
  //TracDegreeSpeedTimeBack(60,0,1000,1);   //ถอยหลังความเร็ว 60 ทิศทาง 0 องศา เวลา 1000 ms 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ
  //SpinDegree(60,90,1);      //เลี้ยวความเร็ว 60 ทิศทาง 90 องศา 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ 
  //SpinDegreeBack(60,90,1);  //เลี้ยวหลังความเร็ว 60 ทิศทาง 90 องศา 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ 
  //TracJCDegree(60,0,100,0);       //เดินหน้า ความเร็ว 60 ทิศทาง 0 องศา เจอแยกถอยเวลา 100 ms 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ
  //TracJCDegreeBack(60,0,100,0); //ถอยหลังความเร็ว 60 ทิศทาง 0 องศา เจอแยกเดินเวลา 100 ms 0:ไม่หมุนกลับทิศ 1:หมุนกลับทิศ
  //TestGyro();
  //Finish();                       //จบการทำงานทุกอย่าง
}

void loop() {
  // put your main code here, to run repeatedly:
  Mode();
  FinishWaitOK();                 //หยุดและแสดงเวลา รอกดปุ่ม OK
  zeroYaw();                //เซตมุนเริ่มต้นใหม่
}
void ShowTurnStatus()
{
  if(TurnStatus==0) oled.text(6,0,"Turn=0:Time Turn ");
  else oled.text(6,1,"Turn=1:IMU Turn ");
}
void CheckKnobMode()  //เช็คดูว่ามีการปรับค่า knob เพื่อเปลี่ยนการเลี้ยว
{
  int Num,KnobDiv=500;
  
  Num = knob()-KnobBase;
  if(((Num>KnobDiv)||(Num<-KnobDiv))&&(knob()>1000)) //ปรับค่าความเร็วจาก knob
  {
    delay(50);
    Num = knob()-KnobBase;
    if(((Num>KnobDiv)||(Num<-KnobDiv))&&(knob()>1000)) //ปรับค่าความเร็วจาก knob
    {
      sound(3000,200);
      TurnStatus++;
      TurnStatus %=2;
      KnobBase=knob();
      ShowTurnStatus();
      oled.show();
    }
  }
}
