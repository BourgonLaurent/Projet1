/**
 * Send data with RS232.
 *
 * Hardware Identification
 * USART: D0 & D1.
 *
 * Team #4546
 * \author Catalina Andrea Araya Figueroa
 * \author Mehdi Benouhoud
 * \author Laurent Bourgon
 * \author Ihsane Majdoubi
 *
 * \date March 1, 2023
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <avr/io.h>

class Communication
{
public:
    static void initialize();
    static void send(const uint16_t data);
    static void send(const char* data);

private:
    static void sendCharacter(const uint8_t data);
};
#endif
