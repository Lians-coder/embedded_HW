#ifndef SMA_H
#define SMA_H

#include <Arduino.h>

constexpr uint8_t SAMPLE_SIZE = 10;

float smaFiltered(uint32_t sample);

#endif  // SMA_H
