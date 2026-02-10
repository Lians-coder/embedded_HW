constexpr uint8_t BTN_PIN = 6;
constexpr uint32_t DEBOUNCE_T = 50;
constexpr uint32_t LATCHED_T = 500;

class Btn
{
  private:
    const uint8_t pin;
    volatile bool pressItr = false;
    uint32_t dbStart = 0;
    uint32_t holdStart = 0;
    bool wasPressed = false;
    bool latchedFlag = false;
    
    enum class BtnSt
    {
      IDLE,
      DEBOUNCING,
      PRESSED,
      LATCHED
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
      attachInterruptArg(pin, isr, this, FALLING);
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
          else if (now - holdStart >= LATCHED_T)
          {
            latchedFlag = true;
            state = BtnSt::LATCHED;
          }
          break;

        case BtnSt::LATCHED:
          if (!isDown) 
          { 
            latchedFlag = false;
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

    bool latched()
    {
      if (latchedFlag) 
      {
        latchedFlag = false;
        return true;
      }
      return false;
    }
};

Btn btn(BTN_PIN);
