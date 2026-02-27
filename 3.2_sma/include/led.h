#ifndef LED_H
#define LED_H

#include <stdint.h>

constexpr uint8_t PIN_LED = 6;

// LDR wired to GND -> voltage increases on light
constexpr uint32_t LOW_TRESHOLD = 900;
constexpr uint32_t HIGH_TRESHOLD = 1100;

extern uint8_t ledState;

void setupLedPin();
void updateLedState(uint32_t voltage);

#endif  // LED_H