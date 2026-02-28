#include <Arduino.h>
#include "adc.h"

esp_adc_cal_characteristics_t adc_chars;


void setupADC()
{
  pinMode(PIN_ADC, INPUT);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, V_REF, &adc_chars);
}


float getVoltage()
{
  uint16_t raw = analogRead(PIN_ADC);
  uint32_t voltage = esp_adc_cal_raw_to_voltage((uint32_t)raw, &adc_chars);
  float filtered = smaFiltered(voltage);
  return filtered;
}


float smaFiltered(uint32_t sample)
{
  static uint32_t buffer[SAMPLE_SIZE] = {0};
  static uint8_t index = 0;
  static uint32_t sum;
  static uint8_t count = 0;

  sum -= buffer[index];
  buffer[index] = sample;
  sum += sample;

  index = (index + 1) % SAMPLE_SIZE;

  if (count < SAMPLE_SIZE)
  {
    count++;
    return ((float)sum / count);
  }

  return ((float)sum / SAMPLE_SIZE);
}
