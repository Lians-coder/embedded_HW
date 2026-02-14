#include <Arduino.h>

// gpio

typedef pin_t uint8_t;

constexpr pin_t BOOT_PIN     = 0;
constexpr pin_t EXT_PIN      = 5;
constexpr pin_t LED_RED_PIN  = 15;
constexpr pin_t LED_BLUE_PIN = 16;

// time
constexpr uint32_t DB_DELAY    = 50;
constexpr uint32_t FAST_T      = 500;
constexpr uint32_t SLOW_T      = 2000;

// 1 - fast, 0 - slow
bool MODE = 0;

uint32_t now = 0;


// typedef struct Btn
struct Btn {
  uint32_t lastDBtime;
  uint8_t state;       // DB state
  uint8_t lastState;   // raw state
  pin_t pin;
  bool mode;           // 1 - fast, 0 - slow
  bool activeLow;      // bootBtn is LOW when pressed, extBnt is HIGH when pressed
  
  Btn (pin_t pin, bool mode)
  : pin(pin), mode(mode), activeLow(!mode), state(LOW), lastState(LOW), lastDBtime(0) {}
};//__attribute__((packed)); 

Btn bootBtn {BOOT_PIN, 0};
Btn extBtn {EXT_PIN, 1};


void blink(uint16_t);
void btnHandler(Btn&);


void setupInputPins()
{
  pinMode((uint8_t)bootBtn.pin, INPUT_PULLUP);  // LOW - pressed
  pinMode((uint8_t)extBtn.pin, INPUT);          // HIGH - pressed

  // sizeof(bootBtn);
}

void setupOutputPins()
{
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);
} 

void setup() 
{
  setupInputPins();
  setupOutputPins();
}

void loop() 
{
  now = millis();

  btnHandler(bootBtn);
  btnHandler(extBtn);

  blink(MODE ? FAST_T : SLOW_T);
}

void blink(uint32_t time_delay)
{
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, HIGH);
  delay(time_delay);
  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(LED_BLUE_PIN, LOW);
  delay(time_delay); 
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