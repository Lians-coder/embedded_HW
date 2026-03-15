#include "uart.h"
#include "led.h"


Uart::Uart(uint8_t rxP, uint8_t txP)
  : pinRx(rxP), pinTx(txP) {}


void Uart::init()
{
  uartNr.begin(baudRate, config, pinRx, pinTx);
}


void Uart::receiveAndReact()
{
  if (uartNr.available())
  {
    parseByte(uartNr.read());
  }
}


void Uart::parseByte(uint8_t b)
{
  if (b == startByte)
  {
    state = State::START;
    return;
  }

  switch(state)
  {
    case State::IDLE:
      break;

    case State::START:
      cmdReceived = b;
      state = State::RECEIVE;
      break;

    case State::RECEIVE:
      if (b == (cmdReceived ^ startByte))
      {
        if (cmdReceived == cmdToggle)
        {
          toggleLed();
        }
      }
      state = State::IDLE;
      break;
  }
}


void Uart::transmit(uint8_t cmd)
{
  uint8_t frame[3];
  frame[0] = startByte;
  frame[1] = cmd;
  frame[3] = cmd ^ startByte;

  uartNr.write(frame, 3);
}


void Uart::transmitToggle()
{
  transmit(cmdToggle);
}
