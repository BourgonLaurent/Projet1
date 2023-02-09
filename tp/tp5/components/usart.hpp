#ifndef USART_H
#define USART_H
#include <avr/io.h>
#include <tp2/components/io.hpp>

class Usart
{
public:
    static void initialize();
    static void transmit(uint8_t data);
    static void transmit(char data[], uint8_t dataLength);
};
#endif