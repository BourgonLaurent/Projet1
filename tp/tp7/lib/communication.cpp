/**
 * Receive and send data with RS232.
 *
 * Hardware Identification
 * USART: D0 & D1.
 * 
 * INPUT: jumper on DbgEN
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date March 1, 2023
 */

#include "communication.hpp"

#include <stdio.h>
#include <string.h>

#include <lib/io.hpp>

void Communication::initialize()
{
    // 2400 bauds
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // Allow reception and transmission through USART0
    // (p.186-187) USART Control and Status Register 0 B
    io::setActive(&UCSR0B, RXEN0);
    io::setActive(&UCSR0B, TXEN0);

    // Frame Formats (Using 8N1 format)
    // (p. 188) USART Control and status Register 0 C
    //          Following tables 19-5/19-6/19-7
    io::clear(&UCSR0C, UCSZ02);
    io::setActive(&UCSR0C, UCSZ01);
    io::setActive(&UCSR0C, UCSZ00);

    // 1 stop bit
    io::clear(&UCSR0C, USBS0);

    // no parity
    io::clear(&UCSR0C, UPM01);
    io::clear(&UCSR0C, UPM00);
}

void Communication::send(const uint16_t data)
{
    static constexpr uint8_t nMaxCharacters = 6;

    char str[nMaxCharacters];
    snprintf(str, sizeof(str), "%u", data);
    send(str);
}

void Communication::send(const char* data)
{
    uint8_t dataLength = strlen(data);

    for (uint8_t i = 0; i < dataLength; i++) {
        Communication::sendCharacter(data[i]);
    }
}

void Communication::sendCharacter(const uint8_t data)
{
    while (!(UCSR0A & _BV(UDRE0))) {}

    UDR0 = data;
}
