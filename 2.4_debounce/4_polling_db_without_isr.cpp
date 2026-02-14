#include <Arduino.h>

static constexpr uint8_t BTN_PIN = 5;
static constexpr uint32_t POLLING_T = 5;
uint32_t lastPoll = 0;
uint16_t counter = 0;

enum class BtnSt
{
  NONE, // todo rename
  PRESSED,
  RELEASED,
  ERROR
};

BtnSt currentState = BtnSt::NONE;
uint8_t STABLE = 0;
static constexpr uint8_t STABLE_TIMES = 10; // 50 ms debounce

void setup()
{
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT);
}

void loop()
{
  uint32_t now = millis();

  if (now - lastPoll >= POLLING_T)
  {
    lastPoll = now;
    bool pressed = digitalRead(BTN_PIN) == LOW;
    
    if (currentState == BtnSt::RELEASED)
    {
      if (pressed)
      {
        if (++STABLE >= STABLE_TIMES)
        {
          currentState = BtnSt::PRESSED;
          STABLE = 0;
          counter++;
          Serial.printf("Times pressed: %lu\n", counter);
        }
      }
      else { STABLE = 0; }
    }
    else
    {
      if (!pressed)
      {
        if (++STABLE >= STABLE_TIMES)
        {
          currentState = BtnSt::RELEASED;
          STABLE = 0;
        }
      }
      else { STABLE = 0; }
    }
  }
}
