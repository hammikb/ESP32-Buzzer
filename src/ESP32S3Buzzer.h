#ifndef ESP32S3Buzzer_h
#define ESP32S3Buzzer_h

#include <Arduino.h>
#include <driver/timer.h>
#include <driver/ledc.h>

class ESP32S3Buzzer {
public:
  ESP32S3Buzzer(uint8_t buzzerPin, uint8_t ledcChannel = 0, uint8_t timerResolution = 8, uint32_t pwmFrequency = 2000, timer_idx_t timerIndex = TIMER_0);
  void begin();
  void tone(uint32_t frequency, uint32_t duration = 0, uint16_t cycles = 1, uint32_t cycleInterval = 0);
  void noTone();
  void updateTimer(uint32_t interval);

private:
  uint8_t _buzzerPin;
  uint8_t _ledcChannel;
  uint8_t _timerResolution;
  uint32_t _pwmFrequency;
  timer_idx_t _timerIndex;

  uint32_t _duration;
  uint16_t _cycles;
  uint32_t _cycleInterval;
  bool _isDuration;

  static void IRAM_ATTR onTimer(void* arg);
  void startTimer(uint32_t interval, bool isDuration);
  void stopTimer();
};

#endif
