#ifndef ADC_H
#define ADC_H

#include <esp32-hal-adc.h>
#include <esp_adc_cal.h>

constexpr uint8_t PIN_ADC = 5;
constexpr uint16_t V_REF = 3300;
extern esp_adc_cal_characteristics_t adc_chars;

void setupAdc();
float getVoltage();

#endif  // ADC_H
