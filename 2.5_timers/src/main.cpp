#include <Arduino.h>
#include "esp_task_wdt.h"
#include "pins.h"
#include "timer.h"

constexpr uint32_t BAUD_RATE = 115200;

volatile bool stateChanged = false; 
volatile bool fanState = false;


void setup()
{
  Serial.begin(BAUD_RATE);
  setPins();
  setupTimer();
  setWDT();
}


void loop()
{
  if (stateChanged)
  {
    stateChanged = false;
    fanState = !fanState;
    restartTimer();
    changeStatesFanLed();

    // log
    Serial.println(fanState ? "Fan ON" : "Fan OFF");
  }
  
  esp_task_wdt_reset();
}
