#ifndef SERVO_H
#define SERVO_H

#include <driver/ledc.h>

constexpr uint8_t PIN_SERVO = 7;

constexpr uint8_t ANGLE_OPEN   = 0;
constexpr uint8_t ANGLE_CLOSED = 180;

constexpr uint32_t SERVO_FREQ = 50;
constexpr uint32_t PERIOD_US  = 1000000 / SERVO_FREQ;  // 20 ms

constexpr ledc_channel_t SERVO_CHANNEL = LEDC_CHANNEL_0;
constexpr ledc_timer_t SERVO_TIMER     = LEDC_TIMER_0;
constexpr ledc_timer_bit_t RESOLUTION  = LEDC_TIMER_13_BIT;  // 8192

constexpr uint32_t MIN_PULSE_US = 500;  // 0 deg
constexpr uint32_t MAX_PULSE_US = 2500;  // 180 deg
constexpr uint32_t DUTY_INIT = 0;

class Servo
{
  private:
    void setupTimer();
    void setupChannel();
    uint8_t pin;
    ledc_channel_t channel;  

  public:
    explicit Servo(uint8_t p, ledc_channel_t ch);
    
    void init();
    void setAngle(float angle);
};

#endif  // SERVO_H
