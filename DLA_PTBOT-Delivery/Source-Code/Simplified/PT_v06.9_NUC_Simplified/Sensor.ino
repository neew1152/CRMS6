void readLine() {
  for (byte i = 0; i < 4; i++) {
    line_value[i] = map(adcRead(i), sensor_min[i], sensor_max[i], 0, 100);
    if (line_value[i] < 0) line_value[i] = 0;
    else if (line_value[i] > 100) line_value[i] = 100;
  }
}

void ShowValue_Sensor() {
  lcdClear();
  int num_sensor = 4;
  while (1) {
    vTaskDelay(10 / portTICK_PERIOD_MS);
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
    vTaskDelay(10 / portTICK_PERIOD_MS);
    if (sonar_enable == 1) {
      digitalWrite(TRIG_PIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
      long duration = pulseIn(ECHO_PIN, HIGH, 5000);
      float distance = duration * 0.0343 / 2;
      last_distance = distance;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

float readSonar() {
  if (last_distance == 0.0) return 999.0;
  return last_distance;
}

float readCanDistance() {
  float can_distance = -1.0;
  writeRegister(0x00, 0x01);
  vTaskDelay(10 / portTICK_PERIOD_MS);
  if (xSemaphoreTakeRecursive(i2cMutex, portMAX_DELAY) == pdTRUE) {
    Wire.beginTransmission(0x29);
    Wire.write(0x1E);
    Wire.endTransmission(false);
    Wire.requestFrom((uint16_t)0x29, (uint8_t)2);
    if (Wire.available() >= 2) {
      int highByte = Wire.read();
      int lowByte = Wire.read();
      can_distance = ((highByte << 8) | lowByte) - 50;
      if (can_distance == -30.0f) can_distance = 8140.0f;
      else if (can_distance < 0.0f) can_distance = 0.0f;
    }
    xSemaphoreGiveRecursive(i2cMutex);
  }
  return can_distance;
}

void writeRegister(uint8_t reg, uint8_t value) {
  if (xSemaphoreTakeRecursive(i2cMutex, portMAX_DELAY) == pdTRUE) {
    Wire.beginTransmission(0x29);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
    xSemaphoreGiveRecursive(i2cMutex);
  }
}

void writeRegister16Bit(uint8_t reg, uint16_t value) {
  if (xSemaphoreTakeRecursive(i2cMutex, portMAX_DELAY) == pdTRUE) {
    Wire.beginTransmission(0x29);
    Wire.write(reg);
    Wire.write((value >> 8) & 0xFF);
    Wire.write(value & 0xFF);
    Wire.endTransmission();
    xSemaphoreGiveRecursive(i2cMutex);
  }
}

void ShowDistanceSensor() {
  sonar_enable = 1;
  while (1) {
    Serial.print("Sonar: ");
    Serial.print(readSonar());
    Serial.print(" IR: ");
    Serial.print(readCanDistance());
    Serial.println();
  }
}

void write8(SoftI2C& wire, uint8_t reg, uint8_t value) {
  wire.write(value);
  wire.endTransmission();
}

void STOP() {
  motorStop();
  while (!switchRead(A) && !switchRead(B)) {
    vTaskDelay(10 / portTICK_PERIOD_MS);
  };
  vTaskDelay(500 / portTICK_PERIOD_MS);
}
