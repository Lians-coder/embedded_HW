#ifndef LED_H
#define LED_H

#include <Arduino.h>

constexpr uint8_t PIN_LED = 5;

void ledInit();
void toggleLed();

#endif  // LED_H