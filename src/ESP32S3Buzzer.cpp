#include "ESP32S3Buzzer.h"

ESP32S3Buzzer *self;

ESP32S3Buzzer::ESP32S3Buzzer(uint8_t buzzerPin, uint8_t ledcChannel, uint8_t timerResolution, uint32_t pwmFrequency, timer_idx_t timerIndex)
  : _buzzerPin(buzzerPin), _ledcChannel(ledcChannel), _timerResolution(timerResolution), _pwmFrequency(pwmFrequency), _timerIndex(timerIndex) {
  self = this;
}

void ESP32S3Buzzer::begin() {
  pinMode(_buzzerPin, OUTPUT);
  ledcSetup(_ledcChannel, _pwmFrequency, _timerResolution);
  ledcAttachPin(_buzzerPin, _ledcChannel);
}

void ESP32S3Buzzer::tone(uint32_t frequency, uint32_t duration, uint16_t cycles, uint32_t cycleInterval) {
  _duration = duration;
  _cycles = cycles;
  _cycleInterval = cycleInterval;

  ledcWriteTone(_ledcChannel, frequency);
  if (duration > 0) {
    _isDuration = true;
    startTimer(duration, true);
  }
}

void ESP32S3Buzzer::noTone() {
  ledcWriteTone(_ledcChannel, 0);
}

void IRAM_ATTR ESP32S3Buzzer::onTimer(void* arg) {
  timer_group_clr_intr_status_in_isr(TIMER_GROUP_0, self->_timerIndex);

  if (self->_isDuration) {
    self->noTone();
    if (self->_cycles > 1) {
      self->_cycles--;
      self->_isDuration = false;
      self->startTimer(self->_cycleInterval, false);
    } else {
      self->stopTimer();
    }
  } else {
    self->tone(1000, self->_duration, self->_cycles, self->_cycleInterval);
  }
}

void ESP32S3Buzzer::startTimer(uint32_t interval, bool isDuration) {
  _isDuration = isDuration;

  timer_config_t config = {
    .alarm_en = TIMER_ALARM_EN,
    .counter_en = TIMER_PAUSE,
    .intr_type = TIMER_INTR_LEVEL,
    .counter_dir = TIMER_COUNT_UP,
    .auto_reload = (timer_autoreload_t) false,
    .divider = 80
  };

  timer_init(TIMER_GROUP_0, _timerIndex, &config);
  timer_set_counter_value(TIMER_GROUP_0, _timerIndex, 0x00000000ULL);
  timer_set_alarm_value(TIMER_GROUP_0, _timerIndex, interval * 1000);
  timer_enable_intr(TIMER_GROUP_0, _timerIndex);
  timer_isr_register(TIMER_GROUP_0, _timerIndex, onTimer, NULL, ESP_INTR_FLAG_IRAM, NULL);

  timer_start(TIMER_GROUP_0, _timerIndex);
}

void ESP32S3Buzzer::stopTimer() {
  timer_pause(TIMER_GROUP_0, _timerIndex);
  timer_disable_intr(TIMER_GROUP_0, _timerIndex);
}

void ESP32S3Buzzer::updateTimer(uint32_t interval) {
  timer_set_alarm_value(TIMER_GROUP_0, _timerIndex, interval * 1000);
}
