#include "main.h"
#include "uart.h"
#include "led.h"


UartContext uartCtx =
{
  .head = 0,
  .tail = 0,
  .cmdReceived = 0,
  .state = IDLE
};


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2)
  {
    pushByte(uartCtx.rxByte);
    HAL_UART_Receive_IT(huart, &uartCtx.rxByte, 1);
  }
}



void transmit(uint8_t cmd)
{
  uint8_t frame[FRAME_SIZE];
  frame[0] = START_BYTE;
  frame[1] = cmd;
  frame[2] = cmd ^ START_BYTE;

  HAL_UART_Transmit(&huart2, frame, FRAME_SIZE, FRAME_TIMEOUT);
}


void transmitToggle()
{
  Cmd cmd = TOGGLE;
  transmit(cmd);
}


bool pushByte(uint8_t b)
{
  size_t next = (uartCtx.head + 1) % RX_BUF_SIZE;

  if (next == uartCtx.tail)
  {
    return false;
  }

  uartCtx.rxBuffer[uartCtx.head] = b;
  uartCtx.head = next;
  return true;
}


bool popByte(uint8_t* b)
{
  if (uartCtx.tail == uartCtx.head)
  {
    return false;
  }

  *b = uartCtx.rxBuffer[uartCtx.tail];
  uartCtx.tail = (uartCtx.tail + 1) % RX_BUF_SIZE;
  return true;
}


void uartProcess()
{
  uint8_t b;
  while(popByte(&b))
  {
    parseByte(b);
  }
}


void parseByte(uint8_t b)
{
  static uint32_t lastByteTime = 0;
  uint32_t now = HAL_GetTick();
  if (now - lastByteTime > FRAME_TIMEOUT)
  {
    uartCtx.state = IDLE;
  }
  lastByteTime = now;

  if (b == START_BYTE)
  {
    uartCtx.state = START;
    return;
  }

  switch(uartCtx.state)
  {
    case IDLE:
      break;
  
    case START:
      uartCtx.cmdReceived = b;
      uartCtx.state = RECEIVE;
      break;

    case RECEIVE:
    {
      if (b == (uartCtx.cmdReceived ^ START_BYTE))
      {
        if (uartCtx.cmdReceived == TOGGLE)
        {
          toggleLed();
        }
      }
      uartCtx.state = IDLE;
      break;
    }
  }
}

