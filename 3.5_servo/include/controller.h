#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "potentiometer.h"
#include "servo.h"

constexpr uint32_t POLLING_T = 50;
extern uint32_t lastPoll;

class Controller
{
  private:
    Potentiometer& pot;
    Servo& servo;

  public:
    explicit Controller(Potentiometer& p, Servo& s);
    void update(uint32_t now);
};

#endif  // CONTROLLER_H
