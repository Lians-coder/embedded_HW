#include <Arduino.h>
#include "traffic.h"

Led red(LED_RED_PIN);
Led yellow(LED_YELLOW_PIN);
Led green(LED_GREEN_PIN);
Btn btn(BTN_PIN);

Traffic traffic(red, yellow, green, btn);

void setup()
{
  traffic.init();
}

void loop()
{
  traffic.update(millis());
}
