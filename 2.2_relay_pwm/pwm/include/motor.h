#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "pins.h"
#include "voltage.h"

constexpr uint32_t POLLING_T = 15;  // ms
extern uint32_t lastPolling;
extern uint32_t lastChangeMotorSpeed;

constexpr uint32_t DUTY_CYCLE_PERIOD_US = 1000;  // 1 ms - 1 kHz PWM
extern float workPeriodUS;

void setInitValues();
float getDutyCycleWorkPeriod(uint32_t now);
void updateMotor(uint32_t nowUS, uint32_t workT);

#endif  // MOTOR_H
