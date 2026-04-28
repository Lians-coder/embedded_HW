#include "spi.h"
#include "bme.hpp"

BME280::SPIBus spiBusBme(SPI_HOST, SPI_CS, SPI_CLOCK_HZ);
BME280::BME280 bmeSensor(spiBusBme);

double bmeTemp = 0;
double bmePress = 0;
double bmeHum = 0;

void bmeConfig()
{
  bmeSensor.setOversmplingTemp(BME280::Oversampling::OVERSAMPLING_16X);
  bmeSensor.setOversmplingPress(BME280::Oversampling::OVERSAMPLING_16X);
  bmeSensor.setOversmplingHum(BME280::Oversampling::OVERSAMPLING_16X);
  bmeSensor.setFilter(BME280::Filter::FILTER_16);
  bmeSensor.setMode(BME280::Mode::FORCED_MODE);
}


void bmeReadData()
{
  bmeTemp  = bmeSensor.compensationTempDouble();
  bmePress = bmeSensor.compensationPressDouble() / 100.0;
  bmeHum   = bmeSensor.compensationHumDouble();
}
