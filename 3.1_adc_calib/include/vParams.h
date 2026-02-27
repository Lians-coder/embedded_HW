#ifndef V_PARAMS_H
#define V_PARAMS_H

#include <stdint.h>

struct VoltageParams
{
  uint16_t raw;
  float vManual;
  uint32_t vCalib;
  float err;
};

extern VoltageParams vParams;

void setVoltageParams();

#endif  // V_PARAMS_H
