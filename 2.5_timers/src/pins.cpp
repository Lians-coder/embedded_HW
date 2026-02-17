#include <Arduino.h>
#include "pins.h"


void setPins()
{
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, relayState);

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, !relayState);
}

uint8_t relayState = HIGH;  // active LOW


void changeStatesFanLed()
{
  // fan ON / OFF
  relayState = fanState ? LOW : HIGH;
  digitalWrite(PIN_RELAY, relayState);

  // mirrow relay state - green LED
  digitalWrite(PIN_LED, !relayState);
}
