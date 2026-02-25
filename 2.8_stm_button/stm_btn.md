# 2.8 STM32 Button & LED

## Schematic

[KiCad schematic](https://github.com/Lians-coder/embedded_HW/blob/main/2.8_stm_button/stm_btn_led.kicad_sch) for this project.  

## Code

User code in **main.c**:  

```c
uint8_t buttonState = 0;
uint32_t lastDebounceTime = 0;
uint8_t lastReading = GPIO_PIN_SET;

while (1)
{
uint8_t currentReading = HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin);

if (currentReading != lastReading)
{
    lastDebounceTime = HAL_GetTick();
}

if ((HAL_GetTick() - lastDebounceTime) > DEBOUNCE_TIME)
{
    if (currentReading == GPIO_PIN_RESET && !buttonState)
    {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    buttonState = 1;
    }
    else if (currentReading == GPIO_PIN_SET)
    {
    buttonState = 0;
    }
}

lastReading = currentReading;
}
```

In **main.h**:  

```c
#define BTN_Pin GPIO_PIN_1
#define BTN_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOB

#define DEBOUNCE_TIME 50
```

## Result

[Video](https://drive.google.com/file/d/15Wk57wDObTHIgnoHFOPN0ocWnztxDr-f/view?usp=sharing) demonstrating working process.  
