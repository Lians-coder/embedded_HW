#include "ledc_pwm.h"

uint32_t dutyCycle = 512;


void setupTimer()
{
  ledc_timer_config_t timerConfig = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_10_BIT,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = FREQ,
    .clk_cfg = LEDC_AUTO_CLK
  };
  ledc_timer_config(&timerConfig);
}


void setupChan(uint8_t pin, ledc_channel_t channel)
{
  ledc_channel_config_t chConfig = {
    .gpio_num = pin,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = channel,
    .timer_sel = LEDC_TIMER_0,
    .duty = dutyCycle,
    .hpoint = 0
  };

  ledc_channel_config(&chConfig);
}


void setupChannels()
{
  for (const PwmOut &out : outputs)
  {
    setupChan(out.pin, out.channel);
  } 
}


void setupLEDC()
{
  setupTimer();
  setupChannels();
}


void setDuty(ledc_channel_t channel, uint32_t duty)
{
  ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, duty);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, channel);
}


void updatePWM(uint32_t voltage)
{
  uint32_t duty = map(voltage, V_MIN, V_MAX, 0, 1023);
  for (const PwmOut &out : outputs)
  {
    setDuty(out.channel, duty);
  }
}
