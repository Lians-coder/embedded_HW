#include <Arduino.h>

constexpr uint8_t PIN = 5;
constexpr uint32_t readPeriod = 100;
uint32_t lastRead = 0;

constexpr uint16_t vRef = 1100;
constexpr uint16_t maxADC = 1023;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting");
}

void readVoltageHandler(uint32_t now)
{
  if (now - lastRead >= readPeriod)
  {
    lastRead = now;
    uint16_t voltageRaw = analogRead(PIN);
    uint32_t voltageCalc = voltageRaw * vRef / maxADC;
    uint32_t voltageMV = analogReadMilliVolts(PIN);
    float measurementError = fabs((float)voltageMV - (float)voltageCalc) * 100.0f / (float)voltageMV;

    Serial.printf(
      "Voltage (raw): %lu\nVoltage (mV): %lu\nVoltage (calc.): %lu\nError: %.2f %%\n\n",
      voltageRaw, voltageMV, voltageCalc, measurementError
    );
  }
}

void loop()
{
  uint32_t now = millis();
  readVoltageHandler(now);
}
