#include "button.h"

uint8_t buttonState = 0;
uint32_t lastDebounceTime = 0;
uint8_t lastReading = GPIO_PIN_SET;


void btnUpdate()
{
  uint8_t currentReading = HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin);

  if (currentReading != lastReading)
  {
    lastDebounceTime = HAL_GetTick();
  }

  if ((HAL_GetTick() - lastDebounceTime) > DEBOUNCE_TIME)
  {
    if (currentReading == GPIO_PIN_RESET && !buttonState)
    {
      buttonState = 1;
    }
    else if (currentReading == GPIO_PIN_SET)
    {
      buttonState = 0;
    }
  }

  lastReading = currentReading;
}