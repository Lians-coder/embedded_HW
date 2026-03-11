#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "button.h"

constexpr uint8_t PIN_ENC_A  = 5;
constexpr uint8_t PIN_ENC_B  = 4;
constexpr uint8_t PIN_ENC_SW = 6;


class Encoder
{
  public:
    explicit Encoder(uint8_t pA, uint8_t pB, uint8_t pSw);
    void init();
    bool btnPressed();
    void btnUpdate(uint32_t now);

    volatile int8_t steps{0};

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
    volatile int8_t acc = 0; 
};


#endif  // ENCODER_H
