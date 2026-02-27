#include <Arduino.h>
#include "adc.h"
#include "sma.h"

esp_adc_cal_characteristics_t adc_chars;

void setupAdc()
{
  pinMode(PIN_ADC, INPUT);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, V_REF, &adc_chars);
}

float getVoltage()
{
  uint32_t raw = analogRead(PIN_ADC);
  uint32_t voltage = esp_adc_cal_raw_to_voltage((uint32_t)raw, &adc_chars);
  float filtered = smaFiltered(voltage);
  return filtered;
}
