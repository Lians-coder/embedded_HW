#include <Arduino.h>
#include "led.h"

uint8_t ledState = LOW;

void setupLedPin()
{
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, ledState);
}

void updateLedState(uint32_t voltage)
{
  if ((!ledState && voltage < LOW_TRESHOLD) || (ledState && voltage > HIGH_TRESHOLD))
  {
    ledState = !ledState;
    digitalWrite(PIN_LED, ledState);
  }
}
