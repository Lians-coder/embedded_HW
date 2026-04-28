#ifndef BME_HPP
#define BME_HPP

#include "BME280.hpp"

extern BME280::SPIBus spiBusBme;
extern BME280::BME280 bmeSensor;

extern double bmeTemp;
extern double bmePress;
extern double bmeHum;

void bmeConfig();
void bmeReadData();

#endif  // BME_HPP
