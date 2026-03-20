#include <esp_log.h>
#include "servo.h"

using namespace ServoConfig;

static const char *TAG = "Servo";

void Servo::init(void)
{
  ledc_timer_config_t timer_config = {
    .speed_mode       = LEDC_LOW_SPEED_MODE,
    .duty_resolution  = SERVO_RESOLUTION,        
    .timer_num        = SERVO_UNIT,
    .freq_hz          = SERVO_FREQ,
    .clk_cfg          = LEDC_AUTO_CLK,
    .deconfigure      = false
  };
  ESP_ERROR_CHECK(ledc_timer_config(&timer_config));

  ledc_channel_config_t channel_config = {
    .gpio_num       = SERVO_PIN,        
    .speed_mode     = LEDC_LOW_SPEED_MODE,
    .channel        = SERVO_CHANNEL,
    .intr_type      = LEDC_INTR_DISABLE,
    .timer_sel      = SERVO_UNIT,
    .duty           = 0,
    .hpoint         = 0,
    .sleep_mode     = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD,
    .flags          = {}
  };
  ESP_ERROR_CHECK(ledc_channel_config(&channel_config));
}


uint16_t Servo::clamp(uint16_t value, const uint16_t valMin, const uint16_t valMax)
{
  if (value < valMin) return valMin;
  if (value > valMax) return valMax;
  return value;
}


uint16_t Servo::mapRange(uint16_t value, uint16_t inMin, uint16_t inMax, uint16_t outMin, uint16_t outMax)
{
  if (inMin == inMax)
  {
    return outMax;
  }
  value = clamp(value, inMin, inMax);
  return (outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin));
}


void Servo::servoSetAngleFromMv(uint16_t mv)
{
  mv = clamp(mv, LIGHT_MIN_MV, LIGHT_MAX_MV);
  uint16_t angle = mapRange(mv, LIGHT_MIN_MV, LIGHT_MAX_MV, SERVO_MIN_DEG, SERVO_MAX_DEG);
  ESP_LOGI(TAG, "Angle: %u", angle);
  Params params = angleToPulseAndDuty(angle);
  setAndUpdateDuty(params.duty);  
  ESP_LOGI(TAG, "Pulse US: %lu\tDuty: %lu", params.pulse, params.duty);
}


Servo::Params Servo::angleToPulseAndDuty(uint16_t angle)
{
  angle = clamp(angle, SERVO_MIN_DEG, SERVO_MAX_DEG);
  Params p;
  p.pulse = SERVO_MIN_US + ((uint32_t)angle * (SERVO_MAX_US - SERVO_MIN_US) / SERVO_MAX_DEG);
  p.duty = p.pulse * SERVO_MAX_DUTY / (SERVO_PERIOD_MS * 1000U);
  return p;
}


void Servo::test()
{
  setAndUpdateDuty(DUTY_TEST_0);
  vTaskDelay(pdMS_TO_TICKS(SUPERLOOP_DELAY * 5));

  setAndUpdateDuty(DUTY_TEST_1);
  vTaskDelay(pdMS_TO_TICKS(SUPERLOOP_DELAY * 5));
}


void Servo::setAndUpdateDuty(uint32_t duty)
{
  ESP_ERROR_CHECK(ledc_set_duty(LEDC_LOW_SPEED_MODE, SERVO_CHANNEL, duty));
  ESP_ERROR_CHECK(ledc_update_duty(LEDC_LOW_SPEED_MODE, SERVO_CHANNEL));
}