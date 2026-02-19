#ifndef TRAFFIC_H
#define TRAFFIC_H

#include "led.h"
#include "button.h"
#include "states.h"
#include "times.h"

class Traffic
{
  Led& red;
  Led& yellow;
  Led& green;
  Btn& btn;
  
  St state{St::NONE};
  bool regular{true};

  private:
    void enterState(St next);

  public:
    Traffic(Led& r, Led& y, Led& g, Btn& b);
    void init();
    void update(uint32_t now);
};

#endif  // TRAFFIC_H