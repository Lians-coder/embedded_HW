#include <Arduino.h>
#include "log.h"
#include "vParams.h"

uint8_t trialCount = 0;
extern VoltageParams vParams;

void printHeaders()
{
  if (trialCount % TRIAL_COUNT == 0)
  {
    Serial.println("RAW    U_man(mV)    U_cal(mV)    Error(%)");
    Serial.println("-----------------------------------------");
    trialCount = 0;
  }
}

void printVoltageLog()
{
  printHeaders();
  Serial.printf("%4d   %7.2f    %9lu    %6.2f\n",
  vParams.raw,
  vParams.vManual,
  vParams.vCalib,
  vParams.err);
}
