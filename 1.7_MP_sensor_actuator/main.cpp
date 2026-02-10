#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "states.h"
#include "button.h"
#include "blinkingPatterns.h"

constexpr uint8_t LDR_PIN = 5;

constexpr uint32_t readPeriod = 100;
uint32_t lastRead = 0;

constexpr uint32_t DEADZONE_MV = 30;
uint32_t minVoltage;
uint32_t maxVoltage;
uint32_t lessThanMinV;
uint32_t higherThanMaxV;

uint32_t now = 0;
uint32_t v = 0;

constexpr uint32_t PIXEL_UPDATE_T = 30;
static uint8_t brightnessPos = 0;

void changeColorOnBrightness(uint32_t);
void enterRegular();

void setup()
{
  Serial.begin(115200);

  btn.init();

  pixel.begin();
  pixel.clear();
  pixel.show();

  v = analogReadMilliVolts(LDR_PIN);
  currentState = St::NEED_CALIB;
}

void loop()
{
  now = millis();
  v = analogReadMilliVolts(LDR_PIN);
  btn.update(now);

  if (v < 0 || v > 3300)
  {
    enterState(St::ERROR_UNKNOWN);
  }

  switch (currentState)
  {
    case St::NEED_CALIB:
      if (btn.pressed())
      {
        enterState(St::NEED_MIN);
      }    
      needCalib.blinker(now);
      break;

    case St::NEED_MIN:
      if (btn.pressed())
      {
        minVoltage = v;
        enterState(St::NEED_MAX);
      }    
      needMin.blinker(now);
      break;

    case St::NEED_MAX:
      if (btn.pressed())
      {
        maxVoltage = v;
        if(minVoltage >= maxVoltage)
        {
          enterState(St::ERROR_UNKNOWN);
        }
        else enterState(St::SUCCESS_CALIB);
      }        
      needMax.blinker(now);
      break;

    case St::SUCCESS_CALIB:
      if (successCalib.blinker(now))
      {
        enterRegular();
        enterState(St::REGULAR);
      }
      if (btn.latched())
      {
        enterState(St::FORCE_CALIB);
      } 
      break;

    case St::REGULAR:
      if (maxVoltage <= minVoltage)
      {
        currentState = St::ERROR_UNKNOWN;
      }
      else if (v < minVoltage)
      { 
        lessThanMinV = v;
        enterState(St::ERROR_BELOW); 
      }
      else if (v > maxVoltage)
      { 
        higherThanMaxV = v;
        enterState(St::ERROR_ABOVE); 
      }
      if (btn.latched())
      {
        enterState(St::FORCE_CALIB);
      }     
      changeColorOnBrightness(now);
      break;

    case St::ERROR_ABOVE:
      if (higherThanMaxV < v)
      {
        higherThanMaxV = v;
      }
      if (btn.latched())
      {
        maxVoltage = higherThanMaxV;
        higherThanMaxV = 0;
        enterState(St::RESET_COMPLETED);
      }     
      errAbove.blinker(now);
      break;

    case St::ERROR_BELOW:
      if (lessThanMinV > v)
      {
        lessThanMinV = v;
      }
      if (btn.latched())
      {
        minVoltage = lessThanMinV;
        lessThanMinV = 0;
        enterState(St::RESET_COMPLETED);
      }     
      errBelow.blinker(now);
      break;

    case St::ERROR_UNKNOWN:
      if (btn.latched())
      {
        enterState(St::FORCE_CALIB);
      }    
      errUnknown.blinker(now);
      break;

    case St::RESET_COMPLETED:
      if(minVoltage > maxVoltage)
      {
        enterState(St::FORCE_CALIB);
      }
      if (resetCompleted.blinker(now))
      {
        enterState(St::SUCCESS_CALIB);
      }
      break;

    case St::FORCE_CALIB:
      if (forceCalib.blinker(now))
      {
        minVoltage = 0;
        maxVoltage = 0;
        enterState(St::NEED_CALIB);
      }
      break;
  }
}

void changeColorOnBrightness(uint32_t now)
{
  if (maxVoltage <= minVoltage)
  {
    currentState = St::ERROR_UNKNOWN;
    return;
  }

  static uint32_t lastDifferentV = 0;
  if (abs((int32_t)v - (int32_t)lastDifferentV) < DEADZONE_MV)
  {
    return;
  }
  lastDifferentV = v;

  static uint32_t lastUpdate = 0;
  if (now - lastUpdate < PIXEL_UPDATE_T ) return;
  lastUpdate = now;

  uint32_t clamped = constrain(v, minVoltage, maxVoltage);
  uint8_t pos = map(clamped, minVoltage, maxVoltage, 0, 255);
  pos = (brightnessPos * 3 + pos) /  4;
  brightnessPos = pos;
  uint32_t color = pixel.gamma32(colorWheel(pos));
  pixel.setPixelColor((PIXEL_COUNT - 1), color);
  pixel.show();
}

void enterRegular()
{
  uint32_t clamped = constrain(v, minVoltage, maxVoltage);
  brightnessPos = map(clamped, minVoltage, maxVoltage, 0, 255);
}
