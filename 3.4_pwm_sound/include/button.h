#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <Arduino.h>

constexpr uint8_t BTN_PIN = 6;
constexpr uint32_t DEBOUNCE_T = 50;

class Btn
{
  private:
    uint32_t dbStart{0};
    const uint8_t pin;
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
    explicit Btn(uint8_t p);
    bool isInitialized() const;
    void init();
    void update(uint32_t now);
    bool wasPressed();
};

#endif  // BUTTON_H
