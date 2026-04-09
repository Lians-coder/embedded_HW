// #include "esp_err.h"
#include "i2c.hpp"

i2c_master_bus_handle_t bus;
i2c_master_dev_handle_t devRtc;
i2c_master_dev_handle_t devOled;


uint8_t bcd2dec(uint8_t bcd)
{
  return ((bcd >> 4) * 10) + (bcd & 0x0F);
}


uint8_t dec2bcd(uint8_t dec)
{
  return ((dec / 10) << 4) | (dec % 10);
}


void i2cInit(uint8_t addrRtc, uint8_t addrOled)
{
  i2c_master_bus_config_t busCfg = {
    .i2c_port = I2C_PORT,
    .sda_io_num = PIN_SDA,
    .scl_io_num = PIN_SCL,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .intr_priority = 0,
    .trans_queue_depth = 0,
    .flags = {},
  };
  i2c_new_master_bus(&busCfg, &bus);

  i2c_device_config_t devCfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .scl_speed_hz = 100000,
    .scl_wait_us = 0,
    .flags = {}
  };

  devCfg.device_address = addrRtc;
  i2c_master_bus_add_device(bus, &devCfg, &devRtc);

  devCfg.device_address = addrOled;
  i2c_master_bus_add_device(bus, &devCfg, &devOled);
}