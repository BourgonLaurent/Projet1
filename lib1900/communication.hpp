/**
 * Send data with RS232.
 *
 * Hardware Identification
 *  USART: D0 & D1.
 *
 * USAGE:
 *  Communication::initialize();
 *  Communication::send("lib1900\n");
 *  Communication::send(1000);
 *  const uint8_t value = Communication::receive();
 *
 * Team #4546
 *  \author Catalina Andrea Araya Figueroa
 *  \author Mehdi Benouhoud
 *  \author Laurent Bourgon
 *  \author Ihsane Majdoubi
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

    static uint8_t receive();

    static void send(const char* data);
    static void send(const uint16_t data);

private:
    static void sendCharacter(const uint8_t data);
};
#endif
