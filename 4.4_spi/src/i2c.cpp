// #include "esp_err.h"
#include "i2c.h"

i2c_master_bus_handle_t i2cBus;
i2c_master_dev_handle_t i2cDevRtc;
i2c_master_dev_handle_t i2cDevOled;


uint8_t bcd2dec(uint8_t bcd)
{
  return ((bcd >> 4) * 10) + (bcd & 0x0F);
}


uint8_t dec2bcd(uint8_t dec)
{
  return ((dec / 10) << 4) | (dec % 10);
}


void i2cInit(uint8_t i2cAddrRtc, uint8_t i2cAddrOled)
{
  i2c_master_bus_config_t i2cBusCfg = 
  {
    .i2c_port = I2C_PORT,
    .sda_io_num = I2C_SDA,
    .scl_io_num = I2C_SCL,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .intr_priority = 0,
    .trans_queue_depth = 0,
    .flags = {},
  };
  i2c_new_master_bus(&i2cBusCfg, &i2cBus);

  i2c_device_config_t i2cDevCfg = 
  {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .scl_speed_hz = 100000,
    .scl_wait_us = 0,
    .flags = {}
  };

  i2cDevCfg.device_address = i2cAddrRtc;
  i2c_master_bus_add_device(i2cBus, &i2cDevCfg, &i2cDevRtc);

  i2cDevCfg.device_address = i2cAddrOled;
  i2c_master_bus_add_device(i2cBus, &i2cDevCfg, &i2cDevOled);
}