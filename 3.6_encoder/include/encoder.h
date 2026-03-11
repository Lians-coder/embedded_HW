#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "button.h"

constexpr uint8_t PIN_ENC_A  = 4;
constexpr uint8_t PIN_ENC_B  = 5;
constexpr uint8_t PIN_ENC_SW = 6;
constexpr uint32_t ENC_DEBOUNCE_US = 3000;  // 3 ms

class Encoder
{
  public:
    explicit Encoder(uint8_t pA, uint8_t pB, uint8_t pSw, bool rotRev = false);
    void init();
    bool rotationCw();  // uint32_t now
    bool rotationCcw();  // uint32_t now
    bool btnPressed();
    void btnUpdate(uint32_t now);
    
    bool rotationReverse{false};

    enum class Direction
    {
      NONE,
      CW,
      CCW
    };
    Direction lastDir{Direction::NONE};  

  private:
    uint8_t IRAM_ATTR readState();
    
    static void IRAM_ATTR isrA(void* arg);
    static void IRAM_ATTR isrB(void* arg);
    void IRAM_ATTR handleIsrDirection();

    static const int8_t table[16];
    const uint8_t pinA;
    const uint8_t pinB;
    Btn btn;

    uint8_t lastState;
    volatile bool flagCw{false};
    volatile bool flagCcw{false};

    volatile uint32_t lastTick{0};
    static constexpr uint32_t debounceT = ENC_DEBOUNCE_US;
    Direction lastAcceptedDir{Direction::NONE};  
};


#endif  // ENCODER_H
