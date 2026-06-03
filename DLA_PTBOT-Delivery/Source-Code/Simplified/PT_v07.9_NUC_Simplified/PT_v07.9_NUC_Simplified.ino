#include <PTBOTAtomVX.h>
#include <ESP32Encoder.h>
#include <SoftI2C.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

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
int IRLED_Min[] = { 95, 100, 135, 180 };
int IRLED_Max[] = { 550, 620, 750, 800 };

float ToF_Distance = 35;
float Ultrasonic_Drop_Distance = 5;
float Ultrasonic_Pick_Distance = 4;

int Swing_Left = 58;    // S0 เพิ่ม ง้างออก
int Swing_Right = 58;   // S1 ลด หุบเข้า
int Open_Left = 110;    // S2 เพิ่ม หุบเข้า
int Open_Right = 90;    // S3 ลด หุบออก
int Close_Left = 147;   // S2 เพิ่ม หุบเข้า
int Close_Right = 127;  // S3 ลด หุบออก

void setup() {
  Serial.begin(115200);
  Wire.begin();
  i2cMutex = xSemaphoreCreateRecursiveMutex();
  initialize();
  xTaskCreatePinnedToCore(LiftLoop, "LiftLoop", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(UltrasonicLoop, "UltrasonicLoop", 2048, NULL, 1, &UltrasonicTaskHandle, 0);
  BalanceArm('O');
  Lift(Default_Lift);
  STOP();
  // Experiment();
  // Operation();
  SetBack(25, 275, 'R');
  PickCan(0, 60, 300);
  STOP();
}

void loop() {
}
