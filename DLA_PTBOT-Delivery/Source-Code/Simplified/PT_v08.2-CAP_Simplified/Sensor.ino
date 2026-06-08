void DisplaySensor() {
  lcdClear();
  Ultrasonic_State = 1;

  const int NUM_ADC_SENSORS = 4;
  const int NUM_AUX_SENSORS = 3;
  const int TOTAL_SENSORS = NUM_ADC_SENSORS + NUM_AUX_SENSORS;

  while (1) {
    int sensor_readings[TOTAL_SENSORS];
    int buf_idx = 0;

    for (int i = 0; i < NUM_ADC_SENSORS; i++) {
      sensor_readings[buf_idx++] = adcRead(i);
    }

    sensor_readings[buf_idx++] = ReadUltrasonic();
    sensor_readings[buf_idx++] = ReadToF();
    sensor_readings[buf_idx++] = Encoder.getCount() / 2;

    lcdDrawChart(sensor_readings, TOTAL_SENSORS);
    vTaskDelay(Delay_HW * 5 / portTICK_PERIOD_MS);
  }
}

void ReadIRLED() {
  for (byte i = 0; i < 4; i++) {
    IRLED_Data[i] = map(adcRead(i), IRLED_Min[i], IRLED_Max[i], 0, 100);
    if (IRLED_Data[i] < 0) IRLED_Data[i] = 0;
    else if (IRLED_Data[i] > 100) IRLED_Data[i] = 100;
  }
}

float ReadToF() {
  float ToF_Distance = -1;
  writeRegister(0x00, 0x01);
  vTaskDelay(Delay_HW / portTICK_PERIOD_MS);
  if (xSemaphoreTakeRecursive(i2cMutex, portMAX_DELAY) == pdTRUE) {
    Wire.beginTransmission(0x29);
    Wire.write(0x1E);
    Wire.endTransmission(false);
    Wire.requestFrom((uint16_t)0x29, (uint8_t)2);
    if (Wire.available() >= 2) {
      int highByte = Wire.read();
      int lowByte = Wire.read();
      ToF_Distance = ((highByte << 8) | lowByte) - 50;
      if (ToF_Distance == -30.0f) ToF_Distance = 8140.0f;
      else if (ToF_Distance < 0.0f) ToF_Distance = 0.0f;
    }
    xSemaphoreGiveRecursive(i2cMutex);
  }
  return ToF_Distance;
}

float ReadUltrasonic() {
  if (Last_Distance == 0.0) return 999.0;
  return Last_Distance;
}

void UltrasonicLoop(void* pvParameters) {
  int TRIG_PIN = 13;
  int ECHO_PIN = 4;
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  while (1) {
    vTaskDelay(Delay_HW / portTICK_PERIOD_MS);
    if (Ultrasonic_State == 1) {
      digitalWrite(TRIG_PIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
      long duration = pulseIn(ECHO_PIN, HIGH, 5000);
      float distance = duration * 0.0343 / 2;
      Last_Distance = distance;
    }
    vTaskDelay(Delay_HW * 5 / portTICK_PERIOD_MS);
  }
}

void write8(SoftI2C& wire, uint8_t reg, uint8_t data) {
  wire.write(data);
  wire.endTransmission();
}

void writeRegister(uint8_t reg, uint8_t data) {
  if (xSemaphoreTakeRecursive(i2cMutex, portMAX_DELAY) == pdTRUE) {
    Wire.beginTransmission(0x29);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
    xSemaphoreGiveRecursive(i2cMutex);
  }
}

void writeRegister16Bit(uint8_t reg, uint16_t data) {
  if (xSemaphoreTakeRecursive(i2cMutex, portMAX_DELAY) == pdTRUE) {
    Wire.beginTransmission(0x29);
    Wire.write(reg);
    Wire.write((data >> 8) & 0xFF);
    Wire.write(data & 0xFF);
    Wire.endTransmission();
    xSemaphoreGiveRecursive(i2cMutex);
  }
}

void STOP() {
  motorStop();
  while (!switchRead(A) && !switchRead(B)) {
    vTaskDelay(Delay_HW * 5 / portTICK_PERIOD_MS);
  };
  vTaskDelay(Delay_HIGH / portTICK_PERIOD_MS);
}
