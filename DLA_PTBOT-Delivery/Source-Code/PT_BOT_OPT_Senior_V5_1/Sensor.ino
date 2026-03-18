#define TCS34725_ADDRESS 0x29
#define TCS34725_COMMAND_BIT 0x80

SoftI2C SoftWire1(25, 26);
SoftI2C SoftWire2(27, 14);

float last_distance = 0.0;

void readLine() {
  for (byte i = 0; i < 4; i++) {
    line_value[i] = map(adcRead(i), sensor_min[i], sensor_max[i], 0, 100);
    if (line_value[i] < 0) line_value[i] = 0;
    else if (line_value[i] > 100) line_value[i] = 100;
  }
}

void ShowValue_Sensor() {
  lcdClear();
  while (1) {
    // readLine();
    int num_sensor = 4;
    int sensor_values[num_sensor];          // สร้างตัวแปรแบบ Array เพื่อเก็บค่า Sensor
    for (int i = 0; i < num_sensor; i++) {  // วนลูปอ่านค่า Sensor ทั้งหมด 6 ตัว
      // sensor_values[i] = line_value[i];     // นำค่า Sensor แต่ละตัวเก็บไว้ในตัวแปร
      sensor_values[i] = adcRead(i);  // นำค่า Sensor แต่ละตัวเก็บไว้ในตัวแปร
    }
    lcdDrawChart(sensor_values, num_sensor);  // แสดงกราฟค่าของ Sensor ทั้งหมด 8 ตัว การใช้งาน: lcdDrawChart(ค่าเซ็นเซอร์ [ตัวแปรแบบ Array], จำนวน Sensor)
  }
}

void sonarLoop(void* pvParameters) {
  int TRIG_PIN = 13;
  int ECHO_PIN = 4;
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  while (1) {
    if (sonar_enable == 1) {
      digitalWrite(TRIG_PIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
      long duration = pulseIn(ECHO_PIN, HIGH);
      float distance = duration * 0.0343 / 2;
      last_distance = distance;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

float readSonar() {
  return last_distance;
}

float readCanDistance() {
  writeRegister(0x00, 0x01);
  Wire.beginTransmission(0x29);
  Wire.write(0x1E);
  Wire.endTransmission(false);
  Wire.requestFrom(0x29, 2);
  if (Wire.available() < 2) return -1.0;
  int highByte = Wire.read();
  int lowByte = Wire.read();
  float can_distance = ((highByte << 8) | lowByte) - 50;
  if (can_distance == -30.0f) can_distance = 8140.0f;
  else if (can_distance < 0.0f) can_distance = 0.0f;
  return can_distance;
}

void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(0x29);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void writeRegister16Bit(uint8_t reg, uint16_t value) {
  Wire.beginTransmission(0x29);
  Wire.write(reg);
  Wire.write((value >> 8) & 0xFF);
  Wire.write(value & 0xFF);
  Wire.endTransmission();
}

void ShowDistanceSensor() {
  vTaskResume(sonarTaskHandle);
  sonar_enable = 1;
  delay(10);
  while (1) {
    Serial.print("Sonar: ");
    Serial.print(readSonar());
    Serial.print(" IR: ");
    Serial.print(readCanDistance());
    Serial.println();
    delay(10);
  }
}

void write8(SoftI2C& wire, uint8_t reg, uint8_t value) {
  wire.beginTransmission(TCS34725_ADDRESS);
  wire.write(TCS34725_COMMAND_BIT | reg);
  wire.write(value);
  wire.endTransmission();
}

uint16_t read16(SoftI2C& wire, uint8_t reg) {
  wire.beginTransmission(TCS34725_ADDRESS);
  wire.write(TCS34725_COMMAND_BIT | reg);
  wire.endTransmission();

  wire.requestFrom(TCS34725_ADDRESS, 2);
  uint16_t t = wire.read();
  t |= wire.read() << 8;
  return t;
}

void initSensor(SoftI2C& wire) {
  write8(wire, 0x00, 0x01);
  delay(3);
  write8(wire, 0x00, 0x03);
  delay(3);
  write8(wire, 0x01, 0xD5);
}

void setupColorSensor() {
  SoftWire1.begin();
  SoftWire2.begin();
  initSensor(SoftWire1);
  initSensor(SoftWire2);
}

void readRGB(SoftI2C& wire, int crgb[4]) {
  crgb[0] = read16(wire, 0x14);
  crgb[1] = read16(wire, 0x16);
  crgb[2] = read16(wire, 0x18);
  crgb[3] = read16(wire, 0x1A);
}

void calibrateCanColor() {
  int clear_color_left_cal;
  int clear_color_right_cal;
  int crgb[4];
  lift(0);
  while (!Serial)
    ;

  Serial.println("นำกระป๋องสีเหลืองวางที่มือด้านซ้าย แล้วกดปุ่ม B");
  while (!switchRead(A) && !switchRead(B))
    ;
  beep(50);
  servoWrite(chanal_Gripper_Left, Close_Left);
  delay(500);
  readRGB(SoftWire1, crgb);
  clear_color_left_cal = crgb[0];
  servoWrite(chanal_Gripper_Left, Open_Left);

  Serial.println("นำกระป๋องสีเหลืองวางที่มือด้านขวา แล้วกดปุ่ม B");
  while (!switchRead(A) && !switchRead(B))
    ;
  beep(50);
  servoWrite(chanal_Gripper_Right, Close_Right);
  delay(500);
  readRGB(SoftWire2, crgb);
  clear_color_right_cal = crgb[0];
  servoWrite(chanal_Gripper_Right, Open_Right);

  Serial.printf("clear_color_left: %d\n", clear_color_left_cal);
  Serial.printf("clear_color_right: %d\n", clear_color_right_cal);
  beep(50);
  delay(50);
  beep(50);
  delay(50);
  lift(3);
}

char readColor(char gripper) {
  if (gripper == 'l') {
    int crgb[4];
    readRGB(SoftWire1, crgb);
    if (crgb[0] >= (clear_color_left - 500)) {
      tft.fillRect(0, 0, 80, 128, 0xffc0);
      return 'y';
    } else {
      if (crgb[1] > crgb[2]) {
        tft.fillRect(0, 0, 80, 128, 0xf800);
        return 'r';
      } else if (crgb[2] > crgb[1]) {
        tft.fillRect(0, 0, 80, 128, 0x1d40);
        return 'g';
      } else {
        tft.fillRect(0, 0, 80, 128, 0x0000);
        return 'u';
      }
    }
  } else if (gripper == 'r') {
    int crgb[4];
    readRGB(SoftWire2, crgb);
    if (crgb[0] >= (clear_color_right - 500)) {
      tft.fillRect(80, 0, 80, 128, 0xffc0);
      return 'y';
    } else {
      if (crgb[1] > crgb[2]) {
        tft.fillRect(80, 0, 80, 128, 0xf800);
        return 'r';
      } else if (crgb[2] > crgb[1]) {
        tft.fillRect(80, 0, 80, 128, 0x1d40);
        return 'g';
      } else {
        tft.fillRect(80, 0, 80, 128, 0x0000);
        return 'u';
      }
    }
  } else return 'u';
}

void STOP() {
  motorStop();
  while (!switchRead(A) && !switchRead(B))
    ;
  delay(500);
}

void ShowValue_Distance() {
  lcdClear();
  while (1) {
    int distance_array[1];                  // สร้างตัวแปรแบบ Array ขนาด 1 ช่อง
    distance_array[0] = readCanDistance();  // อ่านค่าระยะทางมาเก็บไว้ใน Array ตำแหน่งที่ 0

    lcdDrawChart(distance_array, 1);  // ส่ง Array และจำนวนเซ็นเซอร์ (1) ไปแสดงผล

    delay(10);  // หน่วงเวลาเล็กน้อยป้องกันจอกระพริบและบอร์ดค้าง (Watchdog reset)
  }
}

void ShowValue_encoder() {
  lcdClear();
  while (1) {
    int distance_array[1];                  // สร้างตัวแปรแบบ Array ขนาด 1 ช่อง
    distance_array[0] = encoder.getCount();  // อ่านค่าระยะทางมาเก็บไว้ใน Array ตำแหน่งที่ 0

    lcdDrawChart(distance_array, 1);  // ส่ง Array และจำนวนเซ็นเซอร์ (1) ไปแสดงผล

    delay(10);  // หน่วงเวลาเล็กน้อยป้องกันจอกระพริบและบอร์ดค้าง (Watchdog reset)
  }
}