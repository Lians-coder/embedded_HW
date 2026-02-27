#ifndef LOG_H
#define LOG_H

#include <stdint.h>

constexpr uint8_t TRIAL_COUNT = 20;
extern uint8_t trialCount;

void printHeaders();
void printVoltageLog();

#endif  // LOG_H
