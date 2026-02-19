#include "traffic.h"

Traffic::Traffic(Led& r, Led& y, Led& g, Btn& b)
  : red(r), yellow(y), green(g), btn(b) {}


void Traffic::init()
{
  red.init();
  yellow.init();
  green.init();
  btn.init();

  state = btn.isInitialized() ? St::GREEN : St::ERROR;
}


void Traffic::enterState(St next)
{
  red.reset();
  yellow.reset();
  green.reset();
  state = next;
}


void Traffic::update(uint32_t now)
{
  btn.update(now);

  if (btn.wasPressed())
  {
    regular = !regular;
  }

  if (!regular && state != St::ERROR)
  {
    enterState(St::SPECIAL);
  }

  switch (state)
    {
      case St::GREEN:
        if (green.stable(now, STABLE_GREEN_P))
        {
          enterState(St::GREEN_BLINK);
        }
        break;

      case St::GREEN_BLINK:
        if (green.blink(now, BLINK_GREEN_P))
        {
          enterState(St::YELLOW);
        }
        break;
      
      case St::YELLOW:
        if (yellow.stable(now, STABLE_YELLOW_P))
        {
          enterState(St::RED);
        }
        break;

      case St::RED:
        if (red.stable(now, STABLE_RED_P))
        {
          enterState(St::RED_YELLOW);
        }
        break;

      case St::RED_YELLOW:
        if (red.stable(now, BEFORE_GREEN_P) &&
          yellow.stable(now, BEFORE_GREEN_P))
        {
          enterState(St::GREEN);
        }
        break;

      case St::SPECIAL:
        if (!regular)
        {
          yellow.blink(now, SPECIAL_P, true);
        }
        else
        {
          enterState(St::GREEN);
        }
        break;

      case St::ERROR:
        red.blink(now, SPECIAL_P, ERROR_T, true);
        yellow.blink(now, SPECIAL_P, ERROR_T, true);
        green.blink(now, SPECIAL_P, ERROR_T, true);
        break;
    }
}
