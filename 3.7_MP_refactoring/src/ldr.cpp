#include <esp_err.h>
#include <esp_log.h>
#include "ldr.h"


static const char *TAG = "LDR";

adc_oneshot_unit_handle_t adc_handle;
adc_cali_handle_t cali_handle;


void ldr_init(void)
{
  adc_oneshot_unit_init_cfg_t unit_config = {
    .unit_id = ADC_UNIT,
    .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
    .ulp_mode = ADC_ULP_MODE_DISABLE
  };
  ESP_ERROR_CHECK(adc_oneshot_new_unit(&unit_config, &adc_handle));

  adc_oneshot_chan_cfg_t channel_config = {
    .atten = ADC_ATTEN,
    .bitwidth = ADC_BITWIDTH,
  };
  ESP_ERROR_CHECK(adc_oneshot_config_channel(
    adc_handle,
    ADC_CHANNEL,
    &channel_config
  ));

  adc_cali_curve_fitting_config_t cfg = {
    .unit_id = ADC_UNIT,
    .chan = ADC_CHANNEL,
    .atten = ADC_ATTEN,
    .bitwidth = ADC_BITWIDTH,
  };
  ESP_ERROR_CHECK(adc_cali_create_scheme_curve_fitting(&cfg, &cali_handle));
}


void readLdr(int &raw, int &mv)
{
  adc_oneshot_read(adc_handle, ADC_CHANNEL, &raw);
  ESP_ERROR_CHECK(
    adc_cali_raw_to_voltage(cali_handle, raw, &mv)
  );
  mv = (int)smaFiltered((uint32_t) mv);
  ESP_LOGI(TAG, "Raw ADC Value: %d\tVoltage Value: %d mV", raw, mv);
}


float smaFiltered(uint32_t sample)
{
  static uint32_t buffer[FILTER_SIZE] = {0};
  static uint8_t index = 0;
  static uint32_t sum = 0;
  static uint8_t count = 0;

  sum -= buffer[index];
  buffer[index] = sample;
  sum += sample;

  index = (index + 1) % FILTER_SIZE;

  if (count < FILTER_SIZE)
  {
    count++;
    return ((float)sum / count);
  }

  return ((float)sum / FILTER_SIZE);
}
