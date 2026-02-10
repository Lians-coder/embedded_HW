
constexpr uint8_t PIXEL_COUNT = 1;
constexpr uint8_t PIXEL_PIN = 48;

constexpr uint16_t SLOW_BLINK_T = 500;
constexpr uint16_t MEDIUM_BLINK_T = 150;
constexpr uint16_t FAST_BLINK_T = 50;
constexpr uint8_t changeStateBlinkTimes = 5;

Adafruit_NeoPixel pixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
uint32_t WHITE   = pixel.Color(255, 255, 255);
uint32_t YELLOW  = pixel.Color(255, 255, 0);
uint32_t RED     = pixel.Color(255, 0, 0);
uint32_t GREEN   = pixel.Color(0, 255, 0);
uint32_t BLUE    = pixel.Color(0, 0, 255);
uint32_t PURPLE  = pixel.Color(255, 0, 255);
uint32_t CYAN    = pixel.Color(0, 255, 255);
uint32_t ORANGE  = pixel.Color(255, 128, 0);

class BlinkMode
{
  public:
    uint16_t period;
    uint32_t color;
    uint32_t lastToggle = 0;
    bool isOn = false;
    uint8_t count = 0;
    uint8_t maxBlink;
    explicit BlinkMode(uint16_t p, uint32_t c, uint8_t mb = 0) 
      : period(p), color(c), maxBlink(mb) {}

    bool stable() const { return period == 0; }

    bool blinker(uint32_t now)
    {
      if (stable())
      {
        pixel.setPixelColor((PIXEL_COUNT - 1), color);
        pixel.show();
        return false;
      }
      else
      {
        if (maxBlink && count >= maxBlink) return true;

        if (now - lastToggle >= period)
        {
          lastToggle = now;
          isOn = !isOn;

          if (isOn) { pixel.setPixelColor((PIXEL_COUNT - 1), color); }
          else 
          { 
            pixel.clear();
            if (maxBlink) count++;
          }
          pixel.show();
        }

        return false;
      }
    }

    void reset()
    {
      count = 0;
      isOn = false;
      lastToggle = 0;
    }
};

BlinkMode needCalib(SLOW_BLINK_T, WHITE);
BlinkMode needMin(0, CYAN);
BlinkMode needMax(0, ORANGE);
BlinkMode successCalib(FAST_BLINK_T, GREEN, changeStateBlinkTimes);
BlinkMode errAbove(SLOW_BLINK_T, RED);
BlinkMode errBelow(SLOW_BLINK_T, BLUE);
BlinkMode errUnknown(FAST_BLINK_T, PURPLE);
BlinkMode resetCompleted(FAST_BLINK_T, CYAN, changeStateBlinkTimes);
BlinkMode forceCalib(FAST_BLINK_T, BLUE, changeStateBlinkTimes);

void enterState(St next)
{
  needCalib.reset();
  needMin.reset();
  needMax.reset();
  successCalib.reset();
  errAbove.reset();
  errBelow.reset();
  errUnknown.reset();
  resetCompleted.reset();
  forceCalib.reset();
  currentState = next;
}

uint32_t colorWheel(uint8_t pos)
{
  pos = 255 - pos;
  if (pos < 85)
  {
    return pixel.Color(0, pos * 3, 255 - pos * 3);  // B -> G
  }
  else if (pos < 170)
  {
    pos -=85;
    return pixel.Color(pos * 3, 255 - pos * 3, 0);  // G -> R
  }
  else
  {
    pos -= 170;
    return pixel.Color(255 - pos * 3, 0, pos * 3);  // R -> B 
  }
}
