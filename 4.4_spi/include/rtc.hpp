#ifndef  RTC_HPP
#define RTC_HPP

#include <ctime>
#include <esp_err.h>
#include <driver/i2c_master.h>

constexpr uint8_t ADDR_RTC  = 0x68;

// Fri 30-04-2026 23:59:30
constexpr tm DATETIME_TO_SET = {
  .tm_sec = 30,
  .tm_min = 59,
  .tm_hour = 23,
  .tm_mday = 30,
  .tm_mon = 4,
  .tm_year = 26,  // years since 1900
  .tm_wday = 5,   // days since Sunday (0-6) 
  .tm_yday = 0,   // irrelevant
  .tm_isdst = 0,  // irrelevant
};


class Rtc
{
  public:
    esp_err_t set(const tm &inTime = DATETIME_TO_SET);
    esp_err_t read(tm &outTime);
};

extern Rtc rtc;

#endif  // RTC_HPP