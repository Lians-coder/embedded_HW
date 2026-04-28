#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "rtc.hpp"
#include "i2c.h"


esp_err_t Rtc::read(tm &t)
{
  uint8_t reg = 0x00;
  uint8_t rawData[7];

  i2c_master_transmit_receive(i2cDevRtc, &reg, 1, rawData, 7, I2C_TIMEOUT_MS);

  t.tm_sec  = bcd2dec(rawData[0] & 0x7F);
  t.tm_min  = bcd2dec(rawData[1]);
  t.tm_hour = bcd2dec(rawData[2] & 0x3F);
  t.tm_wday = bcd2dec(rawData[3]) - 1;
  t.tm_mday = bcd2dec(rawData[4]);
  t.tm_mon  = bcd2dec(rawData[5]) - 1;
  t.tm_year = bcd2dec(rawData[6]) + 100;

  return ESP_OK;
}


esp_err_t Rtc::set(const tm &t)
{
  uint8_t data[8];

  data[0] = 0x00;
  data[1] = dec2bcd(t.tm_sec);
  data[2] = dec2bcd(t.tm_min);
  data[3] = dec2bcd(t.tm_hour);
  data[4] = dec2bcd(t.tm_wday + 1);
  data[5] = dec2bcd(t.tm_mday);
  data[6] = dec2bcd(t.tm_mon);
  data[7] = dec2bcd(t.tm_year % 100);

  i2c_master_transmit(i2cDevRtc, data, 8, I2C_TIMEOUT_MS);
  
  return ESP_OK;
}