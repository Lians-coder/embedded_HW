#ifndef SERVO_H
#define SERVO_H

#include <freertos/FreeRTOS.h>
#include <driver/ledc.h>

constexpr uint32_t SUPERLOOP_DELAY = 20;

namespace ServoConfig
{
  constexpr uint8_t SERVO_PIN = 5;

  constexpr uint32_t SERVO_FREQ = 50;
  constexpr uint32_t SERVO_PERIOD_MS = 1000 / SERVO_FREQ;
  constexpr ledc_timer_bit_t SERVO_RESOLUTION = LEDC_TIMER_12_BIT;
  constexpr uint16_t SERVO_MAX_DUTY =  ((1 << SERVO_RESOLUTION) - 1);
  constexpr ledc_timer_t SERVO_UNIT = LEDC_TIMER_0;
  constexpr ledc_channel_t SERVO_CHANNEL = LEDC_CHANNEL_0;

  constexpr uint32_t DUTY_TEST_0 = 204;
  constexpr uint32_t DUTY_TEST_1 = 408;

  constexpr uint8_t SERVO_MIN_DEG = 10;
  constexpr uint8_t SERVO_MAX_DEG = 170;
  constexpr uint16_t SERVO_MIN_US = 500;
  constexpr uint16_t SERVO_MAX_US = 2500;
  constexpr uint16_t LIGHT_MIN_MV = 50;
  constexpr uint16_t LIGHT_MAX_MV = 3000;         
}


class Servo
{
  private:
    uint16_t mapRange(
      uint16_t value, 
      uint16_t inMin, 
      uint16_t inMax, 
      uint16_t outMin, 
      uint16_t outMax
    );
    void setAndUpdateDuty(uint32_t duty);
    uint16_t clamp(uint16_t value, const uint16_t valMin, const uint16_t valMax);

    struct Params
    {
      uint32_t pulse{0};
      uint32_t duty{0};
    };
    Params params;

    Params angleToPulseAndDuty(uint16_t angle);

  public:
    void init(void);
    void servoSetAngleFromMv(uint16_t mv);
    void test();
};


#endif  // SERVO_H