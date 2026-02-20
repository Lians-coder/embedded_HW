#ifndef VOLTAGE_H
#define VOLTAGE_H

#include <Arduino.h>
#include "pins.h"

constexpr uint32_t MIN_VOLTAGE = 0;
constexpr uint32_t MAX_VOLTAGE = 3300;

extern uint32_t voltageRaw;
extern float voltageFiltered;
constexpr float alpha = 0.1;

constexpr uint8_t DEAD_ZONE = 10;  // % near edge values

uint32_t getVoltage();
uint8_t getPWM(uint32_t voltage);

#endif  // VOLTAGE_H
