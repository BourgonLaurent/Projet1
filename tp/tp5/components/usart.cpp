/**
 * Receive and transmit data with RS232.
 *
 * Team #45
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 9, 2023
 */

#include "usart.hpp"

#include <string.h>

void Usart::initialize()
{
    // 2400 bauds
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0
    io::setActive(&UCSR0B, RXEN0);
    io::setActive(&UCSR0B, TXEN0);

    // Format des trames
    // 8 bits
    io::clear(&UCSR0C, UCSZ02);
    io::setActive(&UCSR0C, UCSZ01);
    io::setActive(&UCSR0C, UCSZ00);

    // 1 stop bit
    io::clear(&UCSR0C, USBS0);

    // sans parité
    io::clear(&UCSR0C, UPM01);
    io::clear(&UCSR0C, UPM00);
}

void Usart::transmit(const uint8_t data)
{
    while (!(UCSR0A & _BV(UDRE0))) {}

    UDR0 = data;
}

void Usart::transmit(const char* data)
{
    uint8_t dataLength = strlen(data);

    for (uint8_t i = 0; i < dataLength; i++) {
        Usart::transmit(data[i]);
    }
}
