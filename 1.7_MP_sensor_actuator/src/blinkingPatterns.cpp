#include "blinkingPatterns.h"

BlinkMode::blinker(uint32_t now)
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