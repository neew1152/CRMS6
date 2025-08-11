float last_distance = 0;

void calibrateMinMax() {
  unsigned long timer = millis();
  for (byte i = 0; i < 8; i++) {
    sensor_min[i] = 1023;
    sensor_max[i] = 0;
  }
  motorWrite(1000, 1000, 1000, 1000);
  while (1) {
    for (byte i = 0; i < 8; i++) {
      int sensor_value = adcRead(i);
      if (sensor_value < sensor_min[i]) sensor_min[i] = sensor_value;
      if (sensor_value > sensor_max[i]) sensor_max[i] = sensor_value;
    }
    if (millis() - timer > 2000) {
      motorStop();
      Serial.print("MIN: ");
      for (byte i = 0; i < 8; i++) {
        Serial.print(sensor_min[i]);
        if (i < 7) Serial.print(", ");
        else Serial.println();
      }
      Serial.print("MAX: ");
      for (byte i = 0; i < 8; i++) {
        Serial.print(sensor_max[i]);
        if (i < 7) Serial.print(", ");
        else Serial.println();
      }
      break;
    }
  }
}

void readLine() {
  for (byte i = 0; i < 8; i++) {
    line_value[i] = map(adcRead(i), sensor_min[i], sensor_max[i], 0, 100);
    if (line_value[i] < 0) line_value[i] = 0;
    else if (line_value[i] > 100) line_value[i] = 100;
  }
}

void ShowValue_Sensor() {
  lcdClear();
  while (1) {
    // readLine();
    int num_sensor = 8;
    int sensor_values[num_sensor];          // สร้างตัวแปรแบบ Array เพื่อเก็บค่า Sensor
    for (int i = 0; i < num_sensor; i++) {  // วนลูปอ่านค่า Sensor ทั้งหมด 6 ตัว
      // sensor_values[i] = line_value[i];     // นำค่า Sensor แต่ละตัวเก็บไว้ในตัวแปร
      sensor_values[i] = adcRead(i);  // นำค่า Sensor แต่ละตัวเก็บไว้ในตัวแปร
    }
    lcdDrawChart(sensor_values, num_sensor);  // แสดงกราฟค่าของ Sensor ทั้งหมด 8 ตัว การใช้งาน: lcdDrawChart(ค่าเซ็นเซอร์ [ตัวแปรแบบ Array], จำนวน Sensor)
  }
}

void sonarLoop(void *pvParameters) {
  const int TRIG_PIN = 27;
  const int ECHO_PIN = 14;
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  while (1) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(50);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2;
    last_distance = distance;
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

float readSonar() {
  return last_distance;
}

bool initVL53L0X() {
  writeRegister(0x88, 0x00);
  writeRegister(0x80, 0x01);
  writeRegister(0xFF, 0x01);
  writeRegister(0x00, 0x00);
  writeRegister(0x91, 0x3C);
  writeRegister(0x00, 0x01);
  writeRegister(0xFF, 0x00);
  writeRegister(0x80, 0x00);
  return true;
}

void setMeasurementTimingBudget(uint32_t budget_us) {
  uint32_t budget = budget_us * 1.065;
  writeRegister16Bit(0x04, (budget >> 16) & 0xFFFF);
  writeRegister16Bit(0x06, budget & 0xFFFF);
}

void setVcselPulsePeriod(uint8_t type, uint8_t period) {
  uint8_t reg = (type == 0) ? 0x50 : 0x70;
  writeRegister(reg, period);
}

int readCanDistance() {
  writeRegister(0x00, 0x01);
  Wire1.beginTransmission(0x29);
  Wire1.write(0x1E);
  Wire1.endTransmission(false);
  Wire1.requestFrom(0x29, 2);
  if (Wire1.available() < 2) return -1;
  int highByte = Wire1.read();
  int lowByte = Wire1.read();
  int can_distance = ((highByte << 8) | lowByte) - 50;
  if (can_distance == -30) can_distance = 8140;
  else if (can_distance < 0) can_distance = 0;
  return can_distance;
}

void writeRegister(uint8_t reg, uint8_t value) {
  Wire1.beginTransmission(0x29);
  Wire1.write(reg);
  Wire1.write(value);
  Wire1.endTransmission();
}

void writeRegister16Bit(uint8_t reg, uint16_t value) {
  Wire1.beginTransmission(0x29);
  Wire1.write(reg);
  Wire1.write((value >> 8) & 0xFF);
  Wire1.write(value & 0xFF);
  Wire1.endTransmission();
}

void setupDistanceSensor() {
  Wire1.begin(25, 26);
  Wire1.setClock(400000);
  initVL53L0X();
  setMeasurementTimingBudget(50000);
  setVcselPulsePeriod(0, 14);
  setVcselPulsePeriod(1, 10);
}

void ShowDistanceSensor() {
  vTaskResume(sonarTaskHandle);
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

void STOP() {
  motorStop();
  while (!switchRead(A) && !switchRead(B));
  delay(500);
}
