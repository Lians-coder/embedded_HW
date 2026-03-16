#include <Arduino.h>
#include "button.h"
#include "uart.h"
#include "led.h"

Uart uart(PIN_RX, PIN_TX);
Btn btn(PIN_BTN);


void setup() 
{
  uart.init();
  btn.init();
  ledInit();
}


void loop() 
{
  btn.update(millis());
  
  uart.process();

  if (btn.pressed()) 
  {
    uart.transmitToggle();
  }
}