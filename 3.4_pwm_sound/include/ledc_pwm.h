#ifndef LEDC_PWM_H
#define LEDC_PWM_H

#include <driver/ledc.h>
#include <Arduino.h>

constexpr uint32_t DUTY_CYCLE = 512;
constexpr uint16_t FREQ = 0;  // silent start
constexpr ledc_timer_bit_t RESOLUTION = LEDC_TIMER_10_BIT;

constexpr uint8_t PIN_BUZZ_1 = 5;
constexpr ledc_channel_t CH_BUZZ_1 = LEDC_CHANNEL_0;

struct PwmOut
{
  uint8_t pin;
  ledc_channel_t channel;
};

#endif  // LEDC_PWM_H
