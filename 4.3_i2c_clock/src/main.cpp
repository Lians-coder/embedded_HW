#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "i2c.hpp"
#include "rtc.hpp"
#include "display.hpp"
#include "temp.hpp"

constexpr uint16_t UPDATE_PERIOD = 200;

Display oled;
Rtc rtc;
Temp temp;

extern "C" void app_main(void)
{
  i2cInit(ADDR_RTC, ADDR_OLED);
  oled.init();
  temp.init();
  rtc.set();

  while(1)
  {
    tm outTime;
    rtc.read(outTime);

    TickType_t now = xTaskGetTickCount();
    oled.drawAll(outTime, temp.getTemp(), now);
    oled.update();

    vTaskDelay(pdMS_TO_TICKS(UPDATE_PERIOD));
  }
}
