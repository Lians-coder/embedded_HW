#ifndef TEMP_HPP
#define TEMP_HPP

#include "driver/gpio.h"

constexpr gpio_num_t PIN_TEMP = GPIO_NUM_5;
constexpr uint8_t DALLAS_POLYNOMIAL = 0x8C;

namespace TempCmds
{
  constexpr uint8_t CMD_SKIP_ROM        = 0xCC;
  constexpr uint8_t CMD_CONVERT_T       = 0x44;
  constexpr uint8_t CMD_READ_SCRATCHPAD = 0xBE;  
}

namespace TempTime
{
  constexpr uint16_t RESET_US        = 480;
  constexpr uint16_t PRESENCE_US     = 70;
  constexpr uint16_t RELEASE_US      = RESET_US - PRESENCE_US;
  constexpr uint16_t SLOT_TOTAL      = 70;
  constexpr uint16_t WRITE_1_LOW_US  = 6;
  constexpr uint16_t WRITE_1_HIGH_US = SLOT_TOTAL - WRITE_1_LOW_US;  
  constexpr uint16_t WRITE_0_LOW_US  = 60;
  constexpr uint16_t WRITE_0_HIGH_US = SLOT_TOTAL - WRITE_0_LOW_US;
  constexpr uint16_t READ_INIT_US    = 6;
  constexpr uint16_t READ_SAMPLE_US  = 9;
  constexpr uint16_t READ_SLOT_US    = 55;
}

class Temp
{
  public:
    void init();
    float getTemp();

  private:
    void low();
    void release();
    bool reset();
    uint8_t crc8(const uint8_t* data, uint8_t len); 
    void writeBit(int b);
    int readBit();
    void writeByte(int b);
    int readByte();

    gpio_num_t pin{PIN_TEMP};
    bool busy{false};
    float lastTemp{0};
    
    enum class TempState
    {
      START_CONVERSION,
      WAIT_CONVERSION,
      READ_SCRATCHPAD
    };

    TempState state = TempState::START_CONVERSION;
};

#endif  // TEMP_HPP
