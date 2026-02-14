#include <Arduino.h>

static constexpr uint8_t BTN_PIN = 5;
uint16_t counter = 0;

class Btn
{
  public:
    uint8_t pin;
    explicit Btn(uint8_t p) : pin(p) {}
    volatile bool pressed = false;

    static void isr(void* arg) 
    {
      Btn* self = static_cast<Btn*>(arg);
      self->pressed = true;
    };

    void init()
    {
      pinMode(pin, INPUT);
      attachInterruptArg(pin, isr, this, FALLING);
    }

    bool handler()
    {
      if (!pressed)
      {
         return false;
      }
      
      if (pressed && digitalRead(pin) == LOW) 
      {
        pressed = false;
        return true;
      }
      return false;
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
  if (btn.handler())
  {
    counter++;
    Serial.printf("Times pressed: %lu\n", counter);
  }
}
