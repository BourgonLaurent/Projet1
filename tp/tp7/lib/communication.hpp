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
 * 
 * USAGE: see the message sent with the command `serieViaUSB -l`
 *      Communication::initialize();
 *      Communication::send("Lib1900\n"); 
 *      Communication::send(1000);
 * 
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
