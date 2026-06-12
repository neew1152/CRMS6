#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>
#include <SoftI2C.h>

#define Channel_Swing_Left 0
#define Channel_Swing_Right 1
#define Channel_Gripper_Left 2
#define Channel_Gripper_Right 3

ESP32Encoder Encoder;

volatile bool Ultrasonic_State = 0;
volatile float Last_Distance = 0.0;
volatile int Lift_Target = 0;
int IRLED_Data[] = { 0, 0, 0, 0 };
int Swing_Current_Degree[] = { 0, 0 };
float Current_Degree = 0;
float Power_Factor = 1;
float Previous_Error_Forward = 0;
TaskHandle_t UltrasonicTaskHandle = NULL;

int Default_Delay = 250;
int Delay_HIGH = Default_Delay * 2;
int Delay_HW = Default_Delay / 25;
int Delay_LOW = Default_Delay / 2;
int Default_Lift = 3;

int Speed_LOW = 10;
int Speed_MID = 25;
int Time_Withdraw = Speed_MID * 20;

//                  S0   S1   S2   S3
int IRLED_Min[] = { 110, 100, 110, 130 };
int IRLED_Max[] = { 490, 530, 720, 600 };


float ToF_Distance = 35;
float Ultrasonic_Drop_Distance = 5;
float Ultrasonic_Pick_Distance = 4.5;

int Swing_Left = 57;                // S0 เพิ่ม ง้างออก
int Swing_Right = 54;               // S1 ลด หุบเข้า
int Open_Left = 100;                // S2 เพิ่ม หุบเข้า
int Open_Right = 97;                // S3 ลด หุบออก
int Close_Left = Open_Left + 37;    // S2 เพิ่ม หุบเข้า
int Close_Right = Open_Right + 37;  // S3 ลด หุบออก

void setup() {
  Serial.begin(115200);
  Wire.begin();
  initialize();
  xTaskCreatePinnedToCore(LiftLoop, "LiftLoop", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(UltrasonicLoop, "UltrasonicLoop", 2048, NULL, 1, &UltrasonicTaskHandle, 0);
  BalanceArm('O');
  Lift(Default_Lift);
  STOP();
  BalanceArm('W');
  STOP();
  // Experiment();
  Operation();
  // DisplaySensor();
  STOP();
}

void loop() {
}
