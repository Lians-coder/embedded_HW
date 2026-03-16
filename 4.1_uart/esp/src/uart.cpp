#include "uart.h"
#include "led.h"


Uart::Uart(uint8_t rxP, uint8_t txP)
  : pinRx(rxP), pinTx(txP) {}


void Uart::init()
{
  uartNr.begin(baudRate, config, pinRx, pinTx);

  uart_isr_free(UART_NUM_1);
  uart_isr_register(UART_NUM_1, uartIsr, this, ESP_INTR_FLAG_IRAM, nullptr);

  uart_set_rx_full_threshold(UART_NUM_1, 1);
  uart_enable_rx_intr(UART_NUM_1);
}


void IRAM_ATTR Uart::uartIsr(void* arg)
{
  Uart* self = static_cast<Uart*>(arg);

  while (self->uartNr.available())
  {
    uint8_t b = self->uartNr.read();
    self->pushByte(b);
  }
}


void Uart::process()
{
  uint8_t b;
  while(popByte(b))
  {
    parseByte(b);
  }
}


bool Uart::pushByte(uint8_t b)
{
  size_t next = (head + 1) % RX_BUF_SIZE;

  if (next == tail)
  {
    return false;
  }

  rxBuffer[head] = b;
  head = next;
  return true;
}


bool Uart::popByte(uint8_t b)
{
  if (tail == head)
  {
    return false;
  }

  b = rxBuffer[tail];
  tail = (tail + 1) % RX_BUF_SIZE;
  return true;
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
    {
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
}


void Uart::transmit(uint8_t cmd)
{
  uint8_t frame[FRAME_SIZE];
  frame[0] = startByte;
  frame[1] = cmd;
  frame[2] = cmd ^ startByte;

  uartNr.write(frame, FRAME_SIZE);
}


void Uart::transmitToggle()
{
  transmit(cmdToggle);
}
