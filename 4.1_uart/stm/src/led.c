#include "led.h"

void toggleLed()
{
  HAL_GPIO_TogglePin(Led_GPIO_Port, Led_Pin);
}
