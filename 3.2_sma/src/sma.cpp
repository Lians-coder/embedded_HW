#include "sma.h"

float smaFiltered(uint32_t sample)
{
  static uint32_t buffer[SAMPLE_SIZE] = {0};
  static uint8_t index = 0;
  static uint32_t sum;
  static uint8_t count = 0;

  sum -= buffer[index];
  buffer[index] = sample;
  sum += sample;

  index = (index + 1) % SAMPLE_SIZE;

  if (count < SAMPLE_SIZE)
  {
    count++;
    return ((float)sum / count);
  }

  return ((float)sum / SAMPLE_SIZE);
}
