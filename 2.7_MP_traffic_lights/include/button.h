#ifndef BUTTON_H
#define BUTTON_H

#include "types.h"

constexpr pin_t BTN_PIN = 4;
constexpr uint32_t DEBOUNCE_T = 50;

class Btn
{
  private:
    uint32_t dbStart{0};
    const pin_t pin;
    bool pressed{false};
    volatile bool isrFlag{false};

    enum class BtnSt
    {
      NONE,
      IDLE,
      DEBOUNCING,
      PRESSED
    };

    BtnSt state{BtnSt::NONE};

    static void IRAM_ATTR isr(void *arg);
  
  public:
    explicit Btn(pin_t p);
    bool isInitialized() const;
    void init();
    void update(uint32_t now);
    bool wasPressed();
};

#endif  // BUTTON_H
