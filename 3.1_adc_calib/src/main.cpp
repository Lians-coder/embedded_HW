#include <Arduino.h>
#include "log.h"
#include "adc.h"
#include "vParams.h"

constexpr uint64_t BAUD_RATE = 115200;
constexpr uint32_t PERIOD = 100;
uint32_t lastRead = 0;


void setup()
{
  Serial.begin(BAUD_RATE);
  setupAdc();
}

void loop()
{
  uint32_t now = millis();
  if (now - lastRead >= PERIOD)
  {
    lastRead = now;
    setVoltageParams();
    printVoltageLog();
    trialCount++;
  }
}
