 #include <POP32.h> 
#include <POP32_Huskylens.h>

POP32_Huskylens huskylens;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  oled.clear();
  
  while (!huskylens.begin(Wire)) { 
    oled.text(1, 0, "Begin failed!");  // Show error if connection fails
    oled.show();
    delay(100);
  }

  huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION); // Set to color recognition mode
  oled.text(1, 0, "Started!");
  oled.show();
  delay(1000);
}

void loop() {
  oled.clear();

  if (huskylens.updateBlocks()) {
    char buffer[16];  // Buffer for formatted text
    sprintf(buffer, "Detected: %d", huskylens.getNumBlocks());
    oled.text(0, 0, buffer);

    int line = 1; // Line index for displaying data
    for (int i = 1; i <= 7; i++) {  // Loop through detected blocks
      if (huskylens.blockSize[i]) { // If blocks are detected
        sprintf(buffer, "Block: %d", i);
        oled.text(line++, 0, buffer);
        
        for (int j = 0; j < huskylens.blockSize[i]; j++) {
          sprintf(buffer, "%d,%d,%d,%d", 
                  huskylens.blockInfo[i][j].x, 
                  huskylens.blockInfo[i][j].y, 
                  huskylens.blockInfo[i][j].width, 
                  huskylens.blockInfo[i][j].height);
          oled.text(line++, 0, buffer);
          if (line > 7) break; // Prevent exceeding display limit
        }
      }
      if (line > 7) break; // Stop if OLED screen runs out of space
    }
  } else {
    oled.text(0, 0, "Not detected");
  }

  oled.show();
  delay(500);
}

// Convert Serial to OLED by ChatGPT-4o
// Prompt: Convert Display, Serial to oled