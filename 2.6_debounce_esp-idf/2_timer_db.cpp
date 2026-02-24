#include "freertos/FreeRTOS.h"
#include"freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"

static constexpr gpio_num_t BTN_PIN = GPIO_NUM_5;
static constexpr uint64_t PERIOD = 10;
static constexpr uint64_t DEBOUNCE_T = 50;
uint32_t counter = 0;


class Btn
{
  private:
    gpio_num_t pin;
    volatile bool pressed{false};
    uint64_t lastPressed{0};

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
    
    bool handler(uint64_t now)
    {
      if (!pressed) return false;
      
      pressed = false;

      if (now - lastPressed < DEBOUNCE_T) return false;
      
      lastPressed = now;
      return true;
    }
};


extern "C" void app_main()
{
  gpio_install_isr_service(0);
  Btn btn(BTN_PIN);
  btn.init();

  while(true)
  {
    uint64_t now = esp_timer_get_time() / 1000;  // millis
    if (btn.handler(now))
    {
      counter++;
      printf("Times pressed: %lu\n", counter);
    }

    vTaskDelay(pdMS_TO_TICKS(PERIOD));
  }  
}
