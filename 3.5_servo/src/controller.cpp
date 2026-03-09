#include "controller.h"

uint32_t lastPoll = 0;

Controller::Controller(Potentiometer& p, Servo& s)
  : pot(p), servo(s) {}

void Controller::update(uint32_t now)
{
  if (now - lastPoll >= POLLING_T)
  {
    lastPoll = now;
    pot.update();
    servo.setAngle(pot.getAngle());
    Serial.printf("Servo angle: %u deg\n", servo.getAngle());
  }
}

