#include <Arduino.h>

constexpr uint8_t debounceT = 50;
constexpr size_t btnCount   = 2;
constexpr uint8_t PIN_LEFT  = 4;
constexpr uint8_t PIN_RIGHT = 5;

struct Btn {
  uint8_t pin;
  const char* name;
  uint32_t counter;
  uint32_t lastPressed;
  volatile bool pressed;

  Btn (uint8_t p, const char* n)
  : pin(p), name(n), counter(0), lastPressed(0), pressed(false) {}
};

Btn btns[btnCount] = {
  {PIN_LEFT, "LEFT"},
  {PIN_RIGHT, "RIGHT"}
};

void IRAM_ATTR handleBtn(Btn &btn)
{
  uint32_t now = millis();
  if (now - btn.lastPressed > debounceT)
  {
    btn.pressed = true;
    btn.lastPressed = now;
  }
}

void IRAM_ATTR reactionLeft() { handleBtn(btns[0]); }
void IRAM_ATTR reactionRight() { handleBtn(btns[1]); }

void setup()
{
  Serial.begin(115200);

  for (int i = 0; i < btnCount; i++)
  {
    pinMode(btns[i].pin, INPUT);
  }

  attachInterrupt(digitalPinToInterrupt(btns[0].pin), reactionLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(btns[1].pin), reactionRight, FALLING);
}

void loop()
{
  for (int i = 0; i < btnCount; i++)
  {
    if (btns[i].pressed)
    {
      btns[i].pressed = false;
      btns[i].counter++;
      Serial.printf("\n%s button pressed! Count: %lu\n", btns[i].name, btns[i].counter);              
    }
  }

  Serial.println("Hello!");
  delay(250);
}
