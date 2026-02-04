#include <Arduino.h>

constexpr uint8_t LED_RED_PIN = 11;
constexpr uint8_t LED_BLUE_PIN = 12;

void setup() 
{
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);
}

void loop() 
{
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, HIGH);
  delay(500);
  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(LED_BLUE_PIN, LOW);
  delay(500); 
}
