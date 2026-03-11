#include "controller.h"


Controller::Controller(Encoder& e, Servo& s)
  : encoder(e), servo(s) {}


void Controller::init()
{
  encoder.init();
  servo.init();
  servo.setAngle(ANGLE_CLOSED);

  Serial.println("SAFE LOCKED");
  resetAttempt();
}


void Controller::selectDigit()
{
  currentDigit = (currentDigit + 1) % 10;
  Serial.printf("\b%u", currentDigit);
}


void Controller::confirmDigit()
{
  if (digitIndex >= PIN_SIZE)
  {
    resetAttempt();
    return;
  }

  digits[digitIndex++] = currentDigit;
  Serial.printf("\b[%u] ", currentDigit);
  currentDigit = 0;

  if (digitIndex == PIN_SIZE)
  {
    trials++;

    if (validate())
    {
      openSafe();
    }
    else
    {
      Serial.printf("\nWRONG PIN!\n");
      resetAttempt();
    }
  }
}


bool Controller::validate()
{
  for (size_t i = 0; i < PIN_SIZE; i++)
  {
    if (digits[i] != PIN_CODE[i])
    {
      return false;
    }
  }
  return true;
}


void Controller::openSafe()
{
  servo.setAngle(ANGLE_OPEN);
  Serial.printf("\nSAFE OPENED!\n");
  while(true);
}


void Controller::resetAttempt()
{
  digitIndex = 0;
  currentDigit = 0;
  encoder.lastDir = Encoder::Direction::NONE;
 
  if(trials < MAX_TRIALS)
    Serial.printf("\tTrial: %u\n ", trials + 1);
}


void Controller::trialsOver()
{
  Serial.printf("You're out of all %u trials!\nALARM!!!\n", MAX_TRIALS);
  while (true);
}



void Controller::update(uint32_t now)
{
  if (trials >= MAX_TRIALS)
  {
    trialsOver();
  }

  // if (now - lastPoll < POLLING_T)
  // {
  //   return;
  // }
  // lastPoll = now;

  encoder.btnUpdate(now);
  if (encoder.btnPressed())
  {
    Serial.printf("\nRESET\n");
    resetAttempt();
    return;
  }

  if (encoder.rotationCw())
  {
      if(digitState == DigitState::CONFIRMED)
      {
        digitState = DigitState::SELECTING;
        currentDigit = 0;
      }

      selectDigit();
      // if (digitState == DigitState::SELECTING)
      // {
        
      // }
      encoder.lastDir = Encoder::Direction::CW;
  }

  else if (encoder.rotationCcw())
  {
      if(digitState == DigitState::SELECTING && encoder.lastDir == Encoder::Direction::CW)
      {
        confirmDigit();
        digitState = DigitState::CONFIRMED;
      }
      encoder.lastDir = Encoder::Direction::CCW;
  }
}

