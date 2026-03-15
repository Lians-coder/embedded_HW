#ifndef UART_H
#define UART_H

#include <HardwareSerial.h>

constexpr uint8_t UART_NR = 1;
constexpr uint8_t PIN_TX = 17;
constexpr uint8_t PIN_RX = 18;
constexpr uint16_t BAUD_RATE = 9600;
constexpr SerialConfig UART_CONFIG = SERIAL_8N1;
constexpr uint8_t START_BYTE = 0xAA;
constexpr uint8_t CMD_TOGGLE = 'T';


class Uart
{
  private:
    void transmit(uint8_t cmd);
    void parseByte(uint8_t b);

    HardwareSerial uartNr{UART_NR};
    SerialConfig config{UART_CONFIG};
    uint16_t baudRate{BAUD_RATE};
    const uint8_t startByte{START_BYTE};
    const uint8_t cmdToggle{CMD_TOGGLE};    
    const uint8_t pinRx;
    const uint8_t pinTx;
    uint8_t cmdReceived;

    enum class State
    {
      IDLE,
      START,
      RECEIVE
    };
    State state{State::IDLE};

  public:
    explicit Uart(uint8_t rxP, uint8_t txP);
    void init();
    void receiveAndReact();
    void transmitToggle();
};


#endif  // UART_H