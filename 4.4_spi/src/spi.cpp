#include "spi.h"

spi_device_handle_t spiDevHandle;

void spiInit()
{
  spi_bus_config_t spiBusCfg =
  {
    .mosi_io_num = SPI_MOSI,
    .miso_io_num = SPI_MISO,
    .sclk_io_num = SPI_SCLK,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1,
    .max_transfer_sz = 16u
  };
  ESP_ERROR_CHECK(spi_bus_initialize(SPI_HOST, &spiBusCfg, SPI_DMA_CH_AUTO));

  // spi_device_interface_config_t spiDevCfg = 
  // {
  //   .command_bits = 0u,
  //   .address_bits = 0u,
  //   .dummy_bits = 0u,
  //   .mode = 0,
  //   .clock_source = SPI_CLK_SRC_DEFAULT,
  //   .duty_cycle_pos = 0,
  //   .cs_ena_pretrans = 1u,
  //   .cs_ena_posttrans = 0u,
  //   .clock_speed_hz = SPI_CLOCK_HZ,
  //   .input_delay_ns = 0u,
  //   .spics_io_num = SPI_CS,
  //   .flags = 0u,
  //   .queue_size = 1u,
  //   .pre_cb = 0,
  //   .post_cb = 0,
  // };
  // ESP_ERROR_CHECK(spi_bus_add_device(SPI_HOST, &spiDevCfg, &spiDevHandle));
}
