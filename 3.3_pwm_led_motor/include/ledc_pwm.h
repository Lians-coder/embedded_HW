#ifndef LEDC_PWM_H
#define LEDC_PWM_H

#include <driver/ledc.h>
#include <Arduino.h>

constexpr uint8_t PIN_MOTOR = 5;
constexpr uint8_t PIN_LED   = 6;
constexpr ledc_channel_t CH_LED   = LEDC_CHANNEL_0;
constexpr ledc_channel_t CH_MOTOR = LEDC_CHANNEL_1;

constexpr uint32_t FREQ  = 10000;
constexpr uint32_t V_MIN = 0;
constexpr uint32_t V_MAX = 3300;
extern uint32_t dutyCycle;

struct PwmOut
{
  uint8_t pin;
  ledc_channel_t channel;
};

constexpr PwmOut outputs[] = {
  {PIN_LED, CH_LED},
  {PIN_MOTOR, CH_MOTOR}
};


void setupTimer();
void setupChannels();
void setupLEDC();
void updatePWM(uint32_t voltage);

#endif  // LEDC_PWM_H