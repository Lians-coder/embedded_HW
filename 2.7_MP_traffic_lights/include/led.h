#ifndef LED_H
#define LED_H

#include <array>
#include "types.h"
#include "times.h"

constexpr pin_t LED_RED_PIN     = 5;
constexpr pin_t LED_YELLOW_PIN  = 6;
constexpr pin_t LED_GREEN_PIN   = 7;

constexpr uint8_t LED_COUNT = 3;

class Led
{
  private:
    uint32_t lastToggle{0};
    uint32_t lastBlink{0};
    pin_t pin;
    bool isOn{false};

  public: 
    explicit Led(pin_t p);
    void init();
    void reset();
    bool stable(uint32_t now, uint32_t totalPeriod);
    bool blink(uint32_t now, uint32_t totalPeriod, uint32_t blinkPeriod = BLINK_T);
    void blinkSpecial(uint32_t now, uint32_t blinkPeriod);
};

#endif  // LED_H
