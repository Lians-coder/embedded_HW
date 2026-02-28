#include <Arduino.h>
#include "adc.h"
#include "ledc_pwm.h"

constexpr uint32_t PERIOD = 10;
uint32_t lastRead = 0;

void setup()
{
  setupADC();
  setupLEDC();
}

void loop()
{
  uint32_t now = millis();
  if (now - lastRead >= PERIOD)
  {
    lastRead = now;
    updatePWM(getVoltage());
  }
}
