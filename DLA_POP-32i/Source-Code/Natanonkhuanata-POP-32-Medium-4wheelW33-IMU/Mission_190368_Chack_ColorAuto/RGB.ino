/////////// RGB Function ////////////////////////////
void SetupTCS34725() {
  delay(100);
  Serial.begin(115200);
  oled.text(0, 0, "Color Sensor Test!");

  if (tcs.begin()) {
    oled.text(1, 0, "Found sensor!");
    oled.show();
  } else {
    oled.text(1, 0, "No TCS34725 found!");
    oled.show();
    delay(5000);
    //while (1); // halt!
  }
  tcs.setIntegrationTime(TCS34725_INTEGRATIONTIME_154MS);
  tcs.setGain(TCS34725_GAIN_4X);
}
uint16_t ReadRGB() {
  uint16_t clear, red, green, blue;

  delay(60);  // takes 50ms to read

  tcs.getRawData(&red, &green, &blue, &clear);

  /*Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  Serial.println();*/

  // Figure out some basic hex code for visualization

  uint32_t sum = clear;
  float r, g, b;
  r = red;
  r /= sum;
  g = green;
  g /= sum;
  b = blue;
  b /= sum;
  r *= 256;
  g *= 256;
  b *= 256;

  uint16_t _color = color16((int)r, (int)g, (int)b);
  return (_color);
}
void ShowRGB() {
  long RGBColor = ReadRGB();
  oled.clear();
  oled.text(0, 0, "RGB=%l", RGBColor);
  oled.show();
}
void CheckRGB() {
  //red more 3000
  //green more Average 1400
  //yellow more 2400
  //blue more Average
  if (result > 35000) {
    sound(200, 500);
    oled.text(7,0, " Color is Red");
    oled.show();
    Color = 1;;
  }
  else if((result > 22000) && (result < 30000)){
    sound(300,500);
    oled.text(7,0," Color is Yollow");
    oled.show();
    Color = 2;
  }
  else if(result < 25000){
    sound(200,500);
    oled.text(7,0,"Color is Green");
    oled.show();
    Color = 3;
  }
}