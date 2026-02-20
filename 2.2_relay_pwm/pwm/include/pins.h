#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

constexpr uint8_t PIN_POTENTIOMETER = 4;
constexpr uint8_t PIN_MOTOR = 5;

constexpr uint8_t adcResolution = 12;
constexpr adc_attenuation_t adcAttenuation = ADC_11db;

void setupPins();

#endif  // PINS_H
