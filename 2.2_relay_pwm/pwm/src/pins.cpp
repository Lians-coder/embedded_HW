#include "pins.h"

void setupPins()
{
  pinMode(PIN_POTENTIOMETER, INPUT);
  analogReadResolution(adcResolution);
  analogSetAttenuation(adcAttenuation);

  pinMode(PIN_MOTOR, OUTPUT);
  digitalWrite(PIN_MOTOR, LOW);
}
