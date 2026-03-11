#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "encoder.h"
#include "servo.h"

constexpr uint8_t PIN_CODE[] = {7, 9, 0, 3};
constexpr size_t PIN_SIZE = sizeof(PIN_CODE);
constexpr uint8_t MAX_TRIALS = 3;


class Controller
{
  private:
    Encoder& encoder;
    Servo& servo;
    
    void selectDigit();
    void confirmDigit();
    bool validate();
    void openSafe();
    void resetAttempt();
    void trialsOver();

    uint8_t digits[PIN_SIZE];
    uint8_t digitIndex{0};
    uint8_t currentDigit{0};
    uint8_t trials{0};

    enum class DigitState
    { 
      SELECTING, 
      CONFIRMED
    };
    DigitState digitState = DigitState::SELECTING;
    
  public:
    explicit Controller(Encoder& e, Servo& s);
    void init();
    void update(uint32_t now);
};

#endif  // CONTROLLER_H
