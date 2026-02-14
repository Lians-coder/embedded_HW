#include <Arduino.h>

constexpr uint32_t BAUD_RATE = 115200;
constexpr uint8_t BUTTON_LEFT_PIN  = 4;
constexpr uint8_t BUTTON_RIGHT_PIN = 5;

volatile uint32_t counterLeft  = 0;
volatile uint32_t counterRight = 0;

volatile bool leftPressed      = false;
volatile bool rightPressed     = false;

void IRAM_ATTR reactionLeft()
{
  counterLeft++;
  leftPressed = true;
}

void IRAM_ATTR reactionRight()
{
  counterRight++;
  rightPressed = true;
}

void setup()
{
  pinMode(BUTTON_LEFT_PIN, INPUT);
  pinMode(BUTTON_RIGHT_PIN, INPUT);
  
  Serial.begin(BAUD_RATE);
  Serial.println();

  attachInterrupt(digitalPinToInterrupt(BUTTON_LEFT_PIN), reactionLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_RIGHT_PIN), reactionRight, RISING);
}

void loop()
{
  

  if (leftPressed) {
    leftPressed = false;
    Serial.printf("\nLEFT button pressed! Count: %lu\n", counterLeft);
  }

  if (rightPressed) {
    rightPressed = false;
    Serial.printf("\nRIGHT button pressed! Count: %lu\n", counterRight);
  }

  
 // Serial.println("Hello!");
 // delay(250);
}
