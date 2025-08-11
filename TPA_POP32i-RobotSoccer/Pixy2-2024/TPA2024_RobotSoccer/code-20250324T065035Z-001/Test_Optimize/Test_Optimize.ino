
/** 
 *  Updated on 31/03/23
 *  Modified by Teerachot
 *  Robo-Soccer, INEX
 */
 
#include <POP32.h>        // เรียก library หลักของบอร์ด POP-32
#include <POP32_Pixy2.h>  // เรียก library ของโมดูลกล้อง pixy 
POP32_Pixy2 pixy;         // สร้าง object สำหรับการใช้งานกล้อง pixy (keyword: การเขียนโปรแกรมเชิงวัตถุ, คลาสในภาษาซี และ c++ language)

int discoverState = 0;    // ใช้ระบุสถานะของหุ่นยนต์ เมื่อเจอบอล
// 0 = วิ่งไล่บอล
// 1 = จัดตำแหน่งเตรียมยิง
// 2 = วิ่งไล่บอล และยิง
int searchState = 0;      // ใช้ระบบสถานะ เมื่อไม่เจอบอล
/////////////////////////////////////////////////////<-----------------

// ฟังก์ชั่นสำหรับการจับเวลา ------------------------------------------------------------------------------------------------
unsigned long startTime, settingTime; 

void resetTimer() // เสมือนการล้างค่าเวลา
{
  startTime = millis(); 
}

void setTime(long t) // กำหนดช่วงการจับเวลา
{
  settingTime = constrain(t, 0, 10000); // 10 sec limiter 
}

bool InTime() // ฟังก์ชั่นจะคืนค่าเป็น "1" เมื่อครบเวลาที่กำหนด "0" เมื่อยังไม่ครบเวลาที่กำหนด
{
  if (millis()-startTime >= settingTime)  
  {
    resetTimer();
    return true;
  }
  return false;
}

// ฟังก์ชั่นสำหรับชุดยิง ----------------------------------------------------------------------------------------------------
#define limPin A0     // กำหนดพินของสวิตซ์เป็น A0 (ลิมิตสวิตซ์บนชุดยิง)
#define reloadSpd 60  // กำหนดความเร็วดึงกลับ ของมอเตอร์ชุดยิง

void shoot() // คำสั่งยิง
{
  motor(4, reloadSpd);  delay(150);
  motor(4, 0);          delay(50);
}

void reload() // คำสั่งรีโหลดกลไก มักใช้งานหลังการยิง
{
  motor(4, reloadSpd);
  
  setTime(800);  // กำหนดเวลารีโหลด 0.8 วินาที
  resetTimer();  // ** ก่อนใช้งานอย่าลืมรีเซตตัวจับเวลา

  while(!InTime()) // การรีโหลดจะสิ้นสุดเมื่อครบเวลาที่กำหนด หรือ เมื่อสวิตซ์ถูกกด
  {
    if (in(limPin)) break;
  }
  motor(4, 0);
}
// note: ฟังก์ชั่น shoot และ reload สามารถปรับแต่งได้ตามความเหมาะสม

// ส่วนของการวิ่งพื้นฐาน --------------------------------------------------------------------------------------------------
#define degToRad 0.0174             // ตัวคูณแปลงหน่วยองศาเป็นเรเดียน (มาจาก PI หาร 180)
#define sin30 sin(30.f * degToRad)  // กำหนดค่าคงที่ sin 30 องศา
#define cos30 cos(30.f * degToRad)  // กำหนดค่าคงที่ cos 30 องศา
float thetaRad, vx, vy, spd1, spd2, spd3;

// สั่งงานสามล้อ
void threeWheel(int mot1, int mot2, int mot3) 
{
  motor(1, mot1);
  motor(2, mot2);
  motor(3, mot3);
}

// สั่งงานการเคลื่อนที่แบบหลายทิศทาง 
// spd คือ ความเร็วที่ต้องการ
// theta คือ ทิศทางที่ต้องการ เทียบกับหุ่นยนต์
// omega คือ ความเร็วเชิงมุมรอบหุ่นยนต์ ใช้เมื่อต้องการเคลื่อนที่แบบโค้ง 
void holonomic(float spd, float theta, float omega) 
{
  thetaRad = theta * degToRad;
  vx = spd * cos(thetaRad);
  vy = spd * sin(thetaRad);
  spd1 =   vy * cos30 - vx * sin30 + omega;
  spd2 = - vy * cos30 - vx * sin30 + omega;
  spd3 =   vx + omega;
  threeWheel(spd1, spd2, spd3);
}

// ส่วนของการวิ่งไล่บอล --------------------------------------------------------------------------------------------------
// ตัวแปรเกี่ยวกับตัวควบคุมทิศทาง
#define rot_Kp 0.8
#define rot_Ki 0.0
#define rot_Kd 0.2
#define rotErrorGap 15  // ในทางปฎิบัติความผิดพลาดเป็นศูนย์เกิดขึ้นได้ยาก เราจึงกำหนดค่าความผิดพลาดที่สามารถยอมรับได้ไว้เสมอ
float rot_error, rot_pError, rot_i, rot_d, rot_omega;
float spRot = 150;      // ระยะกำหนดในแกนนอนของบอล บนเฟรมภาพจากกล้อง pixy ควรจะเป็นพิกัดที่บอลอยู่กึ่งกลางเฟรม
int ballPosX;           // ระยะของบอลที่กล้องมองเห็น ในแกนนอน    
      
// ตัวแปรเกี่ยวกับตัวควบคุมระยะทาง (ระหว่างหุ่นยนต์กับบอล)
#define fli_Kp 1.65
#define fli_Ki 0.0
#define fli_Kd 0.0
#define fliErrorGap 20  // มีหน้าที่เช่นเดียวกับ rotErrorGap 
float fli_error, fli_pError, fli_i, fli_d, fli_spd;
float spFli = 175;      // ระยะกำหนดในแกนตั้งของบอล บนเฟรมภาพจากกล้อง pixy ควรจะเป็นพิกัดที่บอลอยู่ใกล้กับชุดยิง
int ballPosY;           // ระยะของบอลที่กล้องมองเห็น ในแกนตั้ง  

// ฟังก์ชั่นควบคุมการวิ่งไล่บอล
void hunt(int spX, int spY, int posX, int posY)
{
  // ตัวควบคุม PID ของทิศทาง
  rot_error = spX - posX;             // ค่าความผิดพลาด คือ ช่องว่างระหว่างค่ากำหนด (setpoint) กับค่าที่เกิดขึ้นจริง (actual)
  rot_i = rot_i + rot_error;            // i หรือ integral คือ ค่าความผิดพลาดสะสม เพิ่มขึ้นจากการเกิดความผิดพลาดเป็นเวลานาน
  rot_d = constrain(rot_d, -100, 100);  // ** ค่า i สามารถเพิ่มขึ้นไปได้ไม่รู้จบ ควรลิมิตค่าสูงสุดไว้เสมอ
  rot_d = rot_error - rot_pError;       // d หรือ derivatives คือ ค่าความผิดพลาดจากอัตราการเปลี่ยนแปลง เพิ่มขึ้นจากการเปลี่ยนแปลงค่าความผิดพลาดย่างฉับพลัน
  rot_pError = rot_error;               // สืบเนื่องมาจาก d การที่จะหาการเปลี่ยนแปลงได้นั้น ต้องมีการเปรียบเทียมระหว่างค่าเก่า และค่าใหม่
                                        // ดังนั้นต้องเก็บค่าความผิดพลาดล่าสุดไว้ เพื่อใช้ในการคำนวณครั้งถัดไป
  rot_omega = (rot_error * rot_Kp) + (rot_i * rot_Ki) + (rot_d * rot_Kd); // การคำนวณหาค่าชดเชย จากค่าความผิดพลาดที่เกิดขึ้นจาก p, i และ d
  rot_omega = constrain(rot_omega, -30, 30);                              // กำหนดค่าชดเชยสูงสุดไว้ให้ไม่เกินค่าของความเร็วมอเตอร์
  
  // ตัวควบคุม PID ของระยะทาง
  ballPosY = pixy.sigInfo[1][0].y;
  fli_error = spY - posY;
  fli_i = fli_i + fli_error;
  fli_i  = constrain(fli_i , -100, 100);
  fli_d = fli_error - fli_pError;
  fli_pError = fli_error;
  fli_spd = fli_error * fli_Kp + fli_i * fli_Ki + fli_d * fli_Kd;
  fli_spd = constrain(fli_spd , -100, 100);
  
  holonomic(fli_spd, 90, rot_omega);    // สั่งเคลื่อนที่จากค่าที่ชดเชยไว้ สังเกตตัวแปรชื่อ fli_spd และ rot_omega
} 

// ส่วนของการหันยิง -----------------------------------------------------------------------------------------------------
#define ali_Kp 1.2
#define ali_Ki 0.0
#define ali_Kd 0.0
#define aliErrorGap 3.0 
float ali_error, ali_pError, ali_i, ali_d, ali_vec;
float spAli = 160;  // ไม่ต้องใช้พิกัดใกล้ชุดยิงมากก็ได้  

// ฟังก์ชั่นควบคุมทิศทางยิง
void align(int prevDir, int posY)
{
  ali_error = spAli - posY; // ค่าความผิดพลาดเป็นลบเมื่อเข้าใกล้บอล
  ali_i = ali_i + ali_error;
  ali_i  = constrain(ali_i , -90, 90);
  ali_d = ali_error - ali_pError;
  ali_pError = ali_error;
  ali_vec = ali_error * ali_Kp + ali_i * ali_Ki + ali_d * ali_Kd;
  ali_vec = constrain(ali_vec , -90, 90);

  // เลือกทิศหมุนที่ใกล้ที่สุด จากมุมของหุ่นยนต์ล่าสุด
  if ((prevDir >= 0 && prevDir < 180) || (prevDir < -180 && prevDir < -360))  
  // เป็นบวกเมื่อหุ่นยนต์เฉียงไปทางซ้าย หรือบางครั้งข้อมูลจะกระโดดข้ามช่วงไปฝั่งลบ แต่ไม่ใช่ช่วง 0 ถึง -180
  {
    holonomic(60, 180 - ali_vec, -30);
    // theta = 180 หุ่นยนต์สไลด์ไปทางซ้าย
    // omega เป็นลบหมุนตามเข็มนาฬิกา ยิ่งน้อยยิ่งตีวงแคบ
  }
  else
  // เป็นลบเมื่อหุ่นยนต์เฉียงไปทางขวา
  {
    holonomic(60, 0 - ali_vec, 30); 
    // theta = 0 หุ่นยนต์สไลด์ไปทางขวา
    // omega เป็นบวกหมุนทวนเข็มนาฬิกา ยิ่งมากยิ่งตีวงแคบ
  }
}

// ส่วนของการรับค่าไจโร -------------------------------------------------------------------------------------------------
volatile float pvYaw, lastYaw;
volatile uint8_t rxCnt = 0, rxBuf[8];

// ฟังก์ชั่นเริ่มการทำงานของ imu เรียกครั้งแรกใน void setup และเรียกครั้งต่อไปเพื่อเซตศูนย์มุม yaw
void zeroYaw() 
{
  Serial1.begin(115200);  // กำหนดความเร็วในการรับ-ส่งข้อมูลเป็น 115200 บิตต่อวินาที
  delay(100);
  Serial1.write(0XA5);    // รีเซตค่ามุมอื่นๆ เป็นศูนย์
  Serial1.write(0X54); 
  delay(100);
  Serial1.write(0XA5);  // รีเซตค่ามุม yaw เป็นศูนย์
  Serial1.write(0X55); 
  delay(100);             // รีเซต yaw เป็นศูนย์
  Serial1.write(0XA5);    // กำหนดเป็นโหมดรับ-ส่งอัตโนมัติ
  Serial1.write(0X52); 
  delay(100);
}

// ฟังก์ชั่นอ่านค่ามุมจากไจโร
bool updateIMU() 
{
  while (Serial1.available()) // เมื่อมีแพ็จเกจเข้ามา
  {
    rxBuf[rxCnt] = Serial1.read();              // อ่านแพ็คเกจ
    if (rxCnt == 0 && rxBuf[0] != 0xAA) return; // ถ้าหัวแพ็จเกจไม่ถูกต้อง
    rxCnt++;
    if (rxCnt == 8)                             // ถ้าได้รับข้อมูลจากแพ็กเกจครบจำนวน
    {
      rxCnt = 0;
      if (rxBuf[0] == 0xAA && rxBuf[7] == 0x55) // ถ้าได้รับข้อมูลจากแพ็กเกจถูกต้อง
      { 
        pvYaw = (int16_t)(rxBuf[1] << 8 | rxBuf[2]) / 100.f;  // คำนวนมุมจากข้อมูลที่ได้รับ
        return true;
      }
    }
  }
  return false;
}

// ฟังก์ชั่น setup ใส่อะไรในนี้จะทำแค่ครั้งเดียว
void setup() 
{
  zeroYaw();    // เริ่มการทำงานของ imu 
  sound(3500, 100); 
  
  pixy.init();  // เริ่มการทำงานของ pixy ** อย่าลืมเปลี่ยน interface ใน pixyMon เป็น i2c มิเช่นนั้นโค้ดจะค้างที่ฟังก์ชั่นนี้
  sound(3000, 100);
  
  reload();     // เตรียมพร้อมชุดยิงให้พร้อมใช้งาน
  sound(2500, 100);
  
  oled.mode(2); // หมุนหน้าจอเป็นโหมด 2
  oled.text(6, 0, "Press SW_B: zeroYaw"); // กดปุ่ม b เพื่อรีเซตมุม yaw
  oled.text(7, 0, "Press SW_A: Run !!!"); // กดปุ่ม a เพื่อเริ่มทำงาน
  oled.show();
  
  while (!SW_A())
  {
    if (SW_B()) zeroYaw();
    
    updateIMU(); // อ่านค่าจากไจโร และแสดงผลด้วยจอ
    oled.text(0, 0, "Yaw = %f        ", pvYaw); // pvYaw คือ ค่ามุม yaw ที่อ่านได้ปัจจุบัน
    oled.show();
  }
  sound(2000, 100);
}

// ฟังก์ชั่น loop ใส่อะไรในนี้จะทำวนไปไม่รู้จบ
void loop() 
{
  if (pixy.updateBlocks() && pixy.sigSize[1]) // sigSize คือ จำนวนของ signature ที่ 1 ถ้าเจอต้องมีค่ามากกว่า 0
  {
    int ballPosX = pixy.sigInfo[1][0].x;  // อ่านพิกัด x ของ signature 1 ชิ้นที่ 0 (จำนวนจะเริ่มต้นชิ้นที่ 0 ไปถึงชิ้นที่ n)   
    int ballPosY = pixy.sigInfo[1][0].y;  // อ่านพิกัด y    

    for (int i=0; i<16; i++)    // วนอ่านหลายรอบเพื่อเพิ่มความแม่นยำในการรับข้อมูล
    {
      updateIMU();              // อย่าลืมว่าใช้ pvYaw เมื่อไหร่ ต้องอัพเดทค่าก่อนทุกครั้ง
    }
    
    switch (discoverState)
    {
      case 0:
        hunt(spRot, spFli, ballPosX, ballPosY); // ฟังก์ชั่นวิ่งไล่บอล -> ป้อน: พิกัดกำหนด(x), พิกัดกำหนด(y), พิกัด(x)ปัจจุบันของบอล, พิกัด(y)ปัจจุบันของบอล

        // 1. ถ้าทิศทางและระยะทางเข้าใกล้จุดที่กำหนด (อ้างอิงจากกล้อง pixy) ให้หุ่นยนต์เปลี่ยนไปทำ case 1 (จัดตำแหน่งยิง)
        if (abs(rot_error) < rotErrorGap && abs(fli_error) < fliErrorGap) 
        {
          threeWheel(0, 0, 0);
          sound(1500, 100);
          discoverState = 1;

          lastYaw = pvYaw;  // เก็บมุม yaw ล่าสุดไว้ใช้กับ case 2 เพื่อเลือกทิศทางการหมุน
        }
        break;
        
      case 1:   
        align(lastYaw, ballPosY); // ฟังก์ชั่นจัดตำแหน่งยิง -> ป้อน: ทิศทางล่าสุดของหุ่นยนต์, พิกัด(y)ปัจจุบันของบอล
        
        // 2. ถ้าทิศทางตรงกับจุดที่กำหนด (อ้างอิงจากไจโร) ให้หุ่นยนต์เปลี่ยนไปทำ case 2 (พุ่งและยิง)
        // **จุดสังเกต เปลี่ยนกรณีเป็น "ถ้าทิศทางประตูอยู่ตรงกลางเฟรม (อ้างอิงจากกล้อง pixy)" จะทำให้การยิงแม่นยำมากขึ้น
        if (abs(pvYaw) < aliErrorGap) 
        {
          threeWheel(0, 0, 0);
          sound(1000, 100);
          discoverState = 2;

          setTime(1000);  // กำหนดเวลาทำงานใน case 2 ให้ไม่นานจนเกินไป 
          resetTimer();   // ให้รีเซตเวลาก่อนใช้งานทุกครั้ง
        }
        break;

      case 2:
        hunt(spRot, spFli + 20, ballPosX, ballPosY); 
        // spFli + 20 เพราะอยากให้เข้าใกล้บอลกว่าเดิม
        
        // 3.1 ถ้าวิ่งพุ่งจนครบเวลา 1 วินาทีให้เลิกทำ
        if (InTime()) 
        {
          discoverState = 0;  // รีเซตสถานะกลับไปวิ่งไล่บอล
        }
        
        // 3.2 ถ้าระยะทางเข้าใกล้จุดที่กำหนด ให้หุ่นยนต์ยิงบอล
        if (abs(fli_error) < fliErrorGap) 
        {
          threeWheel(0, 0, 0);
          sound(500, 100);
          discoverState = 0;  // รีเซตสถานะกลับไปวิ่งไล่บอล
           
          shoot();            // ยิงและรีโหลดกลไก
          reload();
        }
        break;
    }
    searchState = 0;  // รีเซตสถานะกลับไปหมุนหาบอล เมื่อมองไม่เห็นบอล
  }
  else
  {
    switch (searchState)
    {
      case 0:
        setTime(2000);  // เริ่มจับเวลาเพื่อใช้ในเคสถัดไป
        resetTimer();  
        searchState++;  // เลื่อนสถานะหาบอล
        break;
        
      case 1:
        // หมุนหาบอลด้วยทิศทางที่เห็นบอลล่าสุด 
        // (keyword: การใช้ if แบบย่อในภาษาซี)
        rot_error > 0? holonomic(0, 0, 30): holonomic(0, 0, -30);

        // 4. ถ้าครบเวลา 2 วินาทีให้ไปทำอย่างอื่น
        if(InTime())  
        {
          threeWheel(0, 0, 0);
          sound(250, 100);

          setTime(1000);  // เริ่มจับเวลาเพื่อใช้ในเคสถัดไป
          resetTimer();  
          searchState++;  // เลื่อนสถานะหาบอล
        }
        break;
        
      case 2:
        // สไสด์ขวาหาบอล 
        holonomic(30, 0, 0);
        
        // 5. ถ้าครบเวลา 1 วินาทีให้ไปทำอย่างอื่น
        if(InTime())  
        {
          threeWheel(0, 0, 0);
          sound(125, 100);

          setTime(1000);  // เริ่มจับเวลาเพื่อใช้ในเคสถัดไป
          resetTimer();  
          searchState++;  // เลื่อนสถานะหาบอล
        }
        break;

      case 3: 
        // สไสด์ซ้ายหาบอล 
        holonomic(30, 180, 0);
        
        // 6. ถ้าครบเวลา 1 วินาทีให้ไปทำอย่างอื่น
        if(InTime())  
        {
          threeWheel(0, 0, 0);
          sound(60, 100);
          searchState = 0;  // กลับไปหมุนหาบอล
        }
        break;
    }
    discoverState = 0;  // รีเซตสถานะกลับไปวิ่งไล่บอล เมื่อมองเห็นบอลอีกครั้ง
  }
}
