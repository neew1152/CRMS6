void DisplaySensor() {
  lcdClear();
  Ultrasonic_Enable = 1;

  int num_ir_sensors = 4;
  int total_sensors = num_ir_sensors + 2;

  while (1) {
    int sensor_readings[total_sensors];

    for (int i = 0; i < num_ir_sensors; i++) {
      sensor_readings[i] = adcRead(i);
    }

    sensor_readings[num_ir_sensors] = ReadUltrasonic();
    sensor_readings[num_ir_sensors + 1] = ReadLaser();

    lcdDrawChart(sensor_readings, total_sensors);
  }
}

void ReadIR() {
  for (byte i = 0; i < 4; i++) {
    IR_Data[i] = map(adcRead(i), IR_Min[i], IR_Max[i], 0, 100);
    if (IR_Data[i] < 0) IR_Data[i] = 0;
    else if (IR_Data[i] > 100) IR_Data[i] = 100;
  }
}

float ReadLaser() {
  float Laser_Distance = -1.0;
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
      Laser_Distance = ((highByte << 8) | lowByte) - 50;
      if (Laser_Distance == -30.0f) Laser_Distance = 8140.0f;
      else if (Laser_Distance < 0.0f) Laser_Distance = 0.0f;
    }
    xSemaphoreGiveRecursive(i2cMutex);
  }
  return Laser_Distance;
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
    vTaskDelay(10 / portTICK_PERIOD_MS);
    if (Ultrasonic_Enable == 1) {
      digitalWrite(TRIG_PIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
      long duration = pulseIn(ECHO_PIN, HIGH, 5000);
      float distance = duration * 0.0343 / 2;
      Last_Distance = distance;
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
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
    vTaskDelay(10 / portTICK_PERIOD_MS);
  };
  vTaskDelay(500 / portTICK_PERIOD_MS);
}
