#include <Arduino.h>
#include "potentiometer.h"
#include "servo.h"
#include "controller.h"

constexpr uint32_t BAUD_RATE = 115200;

Potentiometer pot(PIN_POTENTIOMETER);
Servo servo(PIN_SERVO, SERVO_CHANNEL);
Controller controller(pot, servo);


void setup()
{
  Serial.begin(BAUD_RATE);

  pot.init();
  servo.init();
}

void loop()
{
  controller.update(millis());
}
