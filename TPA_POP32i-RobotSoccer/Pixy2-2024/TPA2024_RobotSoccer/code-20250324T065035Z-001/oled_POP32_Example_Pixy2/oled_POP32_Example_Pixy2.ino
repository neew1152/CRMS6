#include <POP32.h> 
#include <POP32_Pixy2.h>

POP32_Pixy2 pixy;

void setup() 
{
  Serial.begin(115200);
  oled.clear();
  pixy.init();

  oled.text(1, 0, "Started!");
  oled.show();
  delay(1000);
}

void loop() 
{
  oled.clear();

  if (pixy.updateBlocks()) 
  {
    char buffer[16];  
    sprintf(buffer, "Detected: %d", pixy.getNumBlocks());
    oled.text(0, 0, buffer);

    int line = 1;  // Line index for displaying data
    for (int i = 1; i <= 7; i++)  // Loop through detected signatures
    {
      if (pixy.sigSize[i]) // If a signature is detected
      {
        sprintf(buffer, "Sig: %d", i);
        oled.text(line++, 0, buffer);

        for (int j = 0; j < pixy.sigSize[i]; j++) // Loop through signature indexes
        {
          sprintf(buffer, "%d,%d,%d,%d", 
                  pixy.sigInfo[i][j].x, 
                  pixy.sigInfo[i][j].y, 
                  pixy.sigInfo[i][j].width, 
                  pixy.sigInfo[i][j].height);
          oled.text(line++, 0, buffer);

          if (line > 7) break; // Prevent exceeding OLED display limit
        }
      }
      if (line > 7) break; // Stop if OLED screen runs out of space
    }
  } 
  else 
  {
    oled.text(0, 0, "Not detected");
  }

  oled.show();
  delay(500);
}

// Convert Serial to OLED by ChatGPT-4o
// Prompt: Convert Display, Serial to oled