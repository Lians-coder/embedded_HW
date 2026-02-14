#include <Arduino.h>

static constexpr uint8_t BTN_PIN = 5;
static constexpr uint32_t DEBOUNCE_T = 50;
uint16_t counter = 0;

class Btn
{
  public:
    uint8_t pin;
    explicit Btn(uint8_t p) : pin(p) {}
    volatile bool pressed = false;
    volatile uint32_t lastPressed = 0;

    static IRAM_ATTR void isr(void* arg) 
    {
      Btn* self = static_cast<Btn*>(arg);
      self->pressed = true;
    };

    void init()
    {
      pinMode(pin, INPUT);
      attachInterruptArg(digitalPinToInterrupt(pin), isr, this, FALLING);
    }

    bool handler(uint32_t now)
    {
      if (!pressed) return false;
      
      pressed = false;

      if (now - lastPressed < DEBOUNCE_T) return false;
      
      lastPressed = now;
      return true;
    }
};


Btn btn(BTN_PIN);

void setup()
{
  Serial.begin(115200);
  btn.init();
}

void loop()
{
  uint32_t now = millis();
  if (btn.handler(now))
  {
    counter++;
    Serial.printf("Times pressed: %lu\n", counter);
  }
}
