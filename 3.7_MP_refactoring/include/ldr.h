#ifndef LDR_H
#define LDR_H

#include <esp_adc/adc_oneshot.h>

constexpr uint8_t FILTER_SIZE = 4;

constexpr adc_channel_t ADC_CHANNEL = ADC_CHANNEL_8;  // GPIO 9
constexpr adc_unit_t ADC_UNIT = ADC_UNIT_1;
constexpr adc_atten_t ADC_ATTEN = ADC_ATTEN_DB_12;
constexpr adc_bitwidth_t ADC_BITWIDTH = ADC_BITWIDTH_12;

extern adc_oneshot_unit_handle_t adc_handle;
extern adc_cali_handle_t cali_handle;

void ldr_init(void);
void readLdr(int &raw, int &mv);
float smaFiltered(uint32_t sample);

#endif  // LDR_H