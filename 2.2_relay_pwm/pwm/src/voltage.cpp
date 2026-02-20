#include "voltage.h"

uint32_t voltageRaw = 0;
float voltageFiltered = 0;

uint32_t getVoltage()
{
  voltageRaw = analogReadMilliVolts(PIN_POTENTIOMETER);
  voltageFiltered = voltageRaw * alpha + (1 - alpha) * voltageFiltered;
  return static_cast<uint32_t>constrain(voltageFiltered, MIN_VOLTAGE, MAX_VOLTAGE);
}


uint8_t getPWM(uint32_t voltage)
{
  uint8_t coefPWM = map(voltage, MIN_VOLTAGE, MAX_VOLTAGE, 0, 100);
  if (coefPWM < DEAD_ZONE)
  {
    coefPWM = 0;
  }
  else if (coefPWM > (100 - DEAD_ZONE))
  {
    coefPWM = 100;
  }
  return coefPWM;
}

