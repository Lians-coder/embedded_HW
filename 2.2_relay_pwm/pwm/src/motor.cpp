#include "motor.h"

uint32_t lastChangeMotorSpeed = 0;
uint32_t lastPolling = 0;
float workPeriodUS = 0;

void setInitValues()
{
  voltageRaw = analogReadMilliVolts(PIN_POTENTIOMETER);
  voltageFiltered = voltageRaw;
  lastChangeMotorSpeed = micros();
}

float getDutyCycleWorkPeriod(uint32_t now)
{
  if (now - lastPolling >= POLLING_T)
  {
    uint32_t clamped = getVoltage();
    uint8_t coefPWM = getPWM(clamped);
    workPeriodUS = DUTY_CYCLE_PERIOD_US * coefPWM / 100.0;
    lastPolling = now;
  }
  return workPeriodUS;
}


void updateMotor(uint32_t nowUS, uint32_t workT)
{
  uint32_t elapsed = nowUS - lastChangeMotorSpeed;

  if (elapsed >= DUTY_CYCLE_PERIOD_US)
  {
    lastChangeMotorSpeed += DUTY_CYCLE_PERIOD_US;
    elapsed = 0;
  }

  digitalWrite(PIN_MOTOR, (elapsed < workT) ? HIGH : LOW);
}
