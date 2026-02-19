#include "button.h"

Btn::Btn(pin_t p) : pin(p) {}


void IRAM_ATTR Btn::isr(void *arg)
{
  static_cast<Btn*>(arg)->isrFlag = true;     
}


void Btn::init()
{
  pinMode(pin, INPUT);
  attachInterruptArg(pin, Btn::isr, this, FALLING);
  state = digitalRead(pin) ? BtnSt::IDLE : BtnSt::PRESSED;
}


bool Btn::isInitialized() const
{
 return (state != BtnSt::NONE);
}


void Btn::update(uint32_t now)
{
  bool isDown = (digitalRead(pin) == LOW);

  switch (state)
  {
    case BtnSt::IDLE:
    {
      noInterrupts();
      bool wasIsr = isrFlag;
      isrFlag = false;
      interrupts();

      if (wasIsr)
      {
        dbStart = now;
        state = BtnSt::DEBOUNCING;
      }
      break;
    }

    case BtnSt::DEBOUNCING:
      if (now - dbStart > DEBOUNCE_T)
      {
        if (isDown)
        {
          pressed = true;
          state = BtnSt::PRESSED;
        }
        else
        {
          state = BtnSt::IDLE;
        }
      }
      break;

    case BtnSt::PRESSED:
      if (!isDown)
      {
        state = BtnSt::IDLE;
      }
      break;
  }
}


bool Btn::wasPressed()
{
  if (pressed)
  {
    pressed = false;
    return true;
  }
  return false;
}
