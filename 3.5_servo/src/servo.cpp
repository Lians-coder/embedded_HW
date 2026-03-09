#include <Arduino.h>
#include "servo.h"

Servo::Servo(uint8_t p, ledc_channel_t ch) : pin(p), channel(ch) {};


void Servo::setupTimer()
{
  ledc_timer_config_t timerConf = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = RESOLUTION,
    .timer_num = SERVO_TIMER,
    .freq_hz = SERVO_FREQ,
    .clk_cfg = LEDC_AUTO_CLK
  };

  ledc_timer_config(&timerConf);
}


void Servo::setupChannel()
{
  ledc_channel_config_t channelConf = {
    .gpio_num = pin,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = channel,
    .intr_type = LEDC_INTR_DISABLE,
    .timer_sel = SERVO_TIMER,
    .duty = DUTY_RIGHT_ANGLE,
    .hpoint = 0
  };
  
  ledc_channel_config(&channelConf);
}


void Servo::init()
{
  setupTimer();
  setupChannel();
  setAngle(INIT_ANGLE_DEG);
}


void Servo::setAngle(float angleVal)
{
  angleVal = constrain(angleVal, 0.0f, 180.0f);
  angle = angleVal;

  float pulse = MIN_PULSE_US + (angleVal * (MAX_PULSE_US - MIN_PULSE_US) / 180.0f);

  uint32_t duty = (uint32_t)((pulse * (1 << RESOLUTION) / PERIOD_US));

  ledc_set_duty(LEDC_LOW_SPEED_MODE, channel, duty);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, channel);
}


uint8_t Servo::getAngle() const
{
  return angle;
}
