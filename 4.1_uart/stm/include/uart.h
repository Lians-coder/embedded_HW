#ifndef UART_H
#define UART_H

#include <stdbool.h>

#define START_BYTE 0xAA
#define FRAME_SIZE 3
#define RX_BUF_SIZE 64
#define FRAME_TIMEOUT 10

extern UART_HandleTypeDef huart2;


typedef enum 
{
  TOGGLE = 'T'
} 
Cmd;

typedef enum
{
  IDLE,
  START,
  RECEIVE
} 
State;

// extern State state;

typedef struct
{
  uint8_t rxBuffer[RX_BUF_SIZE];
  uint8_t rxByte;  
  volatile size_t head;
  volatile size_t tail;
  uint8_t cmdReceived;
  State state;
} UartContext;

extern UartContext uartCtx;


void transmit(uint8_t cmd);
void transmitToggle();
void uartProcess();
void parseByte(uint8_t b);
bool pushByte(uint8_t b);
bool popByte(uint8_t* b);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif  // UART_H