#include <Arduino.h>
#include "button.h"
#include "player.h"


Btn btn(BTN_PIN);
Player player;

void setup()
{
  btn.init();
  player.init();
  player.start(*Player::melodies[0], millis());  
}

void loop()
{
  uint32_t now = millis();
  
  btn.update(now);
  player.update(now);

  if (btn.wasPressed())
  {
    player.nextMelody(now);
  }
}
