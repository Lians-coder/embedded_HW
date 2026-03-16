#ifndef BUTTON_H
#define BUTTON_H

#include "main.h"

#define DEBOUNCE_TIME 50

extern uint8_t buttonState;
extern uint32_t lastDebounceTime;
extern uint8_t lastReading;

void btnUpdate();

#endif  // BUTTON_H