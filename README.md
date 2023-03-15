# ESP32-S3 Buzzer Library

This library allows you to control a buzzer connected to an ESP32-S3 microcontroller easily, without causing brownouts or interrupting the main code execution. The library is designed to work with the Arduino IDE.

# Features
- Easy-to-use API for controlling a buzzer connected to an ESP32-S3 device.
- Non-blocking operation, allowing the rest of the code to execute without interruption.
- Adjustable parameters like frequency, duration, cycles, and cycle interval.
- Utilizes hardware timers and LEDC peripheral to generate the desired tones.

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
