#include "freertos/FreeRTOS.h"
#include"freertos/task.h"
#include "driver/gpio.h"


static constexpr gpio_num_t BTN_PIN = GPIO_NUM_5;
static constexpr uint64_t POLLING = 10;
static constexpr uint8_t STABLE_TIMES = 5;  // 50 ms debounce
uint32_t counter = 0;


class Btn
{
  private:
    gpio_num_t pin;
    uint8_t stableCount{0};

    enum class BtnSt
    {
      NONE,
      IDLE,
      PRESSED
    };

    BtnSt state = BtnSt::NONE;

    bool pressed()
    {
      return (gpio_get_level(pin) == 0);
    }

  public:
    explicit Btn(gpio_num_t p) : pin(p) {}

    void init()
    {
      gpio_config_t ioConf{};
      ioConf.intr_type = GPIO_INTR_DISABLE;
      ioConf.mode = GPIO_MODE_INPUT;
      ioConf.pull_up_en = GPIO_PULLUP_ENABLE;
      ioConf.pull_down_en = GPIO_PULLDOWN_DISABLE;
      ioConf.pin_bit_mask = (1ULL << pin);
      gpio_config(&ioConf);

      state = gpio_get_level(pin) ? BtnSt::IDLE : BtnSt::PRESSED;
    }

    bool update()
    {
      bool physical = pressed();
      bool logical = (state == BtnSt::PRESSED);

      if (physical != logical)
      {
        if (++stableCount >= STABLE_TIMES)
        {
          state = physical ? BtnSt::PRESSED : BtnSt::IDLE;
          stableCount = 0;
          return physical;
        }
      }
      else
      {
        stableCount = 0;
      }

      return false;
    }
};


extern "C" void app_main()
{
  Btn btn(BTN_PIN);
  btn.init();

  TickType_t lastWakeTime = xTaskGetTickCount();

  while(true)
  {
    if (btn.update())
    {
      counter++;
      printf("Times pressed: %lu\n", counter);
    }

    vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(POLLING));
  }  
}
