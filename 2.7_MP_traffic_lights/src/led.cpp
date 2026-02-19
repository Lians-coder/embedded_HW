#include "led.h"


Led::Led(pin_t p) : pin(p) {}

void Led::init()
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}


bool Led::stable(uint32_t now, uint32_t totalPeriod)
{
  if (!lastToggle)
  {
    reset();
    lastToggle = now;
  }

  digitalWrite(pin, HIGH);

  if (now - lastToggle > totalPeriod)
  {
    return true;
  }
  return false;
}


bool Led::blink(uint32_t now, uint32_t totalPeriod, uint32_t blinkPeriod)
{
  if (!lastToggle)
  {
    lastToggle = now;
  }
  if (now - lastToggle > totalPeriod)
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


void Led::blinkSpecial(uint32_t now, uint32_t blinkPeriod)
{
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
}


void Led::reset()
{
  digitalWrite(pin, LOW);
  isOn = false;
  lastToggle = 0;
  lastBlink = 0;
}
