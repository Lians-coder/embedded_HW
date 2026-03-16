#ifndef UART_H
#define UART_H

#include <stdbool.h>

#define START_BYTE 0xAA
#define FRAME_SIZE 3
#define RX_BUF_SIZE 64
#define FRAME_TIMEOUT 50

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


typedef struct
{
  uint8_t rxBuffer[RX_BUF_SIZE];
  uint8_t rxByte;  
  volatile size_t head;
  volatile size_t tail;
  uint8_t cmdReceived;
  State state;
} 
UartContext;

extern UartContext uartCtx;

void uartInit(UART_HandleTypeDef* huart);
void transmit(uint8_t cmd);
void transmitToggle();
void uartProcess(uint32_t now);
void parseByte(uint8_t b, uint32_t now);
bool pushByte(uint8_t b);
bool popByte(uint8_t* b);


#endif  // UART_H