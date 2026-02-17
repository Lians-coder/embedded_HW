#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

constexpr uint8_t PIN_RELAY = 5;
constexpr uint8_t PIN_LED   = 6;

void setPins();
void changeStatesFanLed();

extern volatile bool fanState;
extern uint8_t relayState;

#endif  // PINS_H
