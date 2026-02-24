#include "freertos/FreeRTOS.h"
#include"freertos/task.h"
#include "driver/gpio.h"


static constexpr gpio_num_t BTN_PIN = GPIO_NUM_5;
static constexpr uint64_t PERIOD = 10;
uint32_t counter = 0;


class Btn
{
  private:
    gpio_num_t pin;
    volatile bool pressed{false};

    static void IRAM_ATTR isr(void* arg) 
    {
      static_cast<Btn*>(arg)->pressed = true;
    };

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
    
    bool handler()
    {
      if (!pressed) return false;
      if (pressed && !gpio_get_level(pin))
      {
        pressed = false;
        return true;
      }
      return false;      
    }
};


extern "C" void app_main()
{
  gpio_install_isr_service(0);
  Btn btn(BTN_PIN);
  btn.init();

  while(true)
  {
    if (btn.handler())
    {
      counter++;
      printf("Times pressed: %lu\n", counter);
    }

    vTaskDelay(pdMS_TO_TICKS(PERIOD));
  }  
}
