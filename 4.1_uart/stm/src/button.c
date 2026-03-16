#include "button.h"


ButtonContext btnCtx = 
{
  .state = BTN_IDLE,
  .lastDebounceTime = 0,
  .wasPressed = false
};


void btnUpdate(uint32_t now)
{
bool isDown = (HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin) == GPIO_PIN_RESET);

  switch (btnCtx.state)
  {
    case BTN_IDLE:
    {
      if (isDown)
      {
        btnCtx.lastDebounceTime = now;
        btnCtx.state = DEBOUNCING;
      }
      break;          
    }

    case DEBOUNCING:
      if (now - btnCtx.lastDebounceTime >= DEBOUNCE_TIME)
      {
        if (isDown)
        {
          btnCtx.wasPressed = true;
          btnCtx.state = PRESSED;
        }
        else 
        {
          btnCtx.state = BTN_IDLE; 
        }
      }
      break;

    case PRESSED:
      if (!isDown)
      {
        btnCtx.state = BTN_IDLE;
      }
      break;
  }
}


bool btnPressed()
{
  if (btnCtx.wasPressed)
  {
    btnCtx.wasPressed = false;
    return true;
  }
  return false;
}