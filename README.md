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
1. Include the library in your sketch using the following directive:
```
#include <ESP32S3Buzzer.h>
```

2. Create an instance of the ESP32S3Buzzer class:
```
ESP32S3Buzzer buzzer(buzzerPin, ledcChannel, timerResolution, pwmFrequency, timerIndex);
```

- buzzerPin: The GPIO pin connected to the buzzer.
- ledcChannel: The LEDC channel to use (default: 0).
- timerResolution: The resolution of the LEDC timer (default: 8).
- pwmFrequency: The PWM frequency to use for the buzzer (default: 2000 Hz).
- timerIndex: The hardware timer index to use (default: TIMER_0).

3. Initialize the buzzer by calling the begin() method in the setup() function:
```
buzzer.begin();
```

4. Use the tone() method to play a tone on the buzzer:
```
buzzer.tone(frequency, duration, cycles, cycleInterval);
```

- frequency: The frequency of the tone in Hz.
- duration: The duration of the tone in milliseconds (default: 0).
- cycles: The number of times to repeat the tone (default: 1).
- cycleInterval: The interval between tone cycles in milliseconds (default: 0).

5. Use the noTone() method to stop playing the tone:
```
buzzer.noTone();
```
# Example 
```
#include <ESP32S3Buzzer.h>

ESP32S3Buzzer buzzer1(1, 0); // Buzzer 1 connected to GPIO 1, using LEDC channel 0
ESP32S3Buzzer buzzer2(2, 1); // Buzzer 2 connected to GPIO 2, using LEDC channel 1

void setup() {
  buzzer1.begin();
  buzzer2.begin();
}

void loop() {
  // Buzzer 1: Play a 1000 Hz tone for 500 ms, repeat 3 times with a 200 ms interval between cycles
  buzzer1.tone(1000, 500, 3, 200);
  
  delay(2000); // Wait for 2 seconds

  // Buzzer 2: Play a 1500 Hz tone for 300 ms, repeat 2 times with a 100 ms interval between cycles
  buzzer2.tone(1500, 300, 2, 100);

  delay(5000); // Wait for 5 seconds
}
```
In this example, two buzzers are connected to GPIO 1 and GPIO 2, using LEDC channels 0 and 1, respectively. Buzzer 1 plays a 1000 Hz tone for 500 ms, repeating it 3 times with a 200 ms interval between cycles. After a 2-second delay, Buzzer 2 plays a 1500 Hz tone for 300 ms, repeating it 2 times with a 100 ms interval between cycles. The sequence then waits for 5 seconds before starting again.
