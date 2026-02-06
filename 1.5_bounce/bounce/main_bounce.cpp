#include <Arduino.h>

constexpr uint8_t BUTTON_LEFT  = 4;
constexpr uint8_t BUTTON_RIGHT = 5;

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
  pinMode(BUTTON_LEFT, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);
  
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(BUTTON_LEFT), reactionLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_RIGHT), reactionRight, RISING);
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

  Serial.println("Hello!");
  delay(250);
}
