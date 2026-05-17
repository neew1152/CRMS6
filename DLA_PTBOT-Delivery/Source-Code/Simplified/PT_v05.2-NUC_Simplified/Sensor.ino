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
    int num_sensor = 4;
    int sensor_values[num_sensor];
    for (int i = 0; i < num_sensor; i++) {
      sensor_values[i] = adcRead(i);
    }
    lcdDrawChart(sensor_values, num_sensor);
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
      long duration = pulseIn(ECHO_PIN, HIGH, 30000);
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
  vTaskDelay(10 / portTICK_PERIOD_MS);;
  while (1) {
    Serial.print("Sonar: ");
    Serial.print(readSonar());
    Serial.print(" IR: ");
    Serial.print(readCanDistance());
    Serial.println();
    vTaskDelay(10 / portTICK_PERIOD_MS);;
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

void STOP() {
  motorStop();
  while (!switchRead(A) && !switchRead(B))
    ;
  vTaskDelay(500 / portTICK_PERIOD_MS);
}
