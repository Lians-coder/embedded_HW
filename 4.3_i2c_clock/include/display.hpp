#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <stdint.h>
#include <ctime>
#include <freertos/FreeRTOS.h>

constexpr uint8_t ADDR_OLED = 0x3C;
constexpr uint8_t DISPLAY_HEIGHT = 64;
constexpr uint8_t DISPLAY_WIDTH  = 128;
constexpr uint8_t PAGES = 8;
constexpr uint16_t BUFFER_OLED = DISPLAY_WIDTH * DISPLAY_HEIGHT / PAGES;
constexpr uint8_t BUFFER_TO_SEND = 32;
constexpr uint32_t BLINK_PERIOD = 500;

constexpr const char* DAYS[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

namespace OledCmds
{
  struct CmdPair
  {
    uint8_t cmd;
    uint8_t arg;
  };

  constexpr uint8_t OLED_CTRL_CMD                   {0x00};      // Co=0, D/C=0 → command
  constexpr uint8_t OLED_CTRL_DATA                  {0x40};      // Co=0, D/C=1 → data
  constexpr uint8_t DISPLAY_OFF                     {0xAE};
  constexpr CmdPair DISPLAY_CLOCK_DIV_RATIO         {0xD5, 0x80};
  constexpr CmdPair MULTIPLEX_RATIO                 {0xA8, 0x3F};
  constexpr CmdPair DISPLAY_OFFSET                  {0xD3, 0x00}; 
  constexpr CmdPair ENABLE_CHARGE_PUMP              {0x8D, 0x14};
  constexpr CmdPair MEMORY_ADDRESSING_MODE          {0x20, 0x00}; // (horizontal)
  constexpr uint8_t COM_OUTPUT_SCAN_DIRECTION       {0xA1}; 
  constexpr uint8_t COM_PINS_HARDWARE_CONFIGURATION {0xC8}; 
  constexpr CmdPair COM_OUTPUT_SCAN_DIRECTION_2     {0xDA, 0x12}; 
  constexpr CmdPair CONTRAST_CONTROL                {0x81, 0xCF};
  constexpr CmdPair PRECHARGE_PERIOD                {0xD9, 0xF1};
  constexpr CmdPair VCOMH_DESELECT_LEVEL            {0xDB, 0x40}; 
  constexpr uint8_t ENTIRE_DISPLAY_ON               {0xA4};
  constexpr uint8_t NORMAL_DISPLAY                  {0xA6};       // (not inverted)
  constexpr uint8_t DISPLAY_ON                      {0xAF};
  constexpr uint8_t PAGE_START_ADDRESS              {0xB0};
  constexpr uint8_t SET_COL_LOW                     {0x00};       // lower 4 bits
  constexpr uint8_t SET_COL_HIGH                    {0x10};       // upper 4 bits
}


class Display
{
  public:
    void init();
    void sendData(uint8_t *data, size_t len);
    void drawAll(tm dt, float t, TickType_t now);
    void update();

  private:
    void sendCmds(uint8_t cmd);
    void sendCmds(const OledCmds::CmdPair &c);

    void drawPixel(int x, int y);
    void clear();
    void drawChar(int x, int y, char c);
    void drawString(int y, const char* str, int x = 0);

    uint8_t buffer[BUFFER_OLED];
    uint8_t height{DISPLAY_HEIGHT};
    uint8_t width{DISPLAY_WIDTH};
};

#endif  // DISPLAY_HPP
