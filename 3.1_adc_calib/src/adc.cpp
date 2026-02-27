#include <Arduino.h>
#include "adc.h"
#include "vParams.h"

esp_adc_cal_characteristics_t adc_chars;
VoltageParams vParams;

void setupAdc()
{
  pinMode(PIN_ADC, INPUT);
  analogReadResolution(ADC_RESOLUTION);
  analogSetAttenuation(ADC_ATTENUATION);

  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, V_REF, &adc_chars);
}

void setVoltageParams()
{
  vParams.raw = analogRead(PIN_ADC);
  vParams.vManual = vParams.raw * V_REF / maxADC;
  vParams.vCalib = esp_adc_cal_raw_to_voltage((uint32_t)vParams.raw, &adc_chars);
  
  if (vParams.vCalib != 0)
  {
    vParams.err = (vParams.vManual - (float)vParams.vCalib) * 100.0f / (float)vParams.vCalib;
  }
  else
  {
    vParams.err = 0;
  }
}
