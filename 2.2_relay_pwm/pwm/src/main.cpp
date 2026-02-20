#include <Arduino.h>
#include "motor.h"

void setup()
{
  setupPins();
  setInitValues();
}

void loop()
{
  uint32_t now = millis();
  uint32_t nowUS = micros();
  updateMotor(nowUS, getDutyCycleWorkPeriod(now));
}
