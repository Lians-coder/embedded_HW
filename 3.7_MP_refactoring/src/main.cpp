#include <freertos/FreeRTOS.h>
#include "servo.h"
#include "ldr.h"

Servo servo;

extern "C" void app_main(void)
{
  ldr_init();
  servo.init();
  servo.test();

  int raw;
  int mv;

  while(1)
  {
    readLdr(raw, mv);
    servo.servoSetAngleFromMv((uint16_t)mv);
    vTaskDelay(pdMS_TO_TICKS(SUPERLOOP_DELAY));
  }
}
