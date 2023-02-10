/**
 * Receive and transmit data with RS232.
 *
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \date February 9, 2023
 */

#ifndef USART_H
#define USART_H

#include <avr/io.h>

#include <tp2/components/io.hpp>

class Usart
{
public:
    static void initialize();
    static void transmit(const uint8_t data);
    static void transmit(const char* data);
};
#endif
