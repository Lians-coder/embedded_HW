#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "i2c.h"
#include "display.hpp"
#include "temp.hpp"
#include "spi.h"
#include "rtc.hpp"
#include "bme.hpp"

Display oled;
Temp temp;
Rtc rtc;

constexpr uint32_t UPDATE_PERIOD = 200;
constexpr uint32_t BME_POLL_PERIOD = 10;

extern "C" void app_main(void)
{
  i2cInit(ADDR_RTC, ADDR_OLED);
  oled.init();
  temp.init();  
  spiInit();
  bmeConfig();
  rtc.set();

  while(1)
  {
    tm outTime;
    rtc.read(outTime);

    bmeSensor.setMode(BME280::Mode::FORCED_MODE);
    while(bmeSensor.isMesuring())
    {
      vTaskDelay(pdMS_TO_TICKS(BME_POLL_PERIOD));
    }
    bmeReadData();

    TickType_t now = xTaskGetTickCount();
    oled.drawAll(outTime, temp.getTemp(), now, bmeTemp, bmePress, bmeHum);
    oled.update(); 

    vTaskDelay(pdMS_TO_TICKS(UPDATE_PERIOD));
  }
}
