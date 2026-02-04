#include <Arduino.h>

constexpr uint8_t PIN_0 = 15;
constexpr uint8_t PIN_1 = 16;
constexpr uint8_t PIN_2 = 17;

constexpr uint16_t T_0 = 200;
constexpr uint16_t T_1 = 500;
constexpr uint16_t T_2 = 1000;

uint32_t now = 0;

struct Led {
  uint8_t pin;
  uint16_t blinkTime;
  uint8_t state;
  uint32_t lastToggle;

  Led (uint8_t p, uint16_t t)
  : pin(p), blinkTime(t), state(LOW), lastToggle(0) {}
};

constexpr size_t LED_COUNT = 3;

Led leds[LED_COUNT] = {
  {PIN_0, T_0},
  {PIN_1, T_1},
  {PIN_2, T_2}
};


void updateLeds(uint32_t);

void setup() 
{
  for (size_t i = 0; i < LED_COUNT; i++)
  {
    pinMode(leds[i].pin, OUTPUT);
    digitalWrite(leds[i].pin, LOW);
  }
}

void loop() 
{
  now = millis();
  updateLeds(now);
}

void updateLeds(uint32_t now)
{
  for (size_t i = 0; i < LED_COUNT; i++)
  {
    if (now - leds[i].lastToggle > leds[i].blinkTime)
    {
      leds[i].lastToggle = now;
      leds[i].state = !leds[i].state;
      digitalWrite(leds[i].pin, leds[i].state);
    }
  }
}
