#ifndef APP_H
#define APP_H

#include <stdint.h>

extern uint32_t blinkPeriod;
extern uint32_t lastToggle;
extern GPIO_PinState ledState;

void setup();
void loop();

void blink(uint32_t now);

#endif  // APP_H