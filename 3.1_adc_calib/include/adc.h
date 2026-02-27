#ifndef ADC_H
#define ADC_H

#include <esp32-hal-adc.h>
#include <esp_adc_cal.h>

constexpr uint8_t PIN_ADC = 5;

constexpr uint8_t ADC_RESOLUTION = 12;
constexpr uint16_t maxADC = (1 << ADC_RESOLUTION) - 1;
constexpr adc_attenuation_t ADC_ATTENUATION = ADC_11db;
constexpr float V_REF = 3300.0f;

extern esp_adc_cal_characteristics_t adc_chars;

void setupAdc();

#endif  // ADC_H
