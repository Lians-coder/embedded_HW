#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

constexpr uint8_t PIN_BTN = 6;
constexpr uint32_t DEBOUNCE_T = 50;


class Btn
{
  private:
    static void IRAM_ATTR isr(void* arg);
    uint32_t dbStart{0};    
    const uint8_t pin;
    volatile bool pressItr{false};
    bool wasPressed{false};
    
    enum class BtnSt
    {
      IDLE,
      DEBOUNCING,
      PRESSED
    };

    BtnSt state = BtnSt::IDLE;

  public:
    explicit Btn(uint8_t p);
    void init();
    void update(uint32_t now);
    bool pressed();
};


#endif  // BUTTON_H