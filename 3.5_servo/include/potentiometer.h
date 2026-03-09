#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

constexpr uint8_t PIN_POTENTIOMETER = 5;
constexpr uint8_t ADC_RESOLUTION = 12;
constexpr uint16_t MAX_ADC = (1 << ADC_RESOLUTION) - 1;

class Potentiometer
{
  private:
    float filtered{0};
    uint16_t minVal{MAX_ADC};
    uint16_t maxVal{0};
    uint8_t pin;
    
  public:
    explicit Potentiometer(uint8_t p);

    void init();
    void update();
    float getAngle();
};

#endif  // POTENTIOMETER_H