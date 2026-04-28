#include <cstring>
#include "i2c.h"
#include "display.hpp"
#include "font.h"


void Display::sendCmds(uint8_t cmd)
{
  uint8_t bufSize = 2;
  uint8_t buf[bufSize] = {OledCmds::OLED_CTRL_CMD, cmd};
  i2c_master_transmit(i2cDevOled, buf, sizeof(buf), I2C_TIMEOUT_MS);
}


void Display::sendCmds(const OledCmds::CmdPair &c)
{
  uint8_t bufSize = 3;
  uint8_t buf[bufSize] = {OledCmds::OLED_CTRL_CMD, c.cmd, c.arg};
  i2c_master_transmit(i2cDevOled, buf, sizeof(buf), I2C_TIMEOUT_MS);
}


void Display::init()
{
  using namespace OledCmds;

  sendCmds(DISPLAY_OFF);
  sendCmds(DISPLAY_CLOCK_DIV_RATIO);
  sendCmds(MULTIPLEX_RATIO);
  sendCmds(DISPLAY_OFFSET);
  sendCmds(OLED_CTRL_DATA);
  sendCmds(ENABLE_CHARGE_PUMP);
  sendCmds(MEMORY_ADDRESSING_MODE);
  sendCmds(COM_OUTPUT_SCAN_DIRECTION);
  sendCmds(COM_PINS_HARDWARE_CONFIGURATION);
  sendCmds(COM_OUTPUT_SCAN_DIRECTION_2);
  sendCmds(CONTRAST_CONTROL);
  sendCmds(PRECHARGE_PERIOD);
  sendCmds(VCOMH_DESELECT_LEVEL);
  sendCmds(ENTIRE_DISPLAY_ON);
  sendCmds(NORMAL_DISPLAY);
  sendCmds(DISPLAY_ON);

  memset(buffer, 0, sizeof(buffer));
}


void Display::sendData(uint8_t *data, size_t len)
{
  uint8_t buf[width + 1];
  buf[0] = OledCmds::OLED_CTRL_DATA;
  memcpy(&buf[1], data, len);
  i2c_master_transmit(i2cDevOled, buf, len + 1, I2C_TIMEOUT_MS);
}


void Display::update()
{
  for (int page = 0; page < PAGES; page++)
  {
    sendCmds(OledCmds::PAGE_START_ADDRESS + page);
    sendCmds(OledCmds::SET_COL_LOW);
    sendCmds(OledCmds::SET_COL_HIGH);
    sendData(&buffer[page * width], width);
  }
}


void Display::clear()
{
  memset(buffer, 0, sizeof(buffer));
}


void Display::drawPixel(int x, int y)
{
  if (x < 0 || x >= width || y < 0 || y >= height)
  {
    return;
  }
  uint16_t index = x + (y / 8) * width;
  buffer[index] |= (1 << (y % 8));
}


void Display::drawChar(int x, int y, char c)
{
  const uint8_t* glyph = getGlyph(c);
  if (!glyph) return;

  for (int i = 0; i < FONT_WIDTH; i++)
  {
    uint8_t col = glyph[i];

    for (int j = 0; j < FONT_HEIGHT; j++)
    {
      if (col & (1 << j))
      {
        drawPixel(x + i, y + j);
      }
    }
  }
}


void Display::drawString(int y, const char* str, int x)
{
  while (*str)
  {
    drawChar(x, y, *str);
    x += FONT_WIDTH + 1;
    str++;
  }
}


void Display::drawAll(
  tm dt, float t, TickType_t now, 
  double bmeTemp, double bmePress, double bmeHum
)
{
  clear();

  char buf[BUFFER_TO_SEND];

  // date
  snprintf
  (
    buf, sizeof(buf),
    "%s %02d.%02d.20%02d",
    DAYS[dt.tm_wday % 7],
    dt.tm_mday, dt.tm_mon + 1, dt.tm_year % 100
  );
  drawString(0, buf);

  // time
  uint32_t nowMS = now * portTICK_PERIOD_MS;
  // bool blink = (dt.tm_sec % 2) == 0;
  bool blink = (nowMS / BLINK_PERIOD) % 2;
  if (blink)
  {
    snprintf
    (
      buf, sizeof(buf), 
      "%02d %02d %02d", 
      dt.tm_hour, dt.tm_min, dt.tm_sec
    );
  }
  else
  {
    snprintf
    (
      buf, sizeof(buf), 
      "%02d:%02d:%02d", 
      dt.tm_hour, dt.tm_min, dt.tm_sec
    );
  }
  drawString(FONT_HEIGHT + 1, buf);

  // temp
  if (t > 0)
  {
    snprintf(buf, sizeof(buf), "+%02fdC", t);
  }
  else
  {
    snprintf(buf, sizeof(buf), "%02fdC", t);
  }
  drawString((FONT_HEIGHT + 1) * 2, buf);

  // from BME
  // temp
  if (bmeTemp > 0)
  {
    snprintf(buf, sizeof(buf), "+%02lfdC", bmeTemp);
  }
  else
  {
    snprintf(buf, sizeof(buf), "%02lfdC", bmeTemp);
  }
  drawString((FONT_HEIGHT + 1) * 3, buf);

  // pressure & humidity
  snprintf
  (
    buf, sizeof(buf),
    "%02lf hPa    %02lf %%RH",
    bmePress, bmeHum
  );
  drawString((FONT_HEIGHT + 1) * 4, buf);
}

