#ifndef LED_H
#define LED_H

#include <Arduino.h>

constexpr uint8_t LED_RED_PIN = 11;
constexpr uint8_t LED_BLUE_PIN = 12;

uint8_t ledRedState = LOW;
uint8_t ledBlueState = HIGH;

void setupPins() 
{
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
}

void setPinsLowOnSetup() 
{
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);
}


void setPinsState(uint8_t redState, uint8_t blueState) 
{
  ledRedState = redState;
  ledBlueState = blueState;
}

void handlerPinsState() 
{
  digitalWrite(LED_RED_PIN, ledRedState);
  digitalWrite(LED_BLUE_PIN, ledBlueState);
}


#endif // LED_H