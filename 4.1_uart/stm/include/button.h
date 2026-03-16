#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include "main.h"

#define DEBOUNCE_TIME 50


typedef enum 
{
  BTN_IDLE,
  DEBOUNCING,
  PRESSED
}
BtnSt;

typedef struct
{
  BtnSt state;
  uint32_t lastDebounceTime;
  bool wasPressed;
}
ButtonContext;

extern ButtonContext btnCtx;

void btnUpdate(uint32_t now);
bool btnPressed();

#endif  // BUTTON_H