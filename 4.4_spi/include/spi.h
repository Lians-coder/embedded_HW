#ifndef SPI_H
#define SPI_H

#include "driver/gpio.h"
#include "driver/spi_master.h"

constexpr gpio_num_t SPI_SCLK = GPIO_NUM_12;
constexpr gpio_num_t SPI_MOSI = GPIO_NUM_11;
constexpr gpio_num_t SPI_MISO = GPIO_NUM_13;
constexpr gpio_num_t SPI_CS   = GPIO_NUM_10;
constexpr int SPI_CLOCK_HZ = 1000000u;
constexpr spi_host_device_t SPI_HOST = SPI2_HOST;


extern spi_device_handle_t spiDevHandle;

void spiInit();

#endif  // SPI_H