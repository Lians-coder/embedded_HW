#include <Arduino.h>

static constexpr uint8_t LED_PIN = 4;
static constexpr uint8_t BTN_PIN = 5;
static constexpr uint32_t DEBOUNCE_T = 50;
static constexpr uint16_t PERIOD_ALTERNATE_BLINK = 250;

static constexpr uint16_t loopBundleTimes = 10000;
uint32_t loopCounter = 0;
uint32_t loopTimeStart;
uint32_t loopTimeEnd;

enum ModesLed
{
  STATE_ALTERNATE,
  STATE_ON,
  STATE_OFF
};

uint8_t currentMode = STATE_ALTERNATE;

class Led
{
  public:
    uint8_t pin;
    explicit Led(uint8_t p) : pin(p) {}

    void init() 
    {
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW); 
    };

    void alternate(uint32_t now)
    {
      static uint8_t state = HIGH;
      static uint32_t lastChange = 0;
      static constexpr uint16_t period = PERIOD_ALTERNATE_BLINK;

      if (now - lastChange > period)
      {
        lastChange = now;
        state = !state;
        digitalWrite(pin, state);
      }
    }

    void set(uint8_t mode, uint32_t now) 
    {      
      switch(mode)
      {
        case STATE_ON:
          digitalWrite(pin, HIGH);
          break;
        case STATE_OFF:
          digitalWrite(pin, LOW);
          break;
        case STATE_ALTERNATE:
          alternate(now);    
      }
    };
};


class Btn
{
  public:
    uint8_t pin;
    explicit Btn(uint8_t p) : pin(p) {}

    volatile bool pressed = false;
    volatile uint32_t lastPressed = 0;

    static void IRAM_ATTR isr(void* arg) 
    {
      Btn* self = static_cast<Btn*>(arg);
      self->pressed = true;
    };

    void init()
    {
      pinMode(pin, INPUT);
      attachInterruptArg(pin, isr, this, FALLING);
    }

    bool handler(uint32_t now)
    {
      bool wasPressed = false;

      noInterrupts();
      wasPressed = pressed;
      pressed = false;
      interrupts();

      if (!wasPressed) return false;

      if (now - lastPressed > DEBOUNCE_T)
      {
        lastPressed = now;
        return true;
      }
      return false;
    }
};


Led led(LED_PIN);
Btn btn(BTN_PIN);

void setup()
{
  uint32_t now = millis();
  Serial.begin(115200);
  
  led.init();
  led.set(currentMode, now);

  btn.init();

}

void loop()
{
  uint32_t now = millis();

  // loop counting
  if (loopCounter == 0) loopTimeStart = now;
  loopCounter++;
  if (loopCounter % loopBundleTimes == 0)
  {
    loopTimeEnd = now;
    uint32_t total = loopTimeEnd - loopTimeStart;
    uint32_t mean = total / loopBundleTimes;
    Serial.printf(
      "Loop %u times bundle lasts \n\tfrom: %lu ms \n\tto:   %lu ms\n\ttotal time: %lu ms\n\tmean period: %lu ms.\n\n",
      loopBundleTimes, loopTimeStart, loopTimeEnd, total, mean
    );
    loopTimeStart = loopTimeEnd;
  }
  
  // button pressed
  if (btn.handler(now))
  {
    switch(currentMode)
    {
      case STATE_OFF:
        currentMode = STATE_ALTERNATE;
        break;
      case STATE_ALTERNATE:
        currentMode = STATE_ON;
        break;
      case STATE_ON:
        currentMode = STATE_OFF;
        break;
    }
  }

  // update led
  led.set(currentMode, now);

}
