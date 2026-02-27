#include <Arduino.h>
#include "adc.h"
#include "led.h"

constexpr uint32_t PERIOD = 10;
uint32_t lastRead = 0;

void setup()
{
  setupAdc();
  setupLedPin();
}

void loop()
{
  uint32_t now = millis();
  if (now - lastRead >= PERIOD)
  {
    lastRead = now;
    updateLedState(getVoltage());
  }
}
