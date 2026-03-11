#include <Arduino.h>
#include "controller.h"

constexpr uint32_t BAUD_RATE = 115200;

Encoder encoder(PIN_ENC_A, PIN_ENC_B, PIN_ENC_SW);
Servo servo(PIN_SERVO, SERVO_CHANNEL);
Controller controller(encoder, servo);


void setup()
{
  Serial.begin(BAUD_RATE);
  controller.init();
}

void loop()
{
  controller.update(millis());
}
