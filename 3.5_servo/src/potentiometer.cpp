#include "potentiometer.h"


Potentiometer::Potentiometer(uint8_t p) : pin(p) {}


void Potentiometer::init()
{
  pinMode(pin, INPUT);
  analogReadResolution(ADC_RESOLUTION);
}


void Potentiometer::update()
{
  uint16_t value = analogRead(pin);

  if (value < minVal)
  {
    minVal = value;
  }
  if (value > maxVal)
  {
    maxVal = value;
  }

  if (filtered == 0)
  {
    filtered = value;
  }
  
  filtered = filtered * 0.6f + value * 0.4f;
}


float Potentiometer::getAngle()
{
  if (maxVal - minVal < 10)
  {
    return 0;
  }

  float angle =  (float(filtered) - float(minVal)) * 180.0f / float(maxVal - minVal);
  return constrain(angle, 0.0f, 180.0f);
}
