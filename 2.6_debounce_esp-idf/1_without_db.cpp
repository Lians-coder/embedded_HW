#include <atomic>
#include "freertos/FreeRTOS.h"
#include"freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

static constexpr uint64_t PERIOD = 10;
static constexpr gpio_num_t BTN_PIN = GPIO_NUM_5;

class Btn
{
  private:
    gpio_num_t pin;
    std::atomic<uint32_t> counter{0};
  
    static void IRAM_ATTR isr(void* arg)
    {
      static_cast<Btn*>(arg)->counter.fetch_add(1, std::memory_order_relaxed);
    }
    
  public:
    explicit Btn(gpio_num_t p) : pin(p) {}

    void init()
    {
      gpio_config_t ioConf{};
      ioConf.intr_type = GPIO_INTR_NEGEDGE;
      ioConf.mode = GPIO_MODE_INPUT;
      ioConf.pin_bit_mask = (1ULL << pin);

      gpio_config(&ioConf);
      gpio_isr_handler_add(pin, &Btn::isr, this);
    }

    uint32_t getCount() const
    {
      return counter.load(std::memory_order_relaxed);
    }
};


extern "C" void app_main(void)
{
  gpio_install_isr_service(0);

  Btn btn(BTN_PIN);
  btn.init();

  uint32_t lastCount = 0;

  while(true)
  {
    uint32_t current = btn.getCount();
    if (current != lastCount)
    {
      printf("Times pressed: %lu\n", current);
      lastCount = current;  
    }

    vTaskDelay(pdMS_TO_TICKS(PERIOD));
  }
}
