#include <Arduino.h>

// gpio
constexpr uint8_t BOOT_PIN     = 0;
constexpr uint8_t EXT_PIN      = 5;
constexpr uint8_t LED_RED_PIN  = 15;
constexpr uint8_t LED_BLUE_PIN = 16;

// time
constexpr uint32_t DB_DELAY    = 50;
constexpr uint16_t FAST_T      = 500;
constexpr uint16_t SLOW_T      = 2000;

// 1 - fast, 0 - slow
bool MODE = 0;

uint32_t now = 0;

struct Btn {
  uint8_t pin;
  bool mode;           // 1 - fast, 0 - slow
  bool activeLow;      // bootBtn is LOW when pressed, extBnt is HIGH when pressed
  uint8_t state;       // DB state
  uint8_t lastState;   // raw state
  uint32_t lastDBtime;

  Btn (uint8_t p, bool m)
  : pin(p), mode(m), activeLow(!m), state(LOW), lastState(LOW), lastDBtime(0) {}
};

Btn bootBtn {BOOT_PIN, 0};
Btn extBtn {EXT_PIN, 1};


void blink(uint16_t);
void btnHandler(Btn&);

void setup() 
{
  pinMode(bootBtn.pin, INPUT_PULLUP);  // LOW - pressed
  pinMode(extBtn.pin, INPUT);          // HIGH - pressed

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);
}

void loop() 
{
  now = millis();

  btnHandler(bootBtn);
  btnHandler(extBtn);

  blink(MODE ? FAST_T : SLOW_T);
}

void blink(uint16_t t)
{
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, HIGH);
  delay(t);
  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(LED_BLUE_PIN, LOW);
  delay(t); 
}


void btnHandler(Btn &btn)
{
  uint8_t readState = digitalRead(btn.pin);

  if (readState != btn.lastState)
  {
    btn.lastDBtime = now;
    btn.lastState = readState;
  }
  
  if (now - btn.lastDBtime > DB_DELAY)
  {
    if (readState != btn.state)
    {
      btn.state = readState;

      //! bootBtn is LOW when pressed, extBnt is HIGH when pressed
      bool pressed = (btn.activeLow) ? (btn.state == LOW) : (btn.state == HIGH);

      if (pressed)
      {
        MODE = btn.mode;
      }
    }
  }
}