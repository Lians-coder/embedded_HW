#ifndef UART_H
#define UART_H

#include <HardwareSerial.h>
#include <driver/uart.h>
#include <hal/uart_ll.h>

constexpr uint8_t PIN_TX = 17;
constexpr uint8_t PIN_RX = 18;
constexpr uint16_t BAUD_RATE = 9600;
constexpr SerialConfig UART_CONFIG = SERIAL_8N1;
constexpr uint8_t START_BYTE = 0xAA;
constexpr size_t FRAME_SIZE = 3;
constexpr size_t RX_BUF_SIZE = 64;

enum class Cmd : uint8_t
{
  Toggle = 'T'
};


class Uart
{
  private:
    void transmit(uint8_t cmd);
    void parseByte(uint8_t b);
    static void IRAM_ATTR uartIsr(void* arg);
    bool pushByte(uint8_t b);
    bool popByte(uint8_t &b);
    
    HardwareSerial uartNr{UART_NUM_1};
    SerialConfig config{UART_CONFIG};

    uint8_t rxBuffer[RX_BUF_SIZE];
    volatile size_t head{0};
    volatile size_t tail{0};

    uint16_t baudRate{BAUD_RATE};
    const uint8_t startByte{START_BYTE};
    const uint8_t cmdToggle{static_cast<uint8_t>(Cmd::Toggle)};    
    const uint8_t pinRx;
    const uint8_t pinTx;
    uint8_t cmdReceived{0};

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
    void process();
    void transmitToggle();
};


#endif  // UART_H