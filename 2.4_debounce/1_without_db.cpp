#include <Arduino.h>

static constexpr uint8_t BTN_PIN = 5;
volatile uint16_t counter = 0;
uint32_t lastCount = 0;

class Btn
{
  public:
    uint8_t pin;
    explicit Btn(uint8_t p) : pin(p) {}
    static IRAM_ATTR void isr(void* arg) { counter++; };

    void init()
    {
      pinMode(pin, INPUT);
      attachInterruptArg(pin, isr, this, FALLING);
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
  if (counter != lastCount)
  {
    Serial.printf("Times pressed: %lu\n", counter);
    lastCount = counter;
  }
}
