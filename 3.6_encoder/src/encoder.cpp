#include "encoder.h"


const int8_t Encoder::table[16] =
{
     0,  1, -1,  0,
    -1,  0,  0,  1,
     1,  0,  0, -1,
     0, -1,  1,  0
};


Encoder::Encoder(uint8_t pA, uint8_t pB, uint8_t pSw, bool rotRev)
: pinA (pA), pinB(pB), btn(pSw), rotationReverse(rotRev) {}  


void Encoder::init()
{
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  
  lastState = readState();

  attachInterruptArg(digitalPinToInterrupt(pinA), isrA, this, CHANGE);
  attachInterruptArg(digitalPinToInterrupt(pinB), isrB, this, CHANGE);

  btn.init();
}

void Encoder::btnUpdate(uint32_t now)
{
 btn.update(now);
}


bool Encoder::btnPressed()
{
  return btn.pressed();
}


bool Encoder::rotationCw()
{
  if (flagCw)
  {
    flagCw = false;
    return true;
  }
  return false;
}


bool Encoder::rotationCcw()
{
  if (flagCcw)
  {
    flagCcw = false;
    return true;
  }
  return false;
}


uint8_t IRAM_ATTR Encoder::readState()
{
  uint8_t gpio = REG_READ(GPIO_IN_REG);
  uint8_t gpioA = (gpio >> pinA) & 1;
  uint8_t gpioB = (gpio >> pinB) & 1;
  return (gpioA << 1 | gpioB);
}


void IRAM_ATTR Encoder::isrA(void* arg)
{
  static_cast<Encoder*>(arg)->handleIsrDirection();
}
 

void IRAM_ATTR Encoder::isrB(void* arg)
{
  static_cast<Encoder*>(arg)->handleIsrDirection();
}


void IRAM_ATTR Encoder::handleIsrDirection()
{
  uint32_t nowUS = micros();
  if (nowUS - lastTick < debounceT)
  {
    return;
  }

  uint8_t state = readState();
  int8_t delta = table[(lastState << 2 | state)];
  lastState = state;

  // if(delta > 0) flagCw = true;
  // else if(delta < 0) flagCcw = true;

  Direction dir = Direction::NONE;
  // if (!rotationReverse)
  // {
    dir = (delta > 0) ? Direction::CW : (delta < 0 ? Direction::CCW : Direction::NONE);
  // }
  // else
  // {
  //   dir = (delta < 0) ? Direction::CW : (delta > 0 ? Direction::CCW : Direction::NONE);
  // }

  if (dir == lastAcceptedDir || dir == Direction::NONE)
  {
    return;
  }

  if (dir == Direction::CW) 
  {
    flagCw = true;
  }
  else if (dir == Direction::CCW) 
  {
    flagCcw = true;
  }

  lastAcceptedDir = dir;
  lastTick = nowUS;

  GPIO.status_w1tc = (1 << pinA) | (1 << pinB);
}

