#include <Arduino.h>

#include "led.h"

void setup() 
{
  setupPins();
  setPinsLowOnSetup();
}

void loop() 
{
  setPinsState(!ledRedState, !ledBlueState);
  handlerPinsState();
  delay(500);
}
