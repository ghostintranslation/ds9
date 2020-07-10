/*
 __    _  _____   ___      ___ _  _     __    _ ______ _    
/__|_|/ \(_  |     | |\|    | |_)|_||\|(_ |  |_| |  | / \|\|
\_|| |\_/__) |    _|_| |    | | \| || |__)|__| | | _|_\_/| |

https://ghostintranslation.bandcamp.com
https://www.instagram.com/ghostintranslation
https://github.com/ghostintranslation
*/

#include <Audio.h>
#include "DS9.h"

// Instanciation of DS9
DS9 * ds9 = DS9::getInstance();

// Connecting DS9 to general audio output
AudioOutputI2S  i2s2;
AudioConnection patchCord1(*ds9->getOutput(), 0, i2s2, 0);
AudioConnection patchCord2(*ds9->getOutput(), 0, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1;
AudioControlSGTL5000 audioBoard;
 
void setup() {
  Serial.begin(115200);
  
  ds9->init();

  // Audio connections require memory to work.
  AudioMemory(40);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);
  
  while (!Serial && millis() < 2500); // wait for serial monitor

  // Starting sequence
  Serial.println("Ready!");
}

void loop() {
  ds9->update();
}
