#include <Arduino.h>

constexpr uint8_t PIN_RELAY = 5;
constexpr uint8_t PIN_NO = 4;

constexpr uint8_t TIMES_TO_MEASURE = 10;
uint8_t timesMeasured = 0;

constexpr uint32_t PERIOD = 1000;
uint32_t lastToggle = 0;

constexpr uint32_t debounceRelayT = 2000; // 2 ms
volatile bool pinNOwasClosed = false;
volatile uint32_t lastIsrTime = 0;

uint8_t relayState = HIGH;
uint32_t startT = 0;
uint32_t endT   = 0;
uint32_t sumDelayTime = 0;

void IRAM_ATTR isr()
{
  uint32_t now = micros();
  if (now - lastIsrTime > debounceRelayT)
  {
    pinNOwasClosed = true;
    lastIsrTime = now;
  }
}

void setup()
{
  Serial.begin(115200);  
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, relayState);
  pinMode(PIN_NO, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_NO), isr, FALLING);
}

void loop()
{
  uint32_t now = millis();
  if (now - lastToggle >= PERIOD)
  {
    lastToggle = now;
    relayState = !relayState;
    if (relayState == LOW)
    {
      pinNOwasClosed = false;
      startT = micros();
    }
    digitalWrite(PIN_RELAY, relayState);
  }

  if (pinNOwasClosed && relayState == LOW)
  {
    pinNOwasClosed = false;
    endT = micros();
    uint32_t delayFromInToClosed = endT - startT;
    if (delayFromInToClosed >= debounceRelayT)
    {
      timesMeasured++;
      sumDelayTime += delayFromInToClosed;
      Serial.printf("Trial %u. Delay from IN to close NO contact: %lu μs.\n", timesMeasured, delayFromInToClosed);

      if (timesMeasured % TIMES_TO_MEASURE == 0)
      {
        Serial.printf("\tAvg on last %u times: %.2f ms\n\n", TIMES_TO_MEASURE, ((float)sumDelayTime / (TIMES_TO_MEASURE * 1000)));
        sumDelayTime = 0;
        timesMeasured = 0;
      }      
    }
  }
}
