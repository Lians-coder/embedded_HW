#include "esp_rom_sys.h"
#include "temp.hpp"

void Temp::init()
{
  gpio_set_direction(pin, GPIO_MODE_INPUT_OUTPUT_OD);
}


uint8_t Temp::crc8(const uint8_t* data, uint8_t len)
{
  uint8_t crc = 0;

  for (uint8_t i = 0; i < len; i++)
  {
    uint8_t inbyte = data[i];
    for (uint8_t j = 0; j < 8; j++)
    {
      uint8_t mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix)
      {
        crc ^= DALLAS_POLYNOMIAL;
      }
      inbyte >>= 1;
    }
  }

  return crc;
}


float Temp::getTemp()
{
  switch (state)
  {
    case TempState::START_CONVERSION:
    {
      if (!reset()) 
      {
        break;
      }

      writeByte(TempCmds::CMD_SKIP_ROM);
      writeByte(TempCmds::CMD_CONVERT_T);

      state = TempState::WAIT_CONVERSION;
      break;
    }

    case TempState::WAIT_CONVERSION:
    {
      if (readBit() == 0)
      {
        break;  // busy
      }
      state = TempState::READ_SCRATCHPAD;
      break;
    }

    case TempState::READ_SCRATCHPAD:
    {
      uint8_t data[9];

      if (!reset())
      {
        break;
      }

      writeByte(TempCmds::CMD_SKIP_ROM);
      writeByte(TempCmds::CMD_READ_SCRATCHPAD);

      for (int i = 0; i < 9; i++)
      {
        data[i] = readByte();
      }

      if (crc8(data, 9) != 0)
      { 
        break; // discard
      }

      int16_t raw = (data[1] << 8) | data[0];
      lastTemp = raw * 0.0625f;

      state = TempState::START_CONVERSION;
      break;
    }
  }

  return lastTemp;
}


void Temp::low()
{
  gpio_set_direction(pin, GPIO_MODE_OUTPUT_OD);
  gpio_set_level(pin, 0);
}


void Temp::release()
{
  gpio_set_level(pin, 1);
  gpio_set_direction(pin, GPIO_MODE_INPUT_OUTPUT_OD);
}


bool Temp::reset()
{
  low();
  esp_rom_delay_us(TempTime::RESET_US);
  release();
  esp_rom_delay_us(TempTime::PRESENCE_US);
  bool present = !gpio_get_level(pin);
  esp_rom_delay_us(TempTime::RELEASE_US);
  return present;
}


void Temp::writeBit(int b)
{
  low();
  esp_rom_delay_us(b ? TempTime::WRITE_1_LOW_US : TempTime::WRITE_0_LOW_US);
  release();
  esp_rom_delay_us(b ? TempTime::WRITE_1_HIGH_US : TempTime::WRITE_0_HIGH_US);
}


int Temp::readBit()
{
  low();
  esp_rom_delay_us(TempTime::READ_INIT_US);
  release();
  esp_rom_delay_us(TempTime::READ_SAMPLE_US);
  int r = gpio_get_level(pin);
  esp_rom_delay_us(TempTime::READ_SLOT_US);
  return r;
}


void Temp::writeByte(int b)
{
  for (int i = 0; i < 8; i++)
  {
    writeBit((b >> i) & 1);
  }
}


int Temp::readByte()
{
  uint8_t r = 0;
  for (int i = 0; i < 8; i++)
  {
    r |= readBit() << i;
  }
  return r;
}
