#include "led.h"

void ledInit()
{
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);  
}


void toggleLed()
{
  digitalWrite(PIN_LED, !digitalRead(PIN_LED));
}