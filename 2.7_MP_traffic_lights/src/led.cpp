#include "led.h"


Led::Led(pin_t p) : pin(p) {}

void Led::init()
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}


bool Led::stable(uint32_t now, uint32_t period)
{
  if (!lastToggle)
  {
    reset();
    lastToggle = now;
  }

  digitalWrite(pin, HIGH);

  if (now - lastToggle > period)
  {
    return true;
  }
  return false;
}


bool Led::blink(uint32_t now, uint32_t totalPeriod, uint32_t blinkPeriod, bool infinity)
{
  if (!lastToggle)
  {
    lastToggle = now;
  }
  if (!infinity && (now - lastToggle > totalPeriod))
  {
    reset();
    return true;
  }

  if (!lastBlink)
  {
    lastBlink = now;
    isOn = true;
    digitalWrite(pin, HIGH);
  }
  if (now - lastBlink > blinkPeriod)
  {
    lastBlink = now;
    isOn = !isOn;
    digitalWrite(pin, isOn ? HIGH : LOW);
  }

  return false;
}


void Led::reset()
{
  digitalWrite(pin, LOW);
  isOn = false;
  lastToggle = 0;
  lastBlink = 0;
}
