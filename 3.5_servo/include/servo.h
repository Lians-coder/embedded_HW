#ifndef SERVO_H
#define SERVO_H

#include <driver/ledc.h>

constexpr uint8_t PIN_SERVO = 6;

constexpr uint32_t SERVO_FREQ = 50;
constexpr uint32_t PERIOD_US  = 1000000 / SERVO_FREQ;  // 20 ms

constexpr ledc_channel_t SERVO_CHANNEL = LEDC_CHANNEL_0;
constexpr ledc_timer_t SERVO_TIMER     = LEDC_TIMER_0;
constexpr ledc_timer_bit_t RESOLUTION  = LEDC_TIMER_13_BIT;  // 8192

constexpr uint32_t MIN_PULSE_US = 500;  // 0 deg
constexpr uint32_t MID_PULSE_US = 1500;
constexpr uint32_t MAX_PULSE_US = 2500;  // 180 deg

constexpr uint8_t INIT_ANGLE_DEG = 90;
constexpr uint32_t DUTY_RIGHT_ANGLE = MID_PULSE_US * (1 << RESOLUTION) / PERIOD_US;


class Servo
{
  private:
    void setupTimer();
    void setupChannel();
    uint8_t pin;
    ledc_channel_t channel;
    uint8_t angle{0};  

  public:
    explicit Servo(uint8_t p, ledc_channel_t ch);
    
    void init();
    void setAngle(float angle);
    uint8_t getAngle() const;
};

#endif  // SERVO_H
