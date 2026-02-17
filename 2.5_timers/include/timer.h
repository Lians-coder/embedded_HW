#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

constexpr uint32_t WTD_T     = 5;  // 5 s
constexpr uint16_t T_DEVIDER = 80;
constexpr uint64_t PERIOD    = 15000000;  // 15 s
constexpr uint64_t REST_T    = PERIOD * 3 / 4;
constexpr uint64_t WORK_T    = PERIOD / 4;

void setupTimer();
void setWDT();
void restartTimer();

extern volatile bool stateChanged;
extern volatile bool fanState;

#endif  // TIMER_H