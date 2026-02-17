#include <Arduino.h>
#include "esp_task_wdt.h"
#include "timer.h"


hw_timer_t *timer = nullptr;

void IRAM_ATTR onTimer()
{
  stateChanged = true;
}


void setupTimer()
{
  if (timer != nullptr)
  {
     return;
  }
  timer = timerBegin(0, T_DEVIDER, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, REST_T, false);
  timerAlarmEnable(timer);
}


void setWDT()
{
  esp_task_wdt_init(WTD_T, true);
  esp_task_wdt_add(NULL);  
}


void restartTimer()
{
  timerWrite(timer, 0);
  uint64_t next = fanState ? WORK_T : REST_T;
  timerAlarmWrite(timer, next, false);
  timerAlarmEnable(timer);
}