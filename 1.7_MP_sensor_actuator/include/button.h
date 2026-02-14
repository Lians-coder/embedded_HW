constexpr uint8_t BTN_PIN = 6;
constexpr uint32_t DEBOUNCE_T = 50;
constexpr uint32_t HOLD_T = 2000;

class Btn
{
  private:
    uint32_t dbStart = 0;
    uint32_t holdStart = 0;
    const uint8_t pin;
    volatile bool pressItr = false;
    bool wasPressed = false;
    bool holdFlag = false;
    
    enum class BtnSt
    {
      IDLE,
      DEBOUNCING,
      PRESSED,
      HOLD
    };

    BtnSt state = BtnSt::IDLE;
    
    static void IRAM_ATTR isr(void* arg) 
    {
      static_cast<Btn*>(arg)->pressItr = true;
    }

  public:
    explicit Btn(uint8_t p) : pin(p) {}

    void init()
    {
      pinMode(pin, INPUT);
      attachInterruptArg(digitalPinToInterrupt(pin), isr, this, FALLING);
    }
    
    void update(uint32_t now)
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
              holdStart = now;
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
          else if (now - holdStart >= HOLD_T)
          {
            holdFlag = true;
            state = BtnSt::HOLD;
          }
          break;

        case BtnSt::HOLD:
          if (!isDown) 
          { 
            holdFlag = false;
            state = BtnSt::IDLE;
          }
          break;
      }
    }

    bool pressed()
    {
      if (wasPressed) 
      {
        wasPressed = false;
        return true;
      }
      return false;
    }

    bool held()
    {
      if (holdFlag) 
      {
        holdFlag = false;
        return true;
      }
      return false;
    }
};

Btn btn(BTN_PIN);
