#include <Arduino.h>

constexpr uint8_t debounceT = 50;
constexpr size_t btnCount   = 2;
constexpr uint8_t PIN_LEFT  = 4;
constexpr uint8_t PIN_RIGHT = 5;
constexpr uint32_t BAUD_RATE = 115200;


struct Btn {
  uint32_t counter;
  uint32_t lastPressed;
  uint8_t pin;
  const char* name;
  volatile bool pressed;

  Btn (uint8_t newPin, const char* newName)
  : pin(newPin), name(newName), counter(0), lastPressed(0), pressed(false) {}
};

Btn btns[btnCount] = {
  {PIN_LEFT, "LEFT"},
  {PIN_RIGHT, "RIGHT"}
};

void IRAM_ATTR reactionLeft() { btns[0].pressed = true; }
void IRAM_ATTR reactionRight() { btns[1].pressed = true; }

void setup()
{
  // todo  write in different functions
  //1
  Serial.begin(BAUD_RATE);
  Serial.println();

  //2
  for (int i = 0; i < btnCount; i++)
  {
    pinMode(btns[i].pin, INPUT);
  }

  //3
  attachInterrupt(digitalPinToInterrupt(btns[0].pin), reactionLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(btns[1].pin), reactionRight, RISING);
}


void handleButtons()
{
  // uint32_t now = millis();

  // if (btn.pressed && (now - btn.lastPressed > debounceT)) {
  //   btn.counter++;
  //   btn.lastPressed = now;
  //   Serial.printf("\n%s button pressed! Count: %lu\n", btn.name, btn.counter);
  // }

  // btn.pressed = false;

  for (int i = 0; i < btnCount; i++)
  {
    if (btns[i].pressed)
    {
      btns[i].pressed = false;
      if (now - btns[i].lastPressed > debounceT)
      {
        btns[i].lastPressed = now;
        btns[i].counter++;
        Serial.printf("\n%s button pressed! Count: %lu\n", btns[i].name, btns[i].counter); 
      }
    }
    
  }

}

void loop()
{
  uint32_t now = millis();
  handleButtons();

  // Serial.println("Hello!");
  // delay(250);
}
