#ifndef I2C_H
#define I2C_H

#include "driver/gpio.h"
#include "driver/i2c_master.h"

constexpr gpio_num_t I2C_SCL = GPIO_NUM_8;
constexpr gpio_num_t I2C_SDA = GPIO_NUM_9;
constexpr i2c_port_num_t I2C_PORT = I2C_NUM_0;

constexpr uint32_t I2C_TIMEOUT_MS = 100;

extern i2c_master_bus_handle_t i2cBus;
extern i2c_master_dev_handle_t i2cDevRtc;
extern i2c_master_dev_handle_t i2cDevOled;

void i2cInit(uint8_t i2cAddrRtc, uint8_t i2cAddrOled);

uint8_t bcd2dec(uint8_t bcd);
uint8_t dec2bcd(uint8_t dec);

#endif  // I2C_H