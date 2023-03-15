# ESP32-S3 Buzzer Library

A non-blocking buzzer library for ESP32S3 that enables playing multiple tones with specified frequency, on/off duration, and number of cycles, without interrupting the main loop.

# Features
- Non-blocking: The library allows the main loop to continue running while playing tones.
- Tone Queue: Queue up multiple tones to be played one after another.
- Adjustable parameters: Set the frequency, on/off duration, and number of cycles for each tone.

# Installation
1. Download the latest release of the library as a ZIP file.
2. Open the Arduino IDE, go to Sketch > Include Library > Add .ZIP Library, and select the downloaded ZIP file.
3. Restart the Arduino IDE.

# Usage
```
#include <Arduino.h>
#include "ESP32S3Buzzer.h"

// Set the buzzer pin and channel
const uint8_t buzzerPin = 27;
const uint8_t buzzerChannel = 0;

// Create an instance of ESP32S3Buzzer
ESP32S3Buzzer buzzer(buzzerPin, buzzerChannel);

void setup() {
  // Initialize the buzzer
  buzzer.begin();
  
  // Add a tone to the queue
  uint32_t freq = 1000;
  uint32_t onDuration = 200;
  uint32_t offDuration = 200;
  uint16_t cycles = 5;
  buzzer.tone(freq, onDuration, offDuration, cycles);
}

void loop() {
  // Call the update method to process tones in the queue
  buzzer.update();
  
  // Your other code here
}
```
