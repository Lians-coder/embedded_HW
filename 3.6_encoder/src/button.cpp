#include "button.h"


Btn::Btn(uint8_t p) : pin(p) {}


void IRAM_ATTR Btn::isr(void* arg) 
{
  static_cast<Btn*>(arg)->pressItr = true;
}


void Btn::init()
{
  pinMode(pin, INPUT_PULLUP);
  attachInterruptArg(pin, isr, this, FALLING);
}


void Btn::update(uint32_t now)
{
  bool isDown = (digitalRead(pin) == LOW);

  switch (state)
  {
    case BtnSt::IDLE:
    {
      noInterrupts();
      bool irq = pressItr;
      pressItr = false;
      interrupts();
      if (irq)
      {
        dbStart = now;
        state = BtnSt::DEBOUNCING;
      }
      break;          
    }

    case BtnSt::DEBOUNCING:
      if (now - dbStart >= DEBOUNCE_T)
      {
        if (isDown)
        {
          wasPressed = true;
          state = BtnSt::PRESSED;
        }
        else { state = BtnSt::IDLE; }
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


bool Btn::pressed()
{
  if (wasPressed) 
  {
    wasPressed = false;
    return true;
  }
  return false;
}
