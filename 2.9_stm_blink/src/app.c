#include "main.h"
#include "app.h"

uint32_t blinkPeriod = 500;  // ms
uint32_t lastToggle = 0;
GPIO_PinState ledState = GPIO_PIN_RESET;

void setup()
{
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, ledState);
}

void loop()
{
  uint32_t now = HAL_GetTick();
  blink(now);
}

void blink(uint32_t now)
{
  if (now - lastToggle >= blinkPeriod)
  {
    lastToggle = now;
    ledState = (!ledState) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, ledState);
  }
}